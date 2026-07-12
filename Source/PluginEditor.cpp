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
constexpr auto trackReviewUrl = "https://saucebox.audio/review";
}

SauceBoxAudioProcessorEditor::SauceBoxAudioProcessorEditor (SauceBoxAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    setSize (640, 420);
    processorRef.addChangeListener (this);

    titleLabel.setText ("SAUCE BOX", juce::dontSendNotification);
    titleLabel.setJustificationType (juce::Justification::centred);
    titleLabel.setFont (juce::FontOptions (34.0f, juce::Font::bold));
    addAndMakeVisible (titleLabel);

    bylineLabel.setText ("by 808Bytes", juce::dontSendNotification);
    bylineLabel.setJustificationType (juce::Justification::centred);
    bylineLabel.setColour (juce::Label::textColourId, juce::Colours::white.withAlpha (0.58f));
    bylineLabel.setFont (juce::FontOptions (13.0f));
    addAndMakeVisible (bylineLabel);

    presetLabel.setText ("Preset", juce::dontSendNotification);
    presetLabel.setJustificationType (juce::Justification::centredLeft);
    presetLabel.setColour (juce::Label::textColourId, juce::Colours::white.withAlpha (0.85f));
    presetLabel.setFont (juce::FontOptions (13.0f));
    addAndMakeVisible (presetLabel);

    presetBox.addItem ("Custom", 1);

    for (int i = 0; i < processorRef.getPresetCount(); ++i)
        presetBox.addItem (processorRef.getPresetName (i), i + 2);

    presetBox.onChange = [this]
    {
        const auto index = presetBox.getSelectedItemIndex();
        if (index > 0)
            processorRef.setCurrentProgramForUi (index - 1);
    };
    const auto programIndex = processorRef.getCurrentProgramForUi();
    presetBox.setSelectedItemIndex (programIndex >= 0 ? (programIndex + 1) : 0, juce::dontSendNotification);
    addAndMakeVisible (presetBox);

    ctaLabel.setText ("Need your track release-ready?", juce::dontSendNotification);
    ctaLabel.setJustificationType (juce::Justification::centredRight);
    ctaLabel.setColour (juce::Label::textColourId, juce::Colours::white.withAlpha (0.75f));
    ctaLabel.setFont (juce::FontOptions (14.0f));
    addAndMakeVisible (ctaLabel);

    ctaButton.setButtonText ("Free Track Review");
    ctaButton.setColour (juce::TextButton::buttonColourId, juce::Colour::fromRGB (236, 140, 58));
    ctaButton.setColour (juce::TextButton::buttonOnColourId, juce::Colour::fromRGB (250, 165, 92));
    ctaButton.setColour (juce::TextButton::textColourOffId, juce::Colour::fromRGB (30, 20, 14));
    ctaButton.onClick = [] { juce::URL (trackReviewUrl).launchInDefaultBrowser(); };
    addAndMakeVisible (ctaButton);

    setupKnob (driveSlider, driveKnobLabel, "Drive");
    setupKnob (crushSlider, textureKnobLabel, "Texture");
    setupKnob (wowDepthSlider, wowDepthKnobLabel, "Wow Depth");
    setupKnob (wowRateSlider, wowRateKnobLabel, "Wow Rate");
    setupKnob (toneSlider, toneKnobLabel, "Tone");
    setupKnob (mixSlider, mixKnobLabel, "Mix");
    setupKnob (outputSlider, outputKnobLabel, "Output");

    attachments.emplace_back (std::make_unique<SliderAttachment> (processorRef.apvts, paramDrive, driveSlider));
    attachments.emplace_back (std::make_unique<SliderAttachment> (processorRef.apvts, paramCrush, crushSlider));
    attachments.emplace_back (std::make_unique<SliderAttachment> (processorRef.apvts, paramWowDepth, wowDepthSlider));
    attachments.emplace_back (std::make_unique<SliderAttachment> (processorRef.apvts, paramWowRate, wowRateSlider));
    attachments.emplace_back (std::make_unique<SliderAttachment> (processorRef.apvts, paramTone, toneSlider));
    attachments.emplace_back (std::make_unique<SliderAttachment> (processorRef.apvts, paramMix, mixSlider));
    attachments.emplace_back (std::make_unique<SliderAttachment> (processorRef.apvts, paramOutput, outputSlider));

    const auto bindPresetRefresh = [this] (juce::Slider& slider)
    {
        slider.onValueChange = [this]
        {
            refreshPresetDropdownFromParams();
        };
    };

    bindPresetRefresh (driveSlider);
    bindPresetRefresh (crushSlider);
    bindPresetRefresh (wowDepthSlider);
    bindPresetRefresh (wowRateSlider);
    bindPresetRefresh (toneSlider);
    bindPresetRefresh (mixSlider);
    bindPresetRefresh (outputSlider);

    refreshPresetDropdownFromParams();
}

SauceBoxAudioProcessorEditor::~SauceBoxAudioProcessorEditor()
{
    processorRef.removeChangeListener (this);
}

void SauceBoxAudioProcessorEditor::changeListenerCallback (juce::ChangeBroadcaster* source)
{
    if (source != &processorRef)
        return;

    refreshPresetDropdownFromParams();
}

void SauceBoxAudioProcessorEditor::refreshPresetDropdownFromParams()
{
    const auto programIndex = processorRef.getPresetIndexFromCurrentParamsForUi();
    const auto uiIndex = programIndex >= 0 ? (programIndex + 1) : 0;

    if (presetBox.getSelectedItemIndex() != uiIndex)
        presetBox.setSelectedItemIndex (uiIndex, juce::dontSendNotification);
}

void SauceBoxAudioProcessorEditor::paint (juce::Graphics& g)
{
    auto bg = juce::Colour::fromRGB (22, 17, 12);
    auto accent = juce::Colour::fromRGB (236, 140, 58);

    g.fillAll (bg);

    juce::ColourGradient grad (juce::Colour::fromRGB (58, 34, 21), 0.0f, 0.0f,
                               juce::Colour::fromRGB (15, 12, 9), 0.0f, static_cast<float> (getHeight()), false);
    g.setGradientFill (grad);
    g.fillRoundedRectangle (getLocalBounds().toFloat().reduced (12.0f), 14.0f);

    g.setColour (accent.withAlpha (0.35f));
    g.drawRoundedRectangle (getLocalBounds().toFloat().reduced (12.0f), 14.0f, 2.0f);
}

void SauceBoxAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced (24);

    auto header = area.removeFromTop (56);
    titleLabel.setBounds (header.removeFromTop (36));
    bylineLabel.setBounds (header);

    auto presetRow = area.removeFromTop (30);
    presetLabel.setBounds (presetRow.removeFromLeft (54));
    presetBox.setBounds (presetRow.removeFromLeft (260).reduced (2));

    auto footer = area.removeFromBottom (40);
    ctaButton.setBounds (footer.removeFromRight (190).reduced (6));
    ctaLabel.setBounds (footer.reduced (6));

    auto topRow = area.removeFromTop (area.getHeight() / 2);
    auto bottomRow = area;

    const auto placeKnob = [] (juce::Slider& slider, juce::Label& label, juce::Rectangle<int> cell)
    {
        auto labelArea = cell.removeFromTop (18);
        label.setBounds (labelArea);
        slider.setBounds (cell.reduced (8));
    };

    const auto topW = topRow.getWidth() / 4;
    placeKnob (driveSlider, driveKnobLabel, topRow.removeFromLeft (topW));
    placeKnob (crushSlider, textureKnobLabel, topRow.removeFromLeft (topW));
    placeKnob (wowDepthSlider, wowDepthKnobLabel, topRow.removeFromLeft (topW));
    placeKnob (wowRateSlider, wowRateKnobLabel, topRow.removeFromLeft (topW));

    const auto bottomW = bottomRow.getWidth() / 3;
    placeKnob (toneSlider, toneKnobLabel, bottomRow.removeFromLeft (bottomW));
    placeKnob (mixSlider, mixKnobLabel, bottomRow.removeFromLeft (bottomW));
    placeKnob (outputSlider, outputKnobLabel, bottomRow.removeFromLeft (bottomW));
}

void SauceBoxAudioProcessorEditor::setupKnob (juce::Slider& slider, juce::Label& label, const juce::String& labelText)
{
    slider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 64, 20);
    slider.setName (labelText);

    label.setText (labelText, juce::dontSendNotification);
    label.setJustificationType (juce::Justification::centred);
    label.setColour (juce::Label::textColourId, juce::Colours::white.withAlpha (0.85f));
    label.setFont (juce::FontOptions (13.0f));

    addAndMakeVisible (slider);
    addAndMakeVisible (label);
}
