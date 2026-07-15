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
constexpr auto paramInstantSauce = "instantSauce";
constexpr auto trackReviewUrl = "https://saucebox.audio/review";
}

SauceBoxAudioProcessorEditor::SauceBoxAudioProcessorEditor (SauceBoxAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    setSize (640, 480);
    processorRef.addChangeListener (this);

    // ---- Header ----
    titleLabel.setText ("SAUCE BOX", juce::dontSendNotification);
    titleLabel.setJustificationType (juce::Justification::centred);
    titleLabel.setFont (juce::FontOptions (48.0f, juce::Font::bold));
    titleLabel.setColour (juce::Label::textColourId, juce::Colours::white);
    addAndMakeVisible (titleLabel);

    bylineLabel.setText ("FIRE", juce::dontSendNotification);
    bylineLabel.setJustificationType (juce::Justification::centred);
    bylineLabel.setColour (juce::Label::textColourId, juce::Colour::fromRGB (255, 140, 0));
    bylineLabel.setFont (juce::FontOptions (24.0f, juce::Font::bold));
    addAndMakeVisible (bylineLabel);

    // ---- Preset row ----
    presetLabel.setText ("Preset", juce::dontSendNotification);
    presetLabel.setJustificationType (juce::Justification::centredLeft);
    presetLabel.setColour (juce::Label::textColourId, juce::Colours::white);
    presetLabel.setFont (juce::FontOptions (14.0f, juce::Font::bold));
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

    // ---- Footer CTA ----
    ctaLabel.setText ("Get Your Track Pro-Ready", juce::dontSendNotification);
    ctaLabel.setJustificationType (juce::Justification::centredRight);
    ctaLabel.setColour (juce::Label::textColourId, juce::Colours::white);
    ctaLabel.setFont (juce::FontOptions (13.0f, juce::Font::bold));
    addAndMakeVisible (ctaLabel);

    ctaButton.setButtonText ("Free Review");
    ctaButton.setColour (juce::TextButton::buttonColourId, juce::Colour::fromRGB (255, 140, 0));
    ctaButton.setColour (juce::TextButton::buttonOnColourId, juce::Colour::fromRGB (255, 160, 30));
    ctaButton.setColour (juce::TextButton::textColourOffId, juce::Colour::fromRGB (40, 20, 10));
    ctaButton.onClick = [] { juce::URL (trackReviewUrl).launchInDefaultBrowser(); };
    addAndMakeVisible (ctaButton);

    // ---- Instant Sauce macro knob (Free) ----
    instantSauceSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    instantSauceSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 22);
    instantSauceSlider.setName ("Instant Sauce");
    instantSauceLabelKnob.setText ("HEAT LEVEL", juce::dontSendNotification);
    instantSauceLabelKnob.setJustificationType (juce::Justification::centred);
    instantSauceLabelKnob.setColour (juce::Label::textColourId, juce::Colours::white);
    instantSauceLabelKnob.setFont (juce::FontOptions (18.0f, juce::Font::bold));
    addAndMakeVisible (instantSauceSlider);
    addAndMakeVisible (instantSauceLabelKnob);

    attachments.emplace_back (std::make_unique<SliderAttachment> (processorRef.apvts, paramInstantSauce, instantSauceSlider));

    instantSauceSlider.onValueChange = [this]
    {
        applyInstantSauceMacro (static_cast<float> (instantSauceSlider.getValue()));
        refreshPresetDropdownFromParams();
    };

    // ---- Free controls: Mix + Output ----
    setupKnob (mixSlider, mixKnobLabel, "Mix");
    setupKnob (outputSlider, outputKnobLabel, "Output");

    attachments.emplace_back (std::make_unique<SliderAttachment> (processorRef.apvts, paramMix, mixSlider));
    attachments.emplace_back (std::make_unique<SliderAttachment> (processorRef.apvts, paramOutput, outputSlider));

    mixSlider.onValueChange = [this] { refreshPresetDropdownFromParams(); };
    outputSlider.onValueChange = [this] { refreshPresetDropdownFromParams(); };

    // ---- Pro-locked controls (shown dimmed, non-interactive) ----
    setupKnob (driveSlider, driveKnobLabel, "Drive");
    setupKnob (crushSlider, textureKnobLabel, "Texture");
    setupKnob (wowDepthSlider, wowDepthKnobLabel, "Wow Depth");
    setupKnob (wowRateSlider, wowRateKnobLabel, "Wow Rate");
    setupKnob (toneSlider, toneKnobLabel, "Tone");

    attachments.emplace_back (std::make_unique<SliderAttachment> (processorRef.apvts, paramDrive, driveSlider));
    attachments.emplace_back (std::make_unique<SliderAttachment> (processorRef.apvts, paramCrush, crushSlider));
    attachments.emplace_back (std::make_unique<SliderAttachment> (processorRef.apvts, paramWowDepth, wowDepthSlider));
    attachments.emplace_back (std::make_unique<SliderAttachment> (processorRef.apvts, paramWowRate, wowRateSlider));
    attachments.emplace_back (std::make_unique<SliderAttachment> (processorRef.apvts, paramTone, toneSlider));

    // Lock the pro controls — non-interactive, purely visual
    for (auto* comp : { static_cast<juce::Component*> (&driveSlider),
                        static_cast<juce::Component*> (&crushSlider),
                        static_cast<juce::Component*> (&wowDepthSlider),
                        static_cast<juce::Component*> (&wowRateSlider),
                        static_cast<juce::Component*> (&toneSlider),
                        static_cast<juce::Component*> (&driveKnobLabel),
                        static_cast<juce::Component*> (&textureKnobLabel),
                        static_cast<juce::Component*> (&wowDepthKnobLabel),
                        static_cast<juce::Component*> (&wowRateKnobLabel),
                        static_cast<juce::Component*> (&toneKnobLabel) })
    {
        comp->setEnabled (false);
        comp->setInterceptsMouseClicks (false, false);
    }

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
    // Fire sauce packet: vibrant red/dark red gradient
    const auto fireRed = juce::Colour::fromRGB (220, 20, 60);       // Crimson
    const auto darkRed = juce::Colour::fromRGB (139, 0, 0);         // Dark red
    const auto charcoal = juce::Colour::fromRGB (30, 25, 20);       // Dark packet bottom
    const auto accentOrange = juce::Colour::fromRGB (255, 140, 0);  // Orange trim

    // Main packet gradient: Fire red top → dark red bottom
    juce::ColourGradient grad (fireRed, 0.0f, 0.0f,
                               darkRed, 0.0f, static_cast<float> (getHeight()), false);
    g.setGradientFill (grad);
    g.fillRoundedRectangle (getLocalBounds().toFloat().reduced (8.0f), 12.0f);

    // Packet border: thin orange line
    g.setColour (accentOrange.withAlpha (0.8f));
    g.drawRoundedRectangle (getLocalBounds().toFloat().reduced (8.0f), 12.0f, 2.5f);

    // Tear-here line (horizontal line 1/3 down)
    const auto teary = static_cast<float> (getHeight()) / 4.5f;
    g.setColour (charcoal.withAlpha (0.6f));
    g.drawLine (20.0f, teary, static_cast<float> (getWidth()) - 20.0f, teary, 2.0f);

    // Perforated dashes
    g.setColour (charcoal.withAlpha (0.4f));
    for (float x = 40.0f; x < static_cast<float> (getWidth()) - 40.0f; x += 20.0f)
    {
        g.fillRect (x, teary - 0.5f, 8.0f, 1.0f);
    }

    // Packet fold lines (subtle emboss effect on sides)
    g.setColour (juce::Colours::white.withAlpha (0.08f));
    g.drawLine (50.0f, teary + 20.0f, 50.0f, static_cast<float> (getHeight()) - 40.0f, 1.0f);
    g.drawLine (static_cast<float> (getWidth()) - 50.0f, teary + 20.0f,
                static_cast<float> (getWidth()) - 50.0f, static_cast<float> (getHeight()) - 40.0f, 1.0f);

    // Pro locked zone overlay (stays red-tinted for packet feel)
    if (! proRowBounds_.isEmpty())
    {
        const auto proRect = proRowBounds_.toFloat().expanded (6.0f, 2.0f);
        g.setColour (juce::Colour::fromRGBA (30, 10, 10, 180));  // Dark red overlay
        g.fillRoundedRectangle (proRect, 8.0f);

        g.setColour (accentOrange.withAlpha (0.35f));
        g.drawRoundedRectangle (proRect, 8.0f, 1.0f);

        g.setColour (juce::Colours::white.withAlpha (0.65f));
        g.setFont (juce::FontOptions (12.0f, juce::Font::bold));
        g.drawText ("🔒 PRO UNLOCK", proRect.toNearestInt(), juce::Justification::centred);
    }
}

void SauceBoxAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced (24);

    // Header: "SAUCE BOX" + "FIRE" (takes up more space now)
    auto header = area.removeFromTop (70);
    titleLabel.setBounds (header.removeFromTop (42));
    bylineLabel.setBounds (header);

    // Preset row
    auto presetRow = area.removeFromTop (32);
    presetLabel.setBounds (presetRow.removeFromLeft (54));
    presetBox.setBounds (presetRow.removeFromLeft (260).reduced (2));

    // Footer
    auto footer = area.removeFromBottom (40);
    ctaButton.setBounds (footer.removeFromRight (190).reduced (6));
    ctaLabel.setBounds (footer.reduced (6));

    // Remaining space: macro + free controls + pro row
    // Macro zone: Instant Sauce big knob, centered (~140px)
    auto macroZone = area.removeFromTop (150);
    {
        const int knobW = 200;
        auto knobArea = macroZone.withSizeKeepingCentre (knobW, macroZone.getHeight());
        instantSauceLabelKnob.setBounds (knobArea.removeFromTop (22));
        instantSauceSlider.setBounds (knobArea.reduced (6));
    }

    // Free controls row: Mix + Output, centered (~100px)
    auto freeRow = area.removeFromTop (110);
    {
        const int knobW = freeRow.getWidth() / 3;
        auto centredRow = freeRow.withSizeKeepingCentre (knobW * 2, freeRow.getHeight());

        const auto placeKnob = [] (juce::Slider& sl, juce::Label& lb, juce::Rectangle<int> cell)
        {
            lb.setBounds (cell.removeFromTop (20));
            sl.setBounds (cell.reduced (6));
        };

        placeKnob (mixSlider, mixKnobLabel, centredRow.removeFromLeft (knobW));
        placeKnob (outputSlider, outputKnobLabel, centredRow.removeFromLeft (knobW));
    }

    // Pro locked row: 5 knobs, full width, dimmed
    auto proRow = area;
    proRowBounds_ = proRow;

    {
        const int knobW = proRow.getWidth() / 5;
        const auto placeKnob = [] (juce::Slider& sl, juce::Label& lb, juce::Rectangle<int> cell)
        {
            lb.setBounds (cell.removeFromTop (18));
            sl.setBounds (cell.reduced (6));
        };

        placeKnob (driveSlider,    driveKnobLabel,    proRow.removeFromLeft (knobW));
        placeKnob (crushSlider,    textureKnobLabel,  proRow.removeFromLeft (knobW));
        placeKnob (wowDepthSlider, wowDepthKnobLabel, proRow.removeFromLeft (knobW));
        placeKnob (wowRateSlider,  wowRateKnobLabel,  proRow.removeFromLeft (knobW));
        placeKnob (toneSlider,     toneKnobLabel,     proRow.removeFromLeft (knobW));
    }
}

void SauceBoxAudioProcessorEditor::applyInstantSauceMacro (float value)
{
    // value is 0–100.  Sweet spot at 50 matches the "Instant Sauce" preset.
    // Clean end (0): subtle, barely touched.
    // Heavy end (100): thick lo-fi crunch.

    const float t = juce::jlimit (0.0f, 1.0f, value / 100.0f);

    const auto lerp2 = [] (float x, float lo, float mid, float hi) -> float
    {
        if (x <= 0.5f) return juce::jmap (x * 2.0f, lo, mid);
        return juce::jmap ((x - 0.5f) * 2.0f, mid, hi);
    };

    const float drive    = lerp2 (t,  3.0f, 10.0f, 22.0f);
    const float texture  = lerp2 (t,  0.04f, 0.22f, 0.62f);
    const float wowDepth = lerp2 (t,  0.02f, 0.20f, 0.42f);
    const float wowRate  = lerp2 (t,  0.50f, 1.10f, 2.80f);
    const float tone     = lerp2 (t,  0.78f, 0.58f, 0.36f);   // inverted: cleaner = brighter

    const auto setParam = [this] (const char* id, float val)
    {
        if (auto* p = processorRef.apvts.getParameter (id))
            p->setValueNotifyingHost (p->convertTo0to1 (val));
    };

    setParam (paramDrive,    drive);
    setParam (paramCrush,    texture);
    setParam (paramWowDepth, wowDepth);
    setParam (paramWowRate,  wowRate);
    setParam (paramTone,     tone);
}

void SauceBoxAudioProcessorEditor::setupKnob (juce::Slider& slider, juce::Label& label, const juce::String& labelText)
{
    slider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 64, 20);
    slider.setName (labelText);

    label.setText (labelText, juce::dontSendNotification);
    label.setJustificationType (juce::Justification::centred);
    label.setColour (juce::Label::textColourId, juce::Colours::white);
    label.setFont (juce::FontOptions (13.0f, juce::Font::bold));

    addAndMakeVisible (slider);
    addAndMakeVisible (label);
}
