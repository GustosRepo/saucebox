#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Products/ActiveProduct.h"
#include "Products/HotPacket/HotPacketManifest.h"
#include "Products/ProductCatalog.h"

namespace
{
#if defined (SAUCE_PRODUCT_SECRET_SAUCE)
constexpr auto paramDrive = secret_sauce::parameters::movementRate;
constexpr auto paramCrush = secret_sauce::parameters::movementDepth;
constexpr auto paramWowDepth = secret_sauce::parameters::chop;
constexpr auto paramWowRate = secret_sauce::parameters::stutter;
constexpr auto paramTone = secret_sauce::parameters::filter;
constexpr auto paramMix = secret_sauce::parameters::mix;
constexpr auto paramOutput = secret_sauce::parameters::output;
constexpr auto paramInstantSauce = secret_sauce::parameters::sauce;
constexpr auto paramFlavor = secret_sauce::parameters::flavor;
constexpr auto paramWidth = secret_sauce::parameters::width;
constexpr auto paramFreeze = secret_sauce::performance::freeze;
constexpr auto paramReverseMomentary = secret_sauce::performance::reverse;
constexpr auto paramRepeat = secret_sauce::performance::repeat;
constexpr auto paramDropout = secret_sauce::performance::dropout;
constexpr auto paramTapeStop = secret_sauce::performance::tapeStop;
constexpr auto paramThrowFx = secret_sauce::performance::throwFx;
constexpr auto stateProgramIndex = hot_packet::state::programIndex;

float smoothStep (float edge0, float edge1, float value)
{
    const auto x = juce::jlimit (0.0f, 1.0f, (value - edge0) / (edge1 - edge0));
    return x * x * (3.0f - 2.0f * x);
}

void smoothToward (float& state, float target, float coefficient)
{
    state += (target - state) * coefficient;
}

struct SecretFlavorProfile
{
    int divisionOffset = 0;
    float depthBias = 0.0f;
    float chopBias = 0.0f;
    float stutterBias = 0.0f;
    float filterBias = 0.0f;
    float widthBias = 0.0f;
    float gateDepth = 0.78f;
    float reverseAmount = 0.0f;
    float throwAmount = 0.0f;
    float saturationDrive = 0.0f;
    float dropoutStart = 0.62f;
    float tapeDarken = 0.0f;
    float tapeDip = 0.0f;
};

constexpr std::array<SecretFlavorProfile, 12> secretFlavorProfiles {{
    {  0,  0.00f,  0.00f,  0.00f,  0.02f,  0.00f, 0.58f, 0.00f, 0.00f, 0.00f, 0.72f, 0.00f, 0.00f }, // Self Sample
    {  1,  0.06f,  0.22f,  0.04f,  0.08f, -0.06f, 0.92f, 0.00f, 0.00f, 0.02f, 0.52f, 0.00f, 0.00f }, // Vocal Chop
    { -1,  0.08f, -0.02f, -0.02f, -0.12f,  0.04f, 0.54f, 0.58f, 0.08f, 0.00f, 0.68f, 0.08f, 0.00f }, // Reverse Pull
    {  2,  0.10f,  0.10f,  0.28f,  0.00f, -0.10f, 0.86f, 0.00f, 0.02f, 0.04f, 0.50f, 0.00f, 0.00f }, // Stutter Step
    { -2,  0.12f, -0.08f, -0.08f, -0.20f, -0.04f, 0.45f, 0.08f, 0.00f, 0.05f, 0.76f, 0.30f, 0.12f }, // Tape Wobble
    {  0,  0.16f,  0.10f,  0.10f, -0.24f,  0.08f, 0.74f, 0.10f, 0.08f, 0.42f, 0.58f, 0.18f, 0.04f }, // Dirty Dream
    { -1,  0.04f, -0.08f,  0.06f,  0.16f,  0.16f, 0.50f, 0.04f, 0.60f, 0.00f, 0.70f, 0.00f, 0.00f }, // Drip Throw
    { -3,  0.10f, -0.04f,  0.00f, -0.18f,  0.06f, 0.46f, 0.12f, 0.10f, 0.02f, 0.74f, 0.20f, 0.06f }, // Half-Time Melt
    {  0,  0.08f,  0.02f,  0.04f, -0.04f,  0.14f, 0.56f, 0.18f, 0.04f, 0.08f, 0.64f, 0.06f, 0.00f }, // Formant Ghost
    { -1, -0.04f, -0.08f, -0.04f,  0.18f,  0.22f, 0.42f, 0.00f, 0.12f, 0.00f, 0.78f, 0.00f, 0.00f }, // Hook Maker
    { -2,  0.10f, -0.02f, -0.02f, -0.28f,  0.12f, 0.48f, 0.06f, 0.08f, 0.06f, 0.72f, 0.24f, 0.08f }, // Dark R&B
    {  2,  0.06f,  0.18f,  0.22f,  0.02f, -0.02f, 0.94f, 0.00f, 0.04f, 0.08f, 0.48f, 0.00f, 0.00f }  // Trap Motion
}};
#else
constexpr auto paramDrive = hot_packet::parameters::drive;
constexpr auto paramCrush = hot_packet::parameters::texture;
constexpr auto paramWowDepth = hot_packet::parameters::wowDepth;
constexpr auto paramWowRate = hot_packet::parameters::wowRate;
constexpr auto paramTone = hot_packet::parameters::tone;
constexpr auto paramMix = hot_packet::parameters::mix;
constexpr auto paramOutput = hot_packet::parameters::output;
constexpr auto paramInstantSauce = hot_packet::parameters::instantSauce;
constexpr auto stateProgramIndex = hot_packet::state::programIndex;
#endif

constexpr auto& presets = active_product::factoryPresets;
}

SauceBoxAudioProcessor::SauceBoxAudioProcessor()
    : AudioProcessor (BusesProperties().withInput ("Input", juce::AudioChannelSet::stereo(), true)
                                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
      apvts (*this, nullptr, "PARAMS", createParameterLayout())
{
}

void SauceBoxAudioProcessor::applyPreset (const hot_packet::PresetDefinition& preset)
{
#if defined (SAUCE_PRODUCT_SECRET_SAUCE)
    if (auto* flavorParam = apvts.getParameter (paramFlavor))
        flavorParam->setValueNotifyingHost (flavorParam->convertTo0to1 (static_cast<float> (currentProgram_)));

    if (auto* sauceParam = apvts.getParameter (paramInstantSauce))
        sauceParam->setValueNotifyingHost (sauceParam->convertTo0to1 (preset.instantSauce));

    if (auto* widthParam = apvts.getParameter (paramWidth))
        widthParam->setValueNotifyingHost (widthParam->convertTo0to1 (juce::jlimit (0.20f, 0.90f, preset.mix + 0.08f)));
#endif

    if (auto* driveParam = apvts.getParameter (paramDrive))
        driveParam->setValueNotifyingHost (driveParam->convertTo0to1 (preset.drive));

    if (auto* textureParam = apvts.getParameter (paramCrush))
        textureParam->setValueNotifyingHost (textureParam->convertTo0to1 (preset.texture));

    if (auto* wowDepthParam = apvts.getParameter (paramWowDepth))
        wowDepthParam->setValueNotifyingHost (wowDepthParam->convertTo0to1 (preset.wowDepth));

    if (auto* wowRateParam = apvts.getParameter (paramWowRate))
        wowRateParam->setValueNotifyingHost (wowRateParam->convertTo0to1 (preset.wowRate));

    if (auto* toneParam = apvts.getParameter (paramTone))
        toneParam->setValueNotifyingHost (toneParam->convertTo0to1 (preset.tone));

    if (auto* mixParam = apvts.getParameter (paramMix))
        mixParam->setValueNotifyingHost (mixParam->convertTo0to1 (preset.mix));

    if (auto* outputParam = apvts.getParameter (paramOutput))
        outputParam->setValueNotifyingHost (outputParam->convertTo0to1 (preset.output));
}

int SauceBoxAudioProcessor::findPresetIndexFromCurrentParams() const
{
    const auto drive = apvts.getRawParameterValue (paramDrive)->load();
    const auto texture = apvts.getRawParameterValue (paramCrush)->load();
    const auto wowDepth = apvts.getRawParameterValue (paramWowDepth)->load();
    const auto wowRate = apvts.getRawParameterValue (paramWowRate)->load();
    const auto tone = apvts.getRawParameterValue (paramTone)->load();
    const auto mix = apvts.getRawParameterValue (paramMix)->load();
    const auto output = apvts.getRawParameterValue (paramOutput)->load();
#if defined (SAUCE_PRODUCT_SECRET_SAUCE)
    const auto flavor = apvts.getRawParameterValue (paramFlavor)->load();
#endif

    const auto nearlyEqual = [] (float a, float b, float tolerance)
    {
        return std::abs (a - b) <= tolerance;
    };

    for (size_t i = 0; i < presets.size(); ++i)
    {
        const auto& p = presets[i];
#if defined (SAUCE_PRODUCT_SECRET_SAUCE)
        if (nearlyEqual (flavor, static_cast<float> (i), 0.01f)
            && nearlyEqual (drive, p.drive, 0.02f)
            && nearlyEqual (texture, p.texture, 0.02f)
            && nearlyEqual (wowDepth, p.wowDepth, 0.02f)
            && nearlyEqual (wowRate, p.wowRate, 0.02f)
            && nearlyEqual (tone, p.tone, 0.02f)
            && nearlyEqual (mix, p.mix, 0.02f)
            && nearlyEqual (output, p.output, 0.15f))
            return static_cast<int> (i);
#else
        if (nearlyEqual (drive, p.drive, 0.11f)
            && nearlyEqual (texture, p.texture, 0.002f)
            && nearlyEqual (wowDepth, p.wowDepth, 0.002f)
            && nearlyEqual (wowRate, p.wowRate, 0.002f)
            && nearlyEqual (tone, p.tone, 0.002f)
            && nearlyEqual (mix, p.mix, 0.002f)
            && nearlyEqual (output, p.output, 0.11f))
            return static_cast<int> (i);
#endif
    }

    return -1;
}

void SauceBoxAudioProcessor::prepareToPlay (double sampleRate, int)
{
    isPrepared_ = false;
    sampleRate_ = sampleRate;

    for (auto& s : crushStates_)
        s = {};

    toneState_.fill (0.0f);
    wowPhase_.fill (0.0f);
    secretGateState_.fill (1.0f);
    secretReverseMixState_.fill (0.0f);
    secretThrowMixState_.fill (0.0f);
    secretTapeAmountState_.fill (0.0f);
    secretTapeDipState_.fill (0.0f);
    secretDelayWritePosition_ = 0;
    secretFallbackPpq_ = 0.0;
    secretDelayBuffer_.setSize (2, juce::jmax (1, static_cast<int> (sampleRate_ * 2.0)));
    secretDelayBuffer_.clear();
    isPrepared_ = true;
}

void SauceBoxAudioProcessor::releaseResources()
{
    isPrepared_ = false;
}

bool SauceBoxAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    return layouts.getMainOutputChannelSet() == layouts.getMainInputChannelSet();
}

void SauceBoxAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;

    const auto totalNumInputChannels = getTotalNumInputChannels();
    const auto totalNumOutputChannels = getTotalNumOutputChannels();
    const auto numSamples = buffer.getNumSamples();
    const auto bufferChannels = buffer.getNumChannels();

    for (auto ch = totalNumInputChannels; ch < totalNumOutputChannels; ++ch)
        buffer.clear (ch, 0, numSamples);

    if (! isPrepared_ || sampleRate_ <= 0.0 || numSamples <= 0)
        return;

    const auto driveDb = apvts.getRawParameterValue (paramDrive)->load();
    const auto crush = apvts.getRawParameterValue (paramCrush)->load();
    const auto wowDepth = apvts.getRawParameterValue (paramWowDepth)->load();
    const auto wowRate = apvts.getRawParameterValue (paramWowRate)->load();
    const auto tone = apvts.getRawParameterValue (paramTone)->load();
    const auto mix = apvts.getRawParameterValue (paramMix)->load();
    const auto outputDb = apvts.getRawParameterValue (paramOutput)->load();

#if defined (SAUCE_PRODUCT_SECRET_SAUCE)
    const auto sauce = apvts.getRawParameterValue (paramInstantSauce)->load() / 100.0f;
    const auto flavorIndex = juce::jlimit (0, static_cast<int> (secretFlavorProfiles.size()) - 1,
                                           static_cast<int> (std::round (apvts.getRawParameterValue (paramFlavor)->load())));
    const auto& flavor = secretFlavorProfiles[static_cast<size_t> (flavorIndex)];
    const auto movementRate = driveDb;
    const auto movementDepth = juce::jlimit (0.0f, 1.0f, crush + flavor.depthBias * sauce);
    const auto chop = juce::jlimit (0.0f, 1.0f, wowDepth + flavor.chopBias * sauce);
    const auto stutter = juce::jlimit (0.0f, 1.0f, wowRate + flavor.stutterBias * sauce);
    const auto filter = juce::jlimit (0.0f, 1.0f, tone + flavor.filterBias * sauce);
    const auto width = juce::jlimit (0.0f, 1.0f, apvts.getRawParameterValue (paramWidth)->load() + flavor.widthBias * sauce);
    const auto freezeOn = apvts.getRawParameterValue (paramFreeze)->load() > 0.5f;
    const auto reverseOn = apvts.getRawParameterValue (paramReverseMomentary)->load() > 0.5f;
    const auto repeatOn = apvts.getRawParameterValue (paramRepeat)->load() > 0.5f;
    const auto dropoutOn = apvts.getRawParameterValue (paramDropout)->load() > 0.5f;
    const auto tapeStopOn = apvts.getRawParameterValue (paramTapeStop)->load() > 0.5f;
    const auto throwOn = apvts.getRawParameterValue (paramThrowFx)->load() > 0.5f;
    const auto outputGain = juce::Decibels::decibelsToGain (outputDb);
    const auto channelsToProcess = juce::jmin (bufferChannels, totalNumInputChannels, static_cast<int> (crushStates_.size()));
    const auto delayBufferSamples = secretDelayBuffer_.getNumSamples();
    if (delayBufferSamples < 2)
        return;

    double bpm = 120.0;
    double blockStartPpq = secretFallbackPpq_;

    if (auto* playHead = getPlayHead())
        if (const auto position = playHead->getPosition())
        {
            bpm = juce::jlimit (40.0, 240.0, position->getBpm().orFallback (bpm));

            if (const auto ppq = position->getPpqPosition())
                blockStartPpq = *ppq;
        }

    static constexpr std::array<double, 8> beatDivisions {{
        4.0,      // 1 bar
        2.0,      // 1/2
        1.0,      // 1/4
        0.5,      // 1/8
        1.0 / 3.0,// 1/8 triplet feel
        0.25,     // 1/16
        0.125,    // 1/32
        0.0625    // 1/64
    }};

    const auto baseDivisionIndex = juce::jlimit (0, static_cast<int> (beatDivisions.size()) - 1,
                                                 static_cast<int> (std::round (movementRate * static_cast<float> (beatDivisions.size() - 1))));
    const auto divisionIndex = juce::jlimit (0, static_cast<int> (beatDivisions.size()) - 1,
                                             baseDivisionIndex + flavor.divisionOffset);
    const auto movementDivision = beatDivisions[static_cast<size_t> (divisionIndex)];
    const auto samplesPerQuarter = sampleRate_ * 60.0 / bpm;
    const auto ppqPerSample = 1.0 / samplesPerQuarter;
    const auto repeatDivision = beatDivisions[static_cast<size_t> (juce::jlimit (2, 7, divisionIndex + 2))];
    const auto dropoutDivision = beatDivisions[static_cast<size_t> (juce::jlimit (2, 6, divisionIndex + 1))];
    const auto throwDivision = beatDivisions[static_cast<size_t> (juce::jlimit (1, 5, divisionIndex + (repeatOn ? 2 : 1)))];
    const auto delayWriteStart = secretDelayWritePosition_;
    const auto throwDelaySamples = juce::jlimit (1, delayBufferSamples - 1,
                                                 static_cast<int> (std::round (samplesPerQuarter * throwDivision)));
    const auto reverseWindowSamples = juce::jlimit (1, delayBufferSamples - 1,
                                                   static_cast<int> (std::round (samplesPerQuarter * juce::jlimit (0.125, 1.0, movementDivision * 2.0))));
    const auto holdDivision = freezeOn ? 0.25 : juce::jlimit (0.015625, 0.25, repeatDivision * (1.0 - static_cast<double> (stutter) * 0.78));
    const auto holdSamples = juce::jlimit (1, 8192, static_cast<int> (std::round (samplesPerQuarter * holdDivision)));
    const auto reverseMix = juce::jlimit (0.0f, 0.86f, (reverseOn ? 0.72f : 0.0f) + flavor.reverseAmount * sauce);
    const auto throwMix = juce::jlimit (0.0f, 0.78f, (throwOn ? 0.46f : 0.0f) + flavor.throwAmount * sauce);
    const auto tapeAmount = juce::jlimit (0.0f, 1.0f, (tapeStopOn ? 1.0f : 0.0f) + flavor.tapeDarken * sauce);
    const auto tapeDipAmount = juce::jlimit (0.0f, 1.0f, (tapeStopOn ? 1.0f : 0.0f) + flavor.tapeDip * sauce);
    const auto saturationDrive = 0.55f + flavor.saturationDrive;
    const auto wrapUnit = [] (double value)
    {
        return static_cast<float> (value - std::floor (value));
    };

    for (int ch = 0; ch < channelsToProcess; ++ch)
    {
        auto* data = buffer.getWritePointer (ch);
        auto* delayData = secretDelayBuffer_.getWritePointer (ch);
        auto& holdState = crushStates_[static_cast<size_t> (ch)];
        auto& filterState = toneState_[static_cast<size_t> (ch)];
        auto& gateState = secretGateState_[static_cast<size_t> (ch)];
        auto& reverseMixState = secretReverseMixState_[static_cast<size_t> (ch)];
        auto& throwMixState = secretThrowMixState_[static_cast<size_t> (ch)];
        auto& tapeAmountState = secretTapeAmountState_[static_cast<size_t> (ch)];
        auto& tapeDipState = secretTapeDipState_[static_cast<size_t> (ch)];

        for (int n = 0; n < numSamples; ++n)
        {
            const auto dry = data[n];
            const auto samplePpq = blockStartPpq + static_cast<double> (n) * ppqPerSample;
            const auto movementPosition = wrapUnit (samplePpq / movementDivision);
            const auto repeatPosition = wrapUnit (samplePpq / repeatDivision);
            const auto dropoutPosition = wrapUnit (samplePpq / dropoutDivision);
            const auto lfoPhase = 2.0f * juce::MathConstants<float>::pi * movementPosition + (ch == 1 ? 0.37f : 0.0f);
            const auto lfo = 0.5f - 0.5f * std::cos (lfoPhase);
            const auto fasterLfo = 0.5f - 0.5f * std::cos (2.0f * juce::MathConstants<float>::pi * repeatPosition);
            const auto writePosition = (delayWriteStart + n) % delayBufferSamples;
            const auto throwReadPosition = (writePosition + delayBufferSamples - throwDelaySamples) % delayBufferSamples;
            const auto reverseReadPosition = (writePosition + delayBufferSamples - 1 - (n % reverseWindowSamples)) % delayBufferSamples;
            const auto throwSample = delayData[throwReadPosition];
            const auto reverseSample = delayData[reverseReadPosition];

            const auto chopThreshold = juce::jmap (chop, 0.08f, 0.72f);
            const auto chopOpen = smoothStep (chopThreshold - 0.12f, chopThreshold + 0.12f, fasterLfo);
            const auto chopGate = juce::jmap (chopOpen, 1.0f - chop * sauce * flavor.gateDepth, 1.0f);
            const auto dropoutStart = juce::jlimit (0.36f, 0.82f, flavor.dropoutStart - chop * sauce * 0.12f);
            const auto dropoutEdge = smoothStep (dropoutStart, juce::jmin (0.98f, dropoutStart + 0.12f), dropoutPosition);
            const auto dropoutGate = dropoutOn ? (1.0f - dropoutEdge) : 1.0f;
            smoothToward (gateState, chopGate * dropoutGate, 0.035f);
            const auto movementGain = 1.0f - sauce * movementDepth * 0.56f * lfo;

            if ((holdState.phase % holdSamples) == 0)
                holdState.heldSample = dry;
            holdState.phase = (holdState.phase + 1) % holdSamples;

            auto x = juce::jmap (juce::jlimit (0.0f, 1.0f, stutter * sauce + (repeatOn ? 0.35f : 0.0f)), dry, holdState.heldSample);

            smoothToward (reverseMixState, reverseMix, 0.018f);
            if (reverseMixState > 0.001f)
                x = juce::jmap (reverseMixState, x, reverseSample);

            x *= movementGain * gateState;

            const auto movingFilter = juce::jlimit (0.0f, 1.0f, filter + (lfo - 0.5f) * movementDepth * sauce * 0.36f);
            const auto tapeStopPosition = wrapUnit (samplePpq);
            const auto tapeMotion = 0.5f - 0.5f * std::cos (2.0f * juce::MathConstants<float>::pi * tapeStopPosition);
            const auto tapeStopCurve = tapeStopOn ? (1.0f - tapeStopPosition) : (1.0f - 0.36f * tapeMotion);
            smoothToward (tapeAmountState, tapeAmount, 0.012f);
            smoothToward (tapeDipState, tapeDipAmount, 0.012f);
            const auto tapeToneScale = 1.0f - tapeAmountState * (tapeStopOn ? 0.82f * tapeStopPosition : 0.42f * tapeMotion);
            const auto cutoffHz = juce::jmap (movingFilter * juce::jlimit (0.12f, 1.0f, tapeToneScale), 250.0f, 17000.0f);
            const auto lpCoeff = std::exp (-2.0f * juce::MathConstants<float>::pi * cutoffHz / static_cast<float> (sampleRate_));
            filterState = (1.0f - lpCoeff) * x + lpCoeff * filterState;

            auto saturated = std::tanh (filterState * (1.0f + sauce * saturationDrive));
            smoothToward (throwMixState, throwMix, 0.014f);
            if (throwMixState > 0.001f)
                saturated = juce::jlimit (-1.0f, 1.0f, saturated + throwSample * throwMixState);

            auto out = (dry * (1.0f - mix) + saturated * mix) * outputGain;
            if (tapeDipState > 0.001f)
                out *= 1.0f - tapeDipState * (1.0f - (0.48f + 0.52f * tapeStopCurve));

            out = std::tanh (out * 1.35f) / std::tanh (1.35f);
            data[n] = juce::jlimit (-1.0f, 1.0f, out);

            delayData[writePosition] = juce::jlimit (-1.0f, 1.0f, out + throwSample * (throwMixState > 0.001f ? 0.42f : 0.18f));
        }
    }

    if (bufferChannels >= 2 && totalNumInputChannels >= 2)
    {
        auto* left = buffer.getWritePointer (0);
        auto* right = buffer.getWritePointer (1);
        const auto sideGain = juce::jmap (width, 0.55f, 1.65f);

        for (int n = 0; n < numSamples; ++n)
        {
            const auto mid = 0.5f * (left[n] + right[n]);
            const auto side = 0.5f * (left[n] - right[n]) * sideGain;
            left[n] = juce::jlimit (-1.0f, 1.0f, mid + side);
            right[n] = juce::jlimit (-1.0f, 1.0f, mid - side);
        }
    }

    secretDelayWritePosition_ = (delayWriteStart + numSamples) % delayBufferSamples;
    secretFallbackPpq_ = blockStartPpq + static_cast<double> (numSamples) * ppqPerSample;
    return;
#else
    const auto driveGain = juce::Decibels::decibelsToGain (driveDb);
    const auto outputGain = juce::Decibels::decibelsToGain (outputDb);
    const auto driveComp = juce::Decibels::decibelsToGain (-0.35f * driveDb * mix);
    const auto bits = juce::jlimit (4, 16, static_cast<int> (std::round (16.0f - crush * 12.0f)));
    const auto quantLevels = static_cast<float> (1 << bits);
    const auto downsampleFactor = juce::jlimit (1, 24, static_cast<int> (std::round (1.0f + crush * 23.0f)));

    const auto cutoffHz = juce::jmap (tone, 800.0f, 16000.0f);
    const auto lpCoeff = std::exp (-2.0f * juce::MathConstants<float>::pi * cutoffHz / static_cast<float> (sampleRate_));

    const auto wowAmount = wowDepth * 0.2f;
    const auto phaseInc = 2.0f * juce::MathConstants<float>::pi * wowRate / static_cast<float> (sampleRate_);

    const auto channelsToProcess = juce::jmin (bufferChannels, totalNumInputChannels, static_cast<int> (crushStates_.size()));

    for (int ch = 0; ch < channelsToProcess; ++ch)
    {
        auto* data = buffer.getWritePointer (ch);
        auto& crushState = crushStates_[static_cast<size_t> (ch)];
        auto& toneState = toneState_[static_cast<size_t> (ch)];
        auto& wowPhase = wowPhase_[static_cast<size_t> (ch)];

        for (int n = 0; n < numSamples; ++n)
        {
            const auto dry = data[n];

            auto x = std::tanh (dry * driveGain);

            if ((crushState.phase % downsampleFactor) == 0)
            {
                const auto q = std::round (x * quantLevels) / quantLevels;
                crushState.heldSample = juce::jlimit (-1.0f, 1.0f, q);
            }

            crushState.phase = (crushState.phase + 1) % downsampleFactor;
            x = crushState.heldSample;

            const auto wowLfo = std::sin (wowPhase);
            wowPhase += phaseInc;
            if (wowPhase > 2.0f * juce::MathConstants<float>::pi)
                wowPhase -= 2.0f * juce::MathConstants<float>::pi;

            x *= 1.0f - wowAmount + (wowAmount * (0.5f + 0.5f * wowLfo));

            toneState = (1.0f - lpCoeff) * x + lpCoeff * toneState;
            const auto processed = toneState;

            auto out = (dry * (1.0f - mix) + processed * mix) * driveComp * outputGain;
            // A simple soft output limiter to avoid harsh level jumps.
            out = std::tanh (out * 1.6f) / std::tanh (1.6f);
            data[n] = juce::jlimit (-1.0f, 1.0f, out);
        }
    }
#endif
}

juce::AudioProcessorEditor* SauceBoxAudioProcessor::createEditor()
{
    return new SauceBoxAudioProcessorEditor (*this);
}

bool SauceBoxAudioProcessor::hasEditor() const
{
    return true;
}

const juce::String SauceBoxAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

juce::VST3ClientExtensions* SauceBoxAudioProcessor::getVST3ClientExtensions()
{
    return this;
}

std::vector<juce::String> SauceBoxAudioProcessor::getCompatibleClasses() const
{
    // Legacy Sauce Box VST3 processor/controller IDs retained after the Hot Packet display rename.
   #if defined (SAUCE_PRODUCT_SECRET_SAUCE)
    return {};
   #else
    return { "56535453426F78736175636520626F",
             "56534553426F78736175636520626F" };
   #endif
}

bool SauceBoxAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SauceBoxAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SauceBoxAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SauceBoxAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SauceBoxAudioProcessor::getNumPrograms()
{
    return 1;
}

int SauceBoxAudioProcessor::getCurrentProgram()
{
    return 0;
}

int SauceBoxAudioProcessor::getCurrentProgramForUi() const
{
    return currentProgram_;
}

int SauceBoxAudioProcessor::getPresetIndexFromCurrentParamsForUi() const
{
    return findPresetIndexFromCurrentParams();
}

void SauceBoxAudioProcessor::setCurrentProgram (int index)
{
    juce::ignoreUnused (index);
}

int SauceBoxAudioProcessor::getPresetCount() const
{
    return static_cast<int> (presets.size());
}

juce::String SauceBoxAudioProcessor::getPresetName (int index) const
{
    if (index < 0 || index >= static_cast<int> (presets.size()))
        return {};

    return presets[static_cast<size_t> (index)].name;
}

float SauceBoxAudioProcessor::getPresetInstantSauceValueForUi (int index) const
{
    if (index < 0 || index >= static_cast<int> (presets.size()))
        return 50.0f;

    return presets[static_cast<size_t> (index)].instantSauce;
}

void SauceBoxAudioProcessor::setCurrentProgramForUi (int index)
{
    const auto bounded = juce::jlimit (0, static_cast<int> (presets.size()) - 1, index);
    currentProgram_ = bounded;
    applyPreset (presets[static_cast<size_t> (bounded)]);
    sendChangeMessage();
}

const juce::String SauceBoxAudioProcessor::getProgramName (int index)
{
    juce::ignoreUnused (index);
    return active_product::manifest.productName;
}

void SauceBoxAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused (index, newName);
}

void SauceBoxAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    state.setProperty (stateProgramIndex, findPresetIndexFromCurrentParams(), nullptr);

    if (const auto xml = state.createXml())
        copyXmlToBinary (*xml, destData);
}

void SauceBoxAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    if (const auto xml = getXmlFromBinary (data, sizeInBytes))
        if (xml->hasTagName (apvts.state.getType()))
        {
            const auto loadedState = juce::ValueTree::fromXml (*xml);
            const auto loadedProgramIndex = static_cast<int> (loadedState.getProperty (stateProgramIndex, -999));

            apvts.replaceState (loadedState);

            const auto matchedIndex = findPresetIndexFromCurrentParams();
            if (matchedIndex >= 0)
                currentProgram_ = matchedIndex;
            else if (loadedProgramIndex == -1)
                currentProgram_ = -1;
            else
                currentProgram_ = matchedIndex;

            sendChangeMessage();
        }
}

SauceBoxAudioProcessor::APVTS::ParameterLayout SauceBoxAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

#if defined (SAUCE_PRODUCT_SECRET_SAUCE)
    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { paramInstantSauce, 1 }, "Sauce",
        juce::NormalisableRange<float> (0.0f, 100.0f, 0.1f), 50.0f));

    params.push_back (std::make_unique<juce::AudioParameterChoice> (
        juce::ParameterID { paramFlavor, 1 }, "Flavor",
        juce::StringArray { "Self Sample", "Vocal Chop", "Reverse Pull", "Stutter Step",
                            "Tape Wobble", "Dirty Dream", "Drip Throw", "Half-Time Melt",
                            "Formant Ghost", "Hook Maker", "Dark R&B", "Trap Motion" },
        0));

    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { paramDrive, 1 }, "Movement Rate", juce::NormalisableRange<float> (0.0f, 1.0f, 0.001f), 0.34f));

    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { paramCrush, 1 }, "Movement Depth", juce::NormalisableRange<float> (0.0f, 1.0f, 0.001f), 0.42f));

    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { paramWowDepth, 1 }, "Chop", juce::NormalisableRange<float> (0.0f, 1.0f, 0.001f), 0.12f));

    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { paramWowRate, 1 }, "Stutter", juce::NormalisableRange<float> (0.0f, 1.0f, 0.001f), 0.08f));

    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { paramTone, 1 }, "Filter", juce::NormalisableRange<float> (0.0f, 1.0f, 0.001f), 0.58f));

    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { paramWidth, 1 }, "Width", juce::NormalisableRange<float> (0.0f, 1.0f, 0.001f), 0.62f));

    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { paramMix, 1 }, "Mix", juce::NormalisableRange<float> (0.0f, 1.0f, 0.001f), 0.64f));

    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { paramOutput, 1 }, "Output", juce::NormalisableRange<float> (-18.0f, 12.0f, 0.1f), -1.0f));

    params.push_back (std::make_unique<juce::AudioParameterBool> (
        juce::ParameterID { paramFreeze, 1 }, "Freeze", false));

    params.push_back (std::make_unique<juce::AudioParameterBool> (
        juce::ParameterID { paramReverseMomentary, 1 }, "Reverse", false));

    params.push_back (std::make_unique<juce::AudioParameterBool> (
        juce::ParameterID { paramRepeat, 1 }, "Repeat", false));

    params.push_back (std::make_unique<juce::AudioParameterBool> (
        juce::ParameterID { paramDropout, 1 }, "Dropout", false));

    params.push_back (std::make_unique<juce::AudioParameterBool> (
        juce::ParameterID { paramTapeStop, 1 }, "Tape Stop", false));

    params.push_back (std::make_unique<juce::AudioParameterBool> (
        juce::ParameterID { paramThrowFx, 1 }, "Throw", false));
#else
    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { paramDrive, 1 }, "Drive", juce::NormalisableRange<float> (0.0f, 30.0f, 0.1f), 10.0f));

    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { paramCrush, 1 }, "Crush", juce::NormalisableRange<float> (0.0f, 1.0f, 0.001f), 0.22f));

    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { paramWowDepth, 1 }, "Wow Depth", juce::NormalisableRange<float> (0.0f, 1.0f, 0.001f), 0.20f));

    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { paramWowRate, 1 }, "Wow Rate", juce::NormalisableRange<float> (0.1f, 8.0f, 0.001f), 1.10f));

    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { paramTone, 1 }, "Tone", juce::NormalisableRange<float> (0.0f, 1.0f, 0.001f), 0.58f));

    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { paramMix, 1 }, "Mix", juce::NormalisableRange<float> (0.0f, 1.0f, 0.001f), 0.62f));

    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { paramOutput, 1 }, "Output", juce::NormalisableRange<float> (-18.0f, 12.0f, 0.1f), -1.5f));

    params.push_back (std::make_unique<juce::AudioParameterFloat> (
        juce::ParameterID { paramInstantSauce, 1 }, "Instant Sauce",
        juce::NormalisableRange<float> (0.0f, 100.0f, 0.1f), 50.0f));
#endif

    return { params.begin(), params.end() };
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SauceBoxAudioProcessor();
}
