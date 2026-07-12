#include "PluginProcessor.h"
#include "PluginEditor.h"

namespace
{
constexpr auto paramDrive = "drive";
constexpr auto paramCrush = "crush";
constexpr auto paramWowDepth = "wowDepth";
constexpr auto paramWowRate = "wowRate";
constexpr auto paramTone = "tone";
constexpr auto paramMix = "mix";
constexpr auto paramOutput = "output";
constexpr auto stateProgramIndex = "programIndex";

constexpr std::array<SauceBoxAudioProcessor::Preset, 12> presets {{
    { "Instant Sauce",      10.0f, 0.22f, 0.20f, 1.10f, 0.58f, 0.62f, -1.5f },
    { "Velvet Vocal",        8.0f, 0.12f, 0.08f, 0.75f, 0.68f, 0.48f, -1.0f },
    { "Crisp Vocal Edge",   14.0f, 0.18f, 0.06f, 1.30f, 0.74f, 0.44f, -2.0f },
    { "808 Glue Heat",      16.0f, 0.30f, 0.04f, 0.55f, 0.46f, 0.56f, -2.5f },
    { "Drum Bus Dirt",      12.0f, 0.36f, 0.10f, 1.80f, 0.52f, 0.50f, -2.0f },
    { "Drum Bus Crunch",    18.0f, 0.45f, 0.12f, 2.20f, 0.57f, 0.46f, -3.0f },
    { "Keys Warm Dust",      9.0f, 0.24f, 0.18f, 0.95f, 0.50f, 0.60f, -1.5f },
    { "Guitar Soft Bite",   13.0f, 0.20f, 0.14f, 1.60f, 0.63f, 0.54f, -1.8f },
    { "Lo-Fi Wash",         11.0f, 0.52f, 0.36f, 0.85f, 0.37f, 0.72f, -2.8f },
    { "Chorus Lift",         7.0f, 0.10f, 0.16f, 1.25f, 0.70f, 0.42f, -0.8f },
    { "Mix Bus Glue Lite",   6.0f, 0.08f, 0.05f, 0.65f, 0.64f, 0.36f, -0.5f },
    { "Night Tape Mood",    10.0f, 0.34f, 0.28f, 0.70f, 0.42f, 0.66f, -2.2f }
}};
}

SauceBoxAudioProcessor::SauceBoxAudioProcessor()
    : AudioProcessor (BusesProperties().withInput ("Input", juce::AudioChannelSet::stereo(), true)
                                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
      apvts (*this, nullptr, "PARAMS", createParameterLayout())
{
}

void SauceBoxAudioProcessor::applyPreset (const Preset& preset)
{
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

    const auto nearlyEqual = [] (float a, float b, float tolerance)
    {
        return std::abs (a - b) <= tolerance;
    };

    for (size_t i = 0; i < presets.size(); ++i)
    {
        const auto& p = presets[i];
        if (nearlyEqual (drive, p.drive, 0.11f)
            && nearlyEqual (texture, p.texture, 0.002f)
            && nearlyEqual (wowDepth, p.wowDepth, 0.002f)
            && nearlyEqual (wowRate, p.wowRate, 0.002f)
            && nearlyEqual (tone, p.tone, 0.002f)
            && nearlyEqual (mix, p.mix, 0.002f)
            && nearlyEqual (output, p.output, 0.11f))
            return static_cast<int> (i);
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
    return "Sauce Box";
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

    return { params.begin(), params.end() };
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SauceBoxAudioProcessor();
}
