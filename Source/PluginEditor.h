#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class SauceBoxAudioProcessorEditor : public juce::AudioProcessorEditor
    , private juce::ChangeListener
{
public:
    explicit SauceBoxAudioProcessorEditor (SauceBoxAudioProcessor&);
    ~SauceBoxAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    SauceBoxAudioProcessor& processorRef;

    juce::Label titleLabel;
    juce::Label bylineLabel;
    juce::Label presetLabel;
    juce::ComboBox presetBox;
    juce::Label ctaLabel;
    juce::TextButton ctaButton;

    juce::Slider driveSlider;
    juce::Slider crushSlider;
    juce::Slider wowDepthSlider;
    juce::Slider wowRateSlider;
    juce::Slider toneSlider;
    juce::Slider mixSlider;
    juce::Slider outputSlider;

    juce::Label driveKnobLabel;
    juce::Label textureKnobLabel;
    juce::Label wowDepthKnobLabel;
    juce::Label wowRateKnobLabel;
    juce::Label toneKnobLabel;
    juce::Label mixKnobLabel;
    juce::Label outputKnobLabel;

    std::vector<std::unique_ptr<SliderAttachment>> attachments;

    void setupKnob (juce::Slider& slider, juce::Label& label, const juce::String& labelText);
    void refreshPresetDropdownFromParams();
    void changeListenerCallback (juce::ChangeBroadcaster* source) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SauceBoxAudioProcessorEditor)
};
