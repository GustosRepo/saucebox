#pragma once

#include <JuceHeader.h>

class SauceBoxAudioProcessor : public juce::AudioProcessor,
                               public juce::ChangeBroadcaster,
                               private juce::VST3ClientExtensions
{
public:
    SauceBoxAudioProcessor();
    ~SauceBoxAudioProcessor() override = default;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    int getPresetCount() const;
    juce::String getPresetName (int index) const;
    float getPresetInstantSauceValueForUi (int index) const;
    int getCurrentProgramForUi() const;
    int getPresetIndexFromCurrentParamsForUi() const;
    void setCurrentProgramForUi (int index);

    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::VST3ClientExtensions* getVST3ClientExtensions() override;
    std::vector<juce::String> getCompatibleClasses() const override;

    using APVTS = juce::AudioProcessorValueTreeState;
    APVTS apvts;

    struct Preset
    {
        const char* name = "";
        float drive = 10.0f;
        float texture = 0.22f;
        float wowDepth = 0.20f;
        float wowRate = 1.10f;
        float tone = 0.58f;
        float mix = 0.62f;
        float output = -1.5f;
        float instantSauce = 50.0f;
    };

    static APVTS::ParameterLayout createParameterLayout();

private:
    struct CrushState
    {
        int phase = 0;
        float heldSample = 0.0f;
    };

    std::array<CrushState, 2> crushStates_;
    std::array<float, 2> toneState_ { 0.0f, 0.0f };
    std::array<float, 2> wowPhase_  { 0.0f, 0.0f };

    double sampleRate_ = 44100.0;
    bool isPrepared_ = false;
    int currentProgram_ = 0;

    void applyPreset (const Preset& preset);
    int findPresetIndexFromCurrentParams() const;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SauceBoxAudioProcessor)
};
