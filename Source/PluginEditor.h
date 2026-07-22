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
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;

    class PacketLookAndFeel : public juce::LookAndFeel_V4
    {
    public:
        PacketLookAndFeel();

        void drawRotarySlider (juce::Graphics&, int x, int y, int width, int height,
                               float sliderPosProportional, float rotaryStartAngle,
                               float rotaryEndAngle, juce::Slider&) override;
        void drawComboBox (juce::Graphics&, int width, int height, bool isButtonDown,
                           int buttonX, int buttonY, int buttonW, int buttonH,
                           juce::ComboBox&) override;
        void positionComboBoxText (juce::ComboBox&, juce::Label&) override;
        void drawButtonBackground (juce::Graphics&, juce::Button&, const juce::Colour& backgroundColour,
                                   bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
        void drawButtonText (juce::Graphics&, juce::TextButton&,
                             bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
    };

    SauceBoxAudioProcessor& processorRef;
    PacketLookAndFeel packetLookAndFeel;
    juce::TooltipWindow tooltipWindow;

    juce::Label titleLabel;
    juce::Label bylineLabel;
    juce::Label presetLabel;
    juce::ComboBox presetBox;
    juce::Label ctaLabel;
    juce::TextButton ctaButton;
    juce::TextButton freezeButton;
    juce::TextButton reverseButton;
    juce::TextButton repeatButton;
    juce::TextButton dropoutButton;
    juce::TextButton tapeStopButton;
    juce::TextButton throwButton;

    juce::Slider driveSlider;
    juce::Slider crushSlider;
    juce::Slider wowDepthSlider;
    juce::Slider wowRateSlider;
    juce::Slider toneSlider;
    juce::Slider mixSlider;
    juce::Slider outputSlider;

    // Instant Sauce macro (Free tier)
    juce::Slider instantSauceSlider;
    juce::Label  instantSauceLabelKnob;

    // Pro-tier detailed controls (shown locked in Free)
    juce::Label driveKnobLabel;
    juce::Label textureKnobLabel;
    juce::Label wowDepthKnobLabel;
    juce::Label wowRateKnobLabel;
    juce::Label toneKnobLabel;
    juce::Label mixKnobLabel;
    juce::Label outputKnobLabel;

    juce::Rectangle<int> proRowBounds_;
    bool isUpdatingInstantSauceFromPreset_ = false;

    std::vector<std::unique_ptr<SliderAttachment>> attachments;
    std::vector<std::unique_ptr<ButtonAttachment>> buttonAttachments;

    void setupKnob (juce::Slider& slider, juce::Label& label, const juce::String& labelText);
    void setupPerformanceButton (juce::TextButton& button, const juce::String& labelText);
    void applyInstantSauceMacro (float value);
    void syncInstantSauceSliderFromPreset (int presetIndex);
    void refreshPresetDropdownFromParams();
    void changeListenerCallback (juce::ChangeBroadcaster* source) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SauceBoxAudioProcessorEditor)
};
