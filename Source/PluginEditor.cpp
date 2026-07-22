#include "PluginEditor.h"
#include "Products/HotPacket/HotPacketManifest.h"
#include "Products/HotPacket/HotPacketTheme.h"
#include "Products/ActiveProduct.h"

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
constexpr auto paramWidth = secret_sauce::parameters::width;
constexpr auto paramFreeze = secret_sauce::performance::freeze;
constexpr auto paramReverseMomentary = secret_sauce::performance::reverse;
constexpr auto paramRepeat = secret_sauce::performance::repeat;
constexpr auto paramDropout = secret_sauce::performance::dropout;
constexpr auto paramTapeStop = secret_sauce::performance::tapeStop;
constexpr auto paramThrowFx = secret_sauce::performance::throwFx;
#else
constexpr auto paramDrive = hot_packet::parameters::drive;
constexpr auto paramCrush = hot_packet::parameters::texture;
constexpr auto paramWowDepth = hot_packet::parameters::wowDepth;
constexpr auto paramWowRate = hot_packet::parameters::wowRate;
constexpr auto paramTone = hot_packet::parameters::tone;
constexpr auto paramMix = hot_packet::parameters::mix;
constexpr auto paramOutput = hot_packet::parameters::output;
constexpr auto paramInstantSauce = hot_packet::parameters::instantSauce;
#endif
constexpr auto trackReviewUrl = active_product::manifest.trackReviewUrl;

const auto& packetRed = active_product::theme::packetRed;
const auto& packetOrange = active_product::theme::packetOrange;
const auto& packetYellow = active_product::theme::packetYellow;
const auto& packetCream = active_product::theme::packetCream;
const auto& packetInk = active_product::theme::packetInk;
const auto& packetPurple = active_product::theme::packetPurple;

juce::Path createPacketPath (juce::Rectangle<float> r)
{
    juce::Path path;
    const auto corner = 28.0f;

    path.startNewSubPath (r.getX() + corner, r.getY());
    path.lineTo (r.getRight() - corner, r.getY());
    path.quadraticTo (r.getRight(), r.getY(), r.getRight(), r.getY() + corner);
    path.lineTo (r.getRight(), r.getBottom() - corner);
    path.quadraticTo (r.getRight(), r.getBottom(), r.getRight() - corner, r.getBottom());
    path.lineTo (r.getX() + corner, r.getBottom());
    path.quadraticTo (r.getX(), r.getBottom(), r.getX(), r.getBottom() - corner);
    path.lineTo (r.getX(), r.getY() + corner);
    path.quadraticTo (r.getX(), r.getY(), r.getX() + corner, r.getY());
    path.closeSubPath();

    return path;
}

void drawCrimpMarks (juce::Graphics& g, juce::Rectangle<float> bounds)
{
    for (float x = bounds.getX() + 12.0f; x < bounds.getRight() - 10.0f; x += 18.0f)
        g.drawLine (x, bounds.getY() + 5.0f, x + 8.0f, bounds.getBottom() - 5.0f, 1.7f);
}

void drawSideSealMarks (juce::Graphics& g, juce::Rectangle<float> packetBounds)
{
    for (float y = packetBounds.getY() + 54.0f; y < packetBounds.getBottom() - 54.0f; y += 18.0f)
    {
        g.drawLine (packetBounds.getX() + 4.0f, y, packetBounds.getX() + 24.0f, y + 7.0f, 1.4f);
        g.drawLine (packetBounds.getRight() - 4.0f, y, packetBounds.getRight() - 24.0f, y + 7.0f, 1.4f);
    }
}

void drawPacketCopy (juce::Graphics& g, juce::Rectangle<float> packetBounds)
{
    g.setColour (packetCream.withAlpha (0.88f));
    g.setFont (juce::FontOptions (25.0f, juce::Font::bold));
    g.drawText (active_product::theme::packetFlavor,
                juce::Rectangle<float> (packetBounds.getX() + 92.0f,
                                         packetBounds.getY() + 76.0f,
                                         74.0f, 30.0f).toNearestInt(),
                juce::Justification::centred);

    g.setColour (packetCream.withAlpha (0.18f));
    g.setFont (juce::FontOptions (72.0f, juce::Font::bold));
    g.drawText (active_product::theme::packetBackgroundWord,
                juce::Rectangle<float> (packetBounds.getRight() - 214.0f,
                                         packetBounds.getY() + 118.0f,
                                         170.0f, 78.0f).toNearestInt(),
                juce::Justification::centred);

    auto note = juce::Rectangle<float> (packetBounds.getRight() - 198.0f,
                                        packetBounds.getY() + 206.0f,
                                        126.0f, 54.0f);

    g.saveState();
    g.addTransform (juce::AffineTransform::rotation (-0.055f, note.getCentreX(), note.getCentreY()));

    juce::Path tail;
    tail.startNewSubPath (note.getX() + 30.0f, note.getBottom() - 2.0f);
    tail.lineTo (note.getX() + 43.0f, note.getBottom() + 10.0f);
    tail.lineTo (note.getX() + 54.0f, note.getBottom() - 2.0f);
    tail.closeSubPath();

    g.setColour (packetCream.withAlpha (0.76f));
    g.fillRoundedRectangle (note, 12.0f);
    g.fillPath (tail);

    g.setColour (packetInk.withAlpha (0.38f));
    g.drawRoundedRectangle (note, 12.0f, 1.0f);
    g.strokePath (tail, juce::PathStrokeType (1.0f));

    g.setColour (packetInk.withAlpha (0.82f));
    g.setFont (juce::FontOptions (13.0f, juce::Font::bold));
    g.drawFittedText (active_product::theme::packetNote, note.toNearestInt().reduced (10, 7),
                      juce::Justification::centred, 2);
    g.restoreState();

}
}

SauceBoxAudioProcessorEditor::PacketLookAndFeel::PacketLookAndFeel()
{
    setColour (juce::Slider::rotarySliderFillColourId, packetYellow);
    setColour (juce::Slider::rotarySliderOutlineColourId, packetInk.withAlpha (0.42f));
    setColour (juce::Slider::thumbColourId, packetCream);
    setColour (juce::Slider::textBoxTextColourId, packetCream);
    setColour (juce::Slider::textBoxBackgroundColourId, packetInk.withAlpha (0.72f));
    setColour (juce::Slider::textBoxOutlineColourId, packetCream.withAlpha (0.7f));

    setColour (juce::ComboBox::backgroundColourId, packetCream);
    setColour (juce::ComboBox::textColourId, packetInk);
    setColour (juce::ComboBox::outlineColourId, packetInk);
    setColour (juce::ComboBox::arrowColourId, packetRed);
    setColour (juce::PopupMenu::backgroundColourId, packetCream);
    setColour (juce::PopupMenu::textColourId, packetInk);
}

void SauceBoxAudioProcessorEditor::PacketLookAndFeel::drawRotarySlider (juce::Graphics& g,
                                                                        int x,
                                                                        int y,
                                                                        int width,
                                                                        int height,
                                                                        float sliderPosProportional,
                                                                        float rotaryStartAngle,
                                                                        float rotaryEndAngle,
                                                                        juce::Slider& slider)
{
    const auto enabledAlpha = slider.isEnabled() ? 1.0f : 0.36f;
    const auto bounds = juce::Rectangle<float> (static_cast<float> (x), static_cast<float> (y),
                                               static_cast<float> (width), static_cast<float> (height))
                            .reduced (7.0f);
    const auto diameter = juce::jmin (bounds.getWidth(), bounds.getHeight());
    const auto knobBounds = bounds.withSizeKeepingCentre (diameter, diameter);
    const auto centre = knobBounds.getCentre();
    const auto radius = diameter * 0.43f;
    const auto arcRadius = radius * 0.88f;
    const auto angle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);

    g.setColour (packetInk.withAlpha (0.28f * enabledAlpha));
    g.fillEllipse (knobBounds.translated (0.0f, 4.0f));

    g.setColour (packetCream.withAlpha (0.92f * enabledAlpha));
    g.fillEllipse (knobBounds.reduced (2.0f));

    g.setColour (packetRed.withAlpha (0.92f * enabledAlpha));
    g.fillEllipse (knobBounds.reduced (9.0f));

    g.setColour (packetInk.withAlpha (0.78f * enabledAlpha));
    g.drawEllipse (knobBounds.reduced (2.0f), 2.0f);

    juce::Path track;
    track.addCentredArc (centre.x, centre.y, arcRadius, arcRadius, 0.0f,
                         rotaryStartAngle, rotaryEndAngle, true);
    g.setColour (packetInk.withAlpha (0.42f * enabledAlpha));
    g.strokePath (track, juce::PathStrokeType (4.5f, juce::PathStrokeType::curved,
                                               juce::PathStrokeType::rounded));

    juce::Path valueTrack;
    valueTrack.addCentredArc (centre.x, centre.y, arcRadius, arcRadius, 0.0f,
                              rotaryStartAngle, angle, true);
    g.setColour (packetYellow.withAlpha (0.98f * enabledAlpha));
    g.strokePath (valueTrack, juce::PathStrokeType (7.0f, juce::PathStrokeType::curved,
                                                    juce::PathStrokeType::rounded));

    const auto pointerLength = radius * 0.66f;
    const auto pointerThickness = juce::jmax (3.0f, diameter * 0.06f);
    juce::Path pointer;
    pointer.addRoundedRectangle (-pointerThickness * 0.5f, -pointerLength,
                                 pointerThickness, pointerLength, pointerThickness * 0.5f);
    pointer.applyTransform (juce::AffineTransform::rotation (angle).translated (centre.x, centre.y));

    g.setColour (packetCream.withAlpha (0.96f * enabledAlpha));
    g.fillPath (pointer);
}

void SauceBoxAudioProcessorEditor::PacketLookAndFeel::drawComboBox (juce::Graphics& g,
                                                                    int width,
                                                                    int height,
                                                                    bool isButtonDown,
                                                                    int,
                                                                    int,
                                                                    int,
                                                                    int,
                                                                    juce::ComboBox&)
{
    auto bounds = juce::Rectangle<float> (0.5f, 0.5f,
                                          static_cast<float> (width) - 1.0f,
                                          static_cast<float> (height) - 1.0f);

    g.setColour ((isButtonDown ? packetYellow : packetCream).withAlpha (0.98f));
    g.fillRoundedRectangle (bounds, 9.0f);

    g.setColour (packetInk);
    g.drawRoundedRectangle (bounds, 9.0f, 2.0f);

    const auto arrowBounds = bounds.removeFromRight (34.0f).reduced (9.0f, 10.0f);
    juce::Path arrow;
    arrow.startNewSubPath (arrowBounds.getX(), arrowBounds.getY());
    arrow.lineTo (arrowBounds.getCentreX(), arrowBounds.getBottom());
    arrow.lineTo (arrowBounds.getRight(), arrowBounds.getY());

    g.setColour (packetRed);
    g.strokePath (arrow, juce::PathStrokeType (3.0f, juce::PathStrokeType::curved,
                                               juce::PathStrokeType::rounded));
}

void SauceBoxAudioProcessorEditor::PacketLookAndFeel::positionComboBoxText (juce::ComboBox& box,
                                                                           juce::Label& label)
{
    label.setBounds (8, 1, box.getWidth() - 40, box.getHeight() - 2);
    label.setFont (juce::FontOptions (18.0f, juce::Font::bold));
    label.setJustificationType (juce::Justification::centredLeft);
}

void SauceBoxAudioProcessorEditor::PacketLookAndFeel::drawButtonBackground (juce::Graphics& g,
                                                                           juce::Button& button,
                                                                           const juce::Colour&,
                                                                           bool isHighlighted,
                                                                           bool isDown)
{
    auto bounds = button.getLocalBounds().toFloat().reduced (0.5f);
    const auto fill = isDown ? packetYellow : (isHighlighted ? packetOrange.brighter (0.08f) : packetOrange);

    g.setColour (packetInk.withAlpha (0.32f));
    g.fillRoundedRectangle (bounds.translated (0.0f, 3.0f), 8.0f);

    g.setColour (fill);
    g.fillRoundedRectangle (bounds, 8.0f);

    g.setColour (packetCream);
    g.drawRoundedRectangle (bounds.reduced (2.0f), 6.0f, 1.1f);

    g.setColour (packetInk);
    g.drawRoundedRectangle (bounds, 8.0f, 1.6f);
}

void SauceBoxAudioProcessorEditor::PacketLookAndFeel::drawButtonText (juce::Graphics& g,
                                                                      juce::TextButton& button,
                                                                      bool,
                                                                      bool)
{
    g.setColour (packetInk);
    g.setFont (juce::FontOptions (15.0f, juce::Font::bold));
    g.drawFittedText (button.getButtonText(), button.getLocalBounds().reduced (8, 2),
                      juce::Justification::centred, 1);
}

SauceBoxAudioProcessorEditor::SauceBoxAudioProcessorEditor (SauceBoxAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p), tooltipWindow (this, 700)
{
    setSize (720, 560);
    setLookAndFeel (&packetLookAndFeel);
    processorRef.addChangeListener (this);

    // ---- Header ----
    titleLabel.setText (active_product::manifest.displayTitle, juce::dontSendNotification);
    titleLabel.setJustificationType (juce::Justification::centred);
    titleLabel.setFont (juce::FontOptions (54.0f, juce::Font::bold));
    titleLabel.setColour (juce::Label::textColourId, packetCream);
    addAndMakeVisible (titleLabel);

    bylineLabel.setText (active_product::theme::byline, juce::dontSendNotification);
    bylineLabel.setJustificationType (juce::Justification::centred);
    bylineLabel.setColour (juce::Label::textColourId, packetYellow);
    bylineLabel.setFont (juce::FontOptions (16.0f, juce::Font::bold));
    addAndMakeVisible (bylineLabel);

    // ---- Preset row ----
    presetLabel.setText (active_product::theme::presetLabel, juce::dontSendNotification);
    presetLabel.setJustificationType (juce::Justification::centredLeft);
    presetLabel.setColour (juce::Label::textColourId, packetCream);
    presetLabel.setFont (juce::FontOptions (15.0f, juce::Font::bold));
    addAndMakeVisible (presetLabel);

    presetBox.addItem ("Custom", 1);
    for (int i = 0; i < processorRef.getPresetCount(); ++i)
        presetBox.addItem (processorRef.getPresetName (i), i + 2);
    presetBox.setTooltip ("Choose a factory preset.");

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
    ctaLabel.setText (active_product::theme::ctaLabel, juce::dontSendNotification);
    ctaLabel.setJustificationType (juce::Justification::centredRight);
    ctaLabel.setColour (juce::Label::textColourId, packetCream);
    ctaLabel.setFont (juce::FontOptions (14.0f, juce::Font::bold));
    addAndMakeVisible (ctaLabel);

    ctaButton.setButtonText (active_product::theme::ctaButtonText);
    ctaButton.setColour (juce::TextButton::buttonColourId, packetOrange);
    ctaButton.setColour (juce::TextButton::buttonOnColourId, packetYellow);
    ctaButton.setColour (juce::TextButton::textColourOffId, packetInk);
    ctaButton.setTooltip ("Open the 808Bytes track review page.");
    ctaButton.onClick = [] { juce::URL (trackReviewUrl).launchInDefaultBrowser(); };
    addAndMakeVisible (ctaButton);

    // ---- Instant Sauce macro knob (Free) ----
    instantSauceSlider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    instantSauceSlider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 22);
    instantSauceSlider.setName (
       #if defined (SAUCE_PRODUCT_SECRET_SAUCE)
        "Sauce"
       #else
        "Instant Sauce"
       #endif
    );
    instantSauceSlider.setTooltip ("Controls the overall intensity of the effect.");
    instantSauceSlider.textFromValueFunction = [] (double value)
    {
        return juce::String (static_cast<int> (std::round (value))) + "%";
    };
    instantSauceSlider.valueFromTextFunction = [] (const juce::String& text)
    {
        return text.retainCharacters ("0123456789.-").getDoubleValue();
    };
    instantSauceLabelKnob.setText (
       #if defined (SAUCE_PRODUCT_SECRET_SAUCE)
        "Sauce"
       #else
        "Instant Sauce"
       #endif
        , juce::dontSendNotification);
    instantSauceLabelKnob.setJustificationType (juce::Justification::centred);
    instantSauceLabelKnob.setColour (juce::Label::textColourId, packetCream);
    instantSauceLabelKnob.setFont (juce::FontOptions (19.0f, juce::Font::bold));
    addAndMakeVisible (instantSauceSlider);
    addAndMakeVisible (instantSauceLabelKnob);

    attachments.emplace_back (std::make_unique<SliderAttachment> (processorRef.apvts, paramInstantSauce, instantSauceSlider));

    instantSauceSlider.onValueChange = [this]
    {
        if (isUpdatingInstantSauceFromPreset_)
            return;

        applyInstantSauceMacro (static_cast<float> (instantSauceSlider.getValue()));
        refreshPresetDropdownFromParams();
    };

    // ---- Free controls: Mix + Output ----
    setupKnob (mixSlider, mixKnobLabel, "Mix");
    setupKnob (outputSlider, outputKnobLabel, "Output");

    mixSlider.setTooltip ("Blends the processed signal with the dry signal.");
    mixSlider.textFromValueFunction = [] (double value)
    {
        return juce::String (static_cast<int> (std::round (value * 100.0))) + "%";
    };
    mixSlider.valueFromTextFunction = [] (const juce::String& text)
    {
        return juce::jlimit (0.0, 1.0, text.retainCharacters ("0123456789.-").getDoubleValue() / 100.0);
    };

    outputSlider.setTooltip ("Adjusts the final output level.");
    outputSlider.textFromValueFunction = [] (double value)
    {
        return juce::String (value, 1) + " dB";
    };
    outputSlider.valueFromTextFunction = [] (const juce::String& text)
    {
        return text.retainCharacters ("0123456789.-").getDoubleValue();
    };

    attachments.emplace_back (std::make_unique<SliderAttachment> (processorRef.apvts, paramMix, mixSlider));
    attachments.emplace_back (std::make_unique<SliderAttachment> (processorRef.apvts, paramOutput, outputSlider));

    mixSlider.onValueChange = [this] { refreshPresetDropdownFromParams(); };
    outputSlider.onValueChange = [this] { refreshPresetDropdownFromParams(); };

    // ---- Pro-locked controls (shown dimmed, non-interactive) ----
   #if defined (SAUCE_PRODUCT_SECRET_SAUCE)
    setupKnob (driveSlider, driveKnobLabel, "Rate");
    setupKnob (crushSlider, textureKnobLabel, "Depth");
    setupKnob (wowDepthSlider, wowDepthKnobLabel, "Chop");
    setupKnob (wowRateSlider, wowRateKnobLabel, "Stutter");
    setupKnob (toneSlider, toneKnobLabel, "Filter");

    driveSlider.setTooltip ("Controls movement speed. Available in Pro.");
    crushSlider.setTooltip ("Controls movement depth. Available in Pro.");
    wowDepthSlider.setTooltip ("Adds rhythmic chop gating. Available in Pro.");
    wowRateSlider.setTooltip ("Adds sample-hold repeat texture. Available in Pro.");
    toneSlider.setTooltip ("Controls moving filter brightness. Available in Pro.");
   #else
    setupKnob (driveSlider, driveKnobLabel, "Drive");
    setupKnob (crushSlider, textureKnobLabel, "Texture");
    setupKnob (wowDepthSlider, wowDepthKnobLabel, "Wow Depth");
    setupKnob (wowRateSlider, wowRateKnobLabel, "Wow Rate");
    setupKnob (toneSlider, toneKnobLabel, "Tone");

    driveSlider.setTooltip ("Adds saturation and harmonic intensity. Available in Pro.");
    crushSlider.setTooltip ("Adds crushed, degraded texture. Available in Pro.");
    wowDepthSlider.setTooltip ("Controls pitch modulation depth. Available in Pro.");
    wowRateSlider.setTooltip ("Controls pitch modulation speed. Available in Pro.");
    toneSlider.setTooltip ("Adjusts the brightness of the processed sound. Available in Pro.");
   #endif

    for (auto* slider : { &driveSlider, &crushSlider, &wowDepthSlider, &wowRateSlider, &toneSlider })
        slider->setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);

    attachments.emplace_back (std::make_unique<SliderAttachment> (processorRef.apvts, paramDrive, driveSlider));
    attachments.emplace_back (std::make_unique<SliderAttachment> (processorRef.apvts, paramCrush, crushSlider));
    attachments.emplace_back (std::make_unique<SliderAttachment> (processorRef.apvts, paramWowDepth, wowDepthSlider));
    attachments.emplace_back (std::make_unique<SliderAttachment> (processorRef.apvts, paramWowRate, wowRateSlider));
    attachments.emplace_back (std::make_unique<SliderAttachment> (processorRef.apvts, paramTone, toneSlider));

    // Lock the pro controls: non-interactive, purely visual.
    for (auto* comp : { static_cast<juce::Component*> (&driveSlider),
                        static_cast<juce::Component*> (&crushSlider),
                        static_cast<juce::Component*> (&wowDepthSlider),
                        static_cast<juce::Component*> (&wowRateSlider),
                        static_cast<juce::Component*> (&toneSlider) })
    {
        comp->setEnabled (false);
        comp->setInterceptsMouseClicks (false, false);
    }

    for (auto* label : { &driveKnobLabel, &textureKnobLabel, &wowDepthKnobLabel, &wowRateKnobLabel, &toneKnobLabel })
    {
        label->setAlpha (0.78f);
        label->setInterceptsMouseClicks (false, false);
    }

   #if defined (SAUCE_PRODUCT_SECRET_SAUCE)
    setupPerformanceButton (freezeButton, "Freeze");
    setupPerformanceButton (reverseButton, "Reverse");
    setupPerformanceButton (repeatButton, "Repeat");
    setupPerformanceButton (dropoutButton, "Dropout");
    setupPerformanceButton (tapeStopButton, "Stop");
    setupPerformanceButton (throwButton, "Throw");

    freezeButton.setTooltip ("Holds short slices for a frozen texture.");
    reverseButton.setTooltip ("Pulls from the recent buffer for reverse-style movement.");
    repeatButton.setTooltip ("Pushes the stutter hold harder.");
    dropoutButton.setTooltip ("Adds rhythmic dropouts.");
    tapeStopButton.setTooltip ("Darkens and dips the motion like a tape stop gesture.");
    throwButton.setTooltip ("Adds a feedback throw from the recent buffer.");

    buttonAttachments.emplace_back (std::make_unique<ButtonAttachment> (processorRef.apvts, paramFreeze, freezeButton));
    buttonAttachments.emplace_back (std::make_unique<ButtonAttachment> (processorRef.apvts, paramReverseMomentary, reverseButton));
    buttonAttachments.emplace_back (std::make_unique<ButtonAttachment> (processorRef.apvts, paramRepeat, repeatButton));
    buttonAttachments.emplace_back (std::make_unique<ButtonAttachment> (processorRef.apvts, paramDropout, dropoutButton));
    buttonAttachments.emplace_back (std::make_unique<ButtonAttachment> (processorRef.apvts, paramTapeStop, tapeStopButton));
    buttonAttachments.emplace_back (std::make_unique<ButtonAttachment> (processorRef.apvts, paramThrowFx, throwButton));
   #endif

    refreshPresetDropdownFromParams();
}

SauceBoxAudioProcessorEditor::~SauceBoxAudioProcessorEditor()
{
    setLookAndFeel (nullptr);
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

    if (programIndex >= 0)
        syncInstantSauceSliderFromPreset (programIndex);
}

void SauceBoxAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (packetInk);

    auto packetBounds = getLocalBounds().toFloat().reduced (12.0f);
    auto packetPath = createPacketPath (packetBounds);

    juce::ColourGradient packetGradient (packetOrange, packetBounds.getX(), packetBounds.getY(),
                                         packetRed.darker (0.25f), packetBounds.getRight(),
                                         packetBounds.getBottom(), false);
    packetGradient.addColour (0.48, packetRed);

    g.setGradientFill (packetGradient);
    g.fillPath (packetPath);

    g.setColour (packetInk.withAlpha (0.28f));
    g.strokePath (packetPath, juce::PathStrokeType (9.0f));

    g.setColour (packetCream);
    g.strokePath (packetPath, juce::PathStrokeType (3.0f));

    const auto innerPacket = packetBounds.reduced (13.0f);
    g.setColour (packetCream.withAlpha (0.22f));
    g.drawRoundedRectangle (innerPacket, 19.0f, 1.5f);

    auto topCrimp = packetBounds.removeFromTop (48.0f).reduced (9.0f, 7.0f);
    auto bottomCrimp = getLocalBounds().toFloat().reduced (21.0f).removeFromBottom (44.0f);

    g.setColour (packetCream.withAlpha (0.28f));
    g.fillRoundedRectangle (topCrimp, 13.0f);
    g.fillRoundedRectangle (bottomCrimp, 13.0f);

    g.setColour (packetInk.withAlpha (0.2f));
    drawCrimpMarks (g, topCrimp);
    drawCrimpMarks (g, bottomCrimp);

    g.setColour (packetCream.withAlpha (0.24f));
    drawSideSealMarks (g, getLocalBounds().toFloat().reduced (12.0f));

    const auto tearY = 116.0f;
    g.setColour (packetCream.withAlpha (0.75f));
    for (float x = 72.0f; x < static_cast<float> (getWidth()) - 72.0f; x += 22.0f)
    {
        if ((x > 72.0f && x < 184.0f) || (x > 268.0f && x < 452.0f))
            continue;

        g.fillRoundedRectangle (x, tearY, 11.0f, 2.0f, 1.0f);
    }

    g.setColour (packetCream.withAlpha (0.64f));
    g.setFont (juce::FontOptions (8.5f, juce::Font::bold));
    g.drawText ("TEAR HERE", getWidth() - 132, static_cast<int> (tearY - 12.0f),
                62, 12, juce::Justification::centred);

    g.setColour (packetPurple.withAlpha (0.92f));
    juce::Path stripe;
    stripe.startNewSubPath (packetBounds.getX() + 28.0f, 92.0f);
    stripe.lineTo (packetBounds.getX() + 80.0f, 92.0f);
    stripe.lineTo (packetBounds.getX() + 54.0f, static_cast<float> (getHeight()) - 104.0f);
    stripe.lineTo (packetBounds.getX() + 2.0f, static_cast<float> (getHeight()) - 104.0f);
    stripe.closeSubPath();
    g.fillPath (stripe);

    g.setColour (packetCream.withAlpha (0.16f));
    g.drawLine (92.0f, 144.0f, 92.0f, static_cast<float> (getHeight()) - 108.0f, 1.4f);
    g.drawLine (static_cast<float> (getWidth()) - 82.0f, 144.0f,
                static_cast<float> (getWidth()) - 82.0f, static_cast<float> (getHeight()) - 108.0f, 1.4f);

    drawPacketCopy (g, getLocalBounds().toFloat().reduced (12.0f));

    if (! proRowBounds_.isEmpty())
    {
        const auto proRect = proRowBounds_.toFloat().expanded (4.0f, 0.0f);
        g.setColour (packetInk.withAlpha (0.34f));
        g.fillRoundedRectangle (proRect, 8.0f);

        g.setColour (packetCream.withAlpha (0.26f));
        g.drawRoundedRectangle (proRect, 8.0f, 1.4f);

        const auto badge = proRect.withSizeKeepingCentre (92.0f, 18.0f)
                                  .withY (proRect.getY() + 7.0f);
        g.setColour (packetCream.withAlpha (0.18f));
        g.fillRoundedRectangle (badge, 7.0f);

        g.setColour (packetCream.withAlpha (0.54f));
        g.drawRoundedRectangle (badge, 7.0f, 1.0f);

        g.setColour (packetCream.withAlpha (0.9f));
        g.setFont (juce::FontOptions (10.5f, juce::Font::bold));
        g.drawText (active_product::theme::unlockBadgeText, badge.toNearestInt(), juce::Justification::centred);
    }
}

void SauceBoxAudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced (34, 28);

    auto header = area.removeFromTop (106);
    titleLabel.setBounds (header.removeFromTop (62));
    header.removeFromTop (4);
    bylineLabel.setBounds (header.removeFromTop (22));

    area.removeFromTop (4);

    auto presetRow = area.removeFromTop (42).reduced (18, 3);
    presetRow.removeFromLeft (48);
    presetLabel.setBounds (presetRow.removeFromLeft (66));
    presetBox.setBounds (presetRow.removeFromLeft (300).reduced (2, 0));

    auto footer = area.removeFromBottom (54).reduced (16, 9);
    auto ctaButtonSlot = footer.removeFromRight (214);
    ctaButton.setBounds (ctaButtonSlot.withSizeKeepingCentre (204, 32));
    ctaLabel.setBounds (footer.reduced (8, 1));

    auto macroZone = area.removeFromTop (136);
    {
        const int knobW = 204;
        auto knobArea = macroZone.withSizeKeepingCentre (knobW, macroZone.getHeight());
        instantSauceLabelKnob.setBounds (knobArea.removeFromTop (24));
        instantSauceSlider.setBounds (knobArea.reduced (6, 2));
    }

    auto freeRow = area.removeFromTop (
       #if defined (SAUCE_PRODUCT_SECRET_SAUCE)
        62
       #else
        74
       #endif
    );
    {
        const int knobW = freeRow.getWidth() / 3;
        auto centredRow = freeRow.withSizeKeepingCentre (knobW * 2, freeRow.getHeight());

        const auto placeKnob = [] (juce::Slider& sl, juce::Label& lb, juce::Rectangle<int> cell)
        {
            lb.setBounds (cell.removeFromTop (18));
            sl.setBounds (cell.reduced (8, 0));
        };

        placeKnob (mixSlider, mixKnobLabel, centredRow.removeFromLeft (knobW));
        placeKnob (outputSlider, outputKnobLabel, centredRow.removeFromLeft (knobW));
    }

    area.removeFromTop (4);

   #if defined (SAUCE_PRODUCT_SECRET_SAUCE)
    auto performanceRow = area.removeFromTop (38).reduced (12, 4);
    {
        const int buttonW = performanceRow.getWidth() / 6;
        freezeButton.setBounds (performanceRow.removeFromLeft (buttonW).reduced (3, 1));
        reverseButton.setBounds (performanceRow.removeFromLeft (buttonW).reduced (3, 1));
        repeatButton.setBounds (performanceRow.removeFromLeft (buttonW).reduced (3, 1));
        dropoutButton.setBounds (performanceRow.removeFromLeft (buttonW).reduced (3, 1));
        tapeStopButton.setBounds (performanceRow.removeFromLeft (buttonW).reduced (3, 1));
        throwButton.setBounds (performanceRow.reduced (3, 1));
    }

    area.removeFromTop (2);
   #endif

    auto proPanel = area.reduced (22, 0);
    proRowBounds_ = proPanel;
    auto proRow = proPanel.reduced (12, 7);
    proRow.removeFromTop (24);

    {
        const int knobW = proRow.getWidth() / 5;
        const auto placeKnob = [] (juce::Slider& sl, juce::Label& lb, juce::Rectangle<int> cell)
        {
            lb.setBounds (cell.removeFromTop (16));
            sl.setBounds (cell.reduced (8, 1));
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
#if defined (SAUCE_PRODUCT_SECRET_SAUCE)
    const float t = juce::jlimit (0.0f, 1.0f, value / 100.0f);

    const float movementRate  = juce::jmap (t, 0.18f, 0.84f);
    const float movementDepth = juce::jmap (t, 0.22f, 0.78f);
    const float chop          = juce::jmap (t, 0.02f, 0.46f);
    const float stutter       = juce::jmap (t, 0.00f, 0.54f);
    const float filter        = juce::jmap (t, 0.68f, 0.34f);
    const float width         = juce::jmap (t, 0.46f, 0.82f);

    const auto setParam = [this] (const char* id, float val)
    {
        if (auto* p = processorRef.apvts.getParameter (id))
            p->setValueNotifyingHost (p->convertTo0to1 (val));
    };

    setParam (paramDrive,    movementRate);
    setParam (paramCrush,    movementDepth);
    setParam (paramWowDepth, chop);
    setParam (paramWowRate,  stutter);
    setParam (paramTone,     filter);
    setParam (paramWidth,    width);
#else
    // value is 0-100. Sweet spot at 50 matches the "Instant Sauce" preset.
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
#endif
}

void SauceBoxAudioProcessorEditor::syncInstantSauceSliderFromPreset (int presetIndex)
{
    const juce::ScopedValueSetter<bool> scopedSetter (isUpdatingInstantSauceFromPreset_, true);
    instantSauceSlider.setValue (processorRef.getPresetInstantSauceValueForUi (presetIndex),
                                 juce::dontSendNotification);
}

void SauceBoxAudioProcessorEditor::setupKnob (juce::Slider& slider, juce::Label& label, const juce::String& labelText)
{
    slider.setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 64, 20);
    slider.setName (labelText);
    slider.setColour (juce::Slider::rotarySliderFillColourId, packetYellow);
    slider.setColour (juce::Slider::rotarySliderOutlineColourId, packetInk.withAlpha (0.42f));
    slider.setColour (juce::Slider::thumbColourId, packetCream);
    slider.setColour (juce::Slider::textBoxTextColourId, packetCream);
    slider.setColour (juce::Slider::textBoxBackgroundColourId, packetInk.withAlpha (0.72f));
    slider.setColour (juce::Slider::textBoxOutlineColourId, packetCream.withAlpha (0.7f));

    label.setText (labelText, juce::dontSendNotification);
    label.setJustificationType (juce::Justification::centred);
    label.setColour (juce::Label::textColourId, packetCream);
    label.setFont (juce::FontOptions (13.0f, juce::Font::bold));

    addAndMakeVisible (slider);
    addAndMakeVisible (label);
}

void SauceBoxAudioProcessorEditor::setupPerformanceButton (juce::TextButton& button, const juce::String& labelText)
{
    button.setButtonText (labelText);
    button.setClickingTogglesState (true);
    button.setColour (juce::TextButton::buttonColourId, packetCream.withAlpha (0.86f));
    button.setColour (juce::TextButton::buttonOnColourId, packetYellow);
    button.setColour (juce::TextButton::textColourOffId, packetInk);
    button.setColour (juce::TextButton::textColourOnId, packetInk);
    addAndMakeVisible (button);
}
