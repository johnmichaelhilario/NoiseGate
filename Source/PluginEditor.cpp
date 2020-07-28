/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"



void NoiseGateAudioProcessorEditor::createTitle(juce::Label* label, juce::String title) {
    label->setText(title, juce::NotificationType::dontSendNotification);
    label->setJustificationType(juce::Justification::topLeft);
    label->setColour(juce::Label::textColourId, juce::Colours::white);
    label->setBounds(16, 16, 100, 25);
    label->setFont(25.0f);
    if (audioProcessor.isPowerOn) {
        label->setColour(juce::Label::textColourId, UI_Color1);
        return;
    }
}
void NoiseGateAudioProcessorEditor::createSliderValueLabel(juce::Label& label, juce::Slider& slider)
{
    int width = slider.getWidth();
    int height = slider.getHeight();
    auto position = slider.getPosition();
    juce::Logger::writeToLog(position.toString());
    int x = position.x;
    int y = position.y + (height * 0.75) + 1;
    juce::Font labelFont;
    labelFont.setBold(true);
    labelFont.setHeight(11.0f);
    label.setColour(juce::Label::ColourIds::textColourId, getLookAndFeel().findColour(Slider::ColourIds::thumbColourId));
    label.setText("0.0", juce::NotificationType::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    label.setColour(juce::Label::ColourIds::outlineColourId, juce::Colour());
    label.toFront(false);
    label.setBounds(x, y, width, height * .25);
    label.setFont(labelFont);
    label.setEnabled(false);
    addAndMakeVisible(label);
}

//==============================================================================
NoiseGateAudioProcessorEditor::NoiseGateAudioProcessorEditor (NoiseGateAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    //Title
    createTitle(&pluginTitle, "GATE");

    
    //Threshold
    thresholdSlider.setSliderStyle(Slider::SliderStyle::Rotary);
    thresholdSlider.setRange(0.0f,1.0f);
    thresholdSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    thresholdLabel.setText ("Threshold", juce::dontSendNotification);
    thresholdLabel.setJustificationType(juce::Justification::centred);
    thresholdSlider.setPopupDisplayEnabled(false, false, this);
    thresholdSlider.setEnabled(false);
    thresholdSlider.setValue(0.0f);
    thresholdSlider.addListener(this); 

    //Smooth
    smoothSlider .setSliderStyle(Slider::SliderStyle::Rotary);
    smoothSlider.setRange(0.0f, 1.0f);
    smoothSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
    smoothLabel.setText ("Smooth", juce::dontSendNotification);
    smoothLabel.setJustificationType(juce::Justification::centred);
    smoothSlider.setPopupDisplayEnabled(false, false, this);
    smoothSlider.setEnabled(false);
    smoothSlider.setValue(0.0f);
    smoothSlider.addListener(this);


    //ThresholdValue
    thresholdLabelValue.setText("-200", juce::dontSendNotification);
    thresholdLabelValue.setJustificationType(juce::Justification::centred);
    thresholdLabelValue.setColour(juce::Label::textColourId, juce::Colours::orange);

    //SmoothValue
    smoothLabelValue.setText("0", juce::dontSendNotification);
    smoothLabelValue.setJustificationType(juce::Justification::centred);
    smoothLabelValue.setColour(juce::Label::textColourId, juce::Colours::orange);


    setLookAndFeel(&appLookAndFeel);
    powerButton.setLookAndFeel(&powerbuttonLookandFeel);

   
    powerButton.onClick = [this] {
        audioProcessor.isPowerOn = powerButton.getToggleState();
        smoothSlider.setEnabled(powerButton.getToggleState());
        thresholdSlider.setEnabled(powerButton.getToggleState());
        createTitle(&pluginTitle, "GATE");
    };

    addAndMakeVisible(&powerButton);
    addAndMakeVisible(&pluginTitle);
    addAndMakeVisible(&thresholdSlider);
    addAndMakeVisible(thresholdLabel);
    addAndMakeVisible(&smoothSlider);
    addAndMakeVisible(&smoothLabel);

    setSize (295, 157);

    createSliderValueLabel(thresholdLabelValue, thresholdSlider);
    createSliderValueLabel(smoothLabelValue, smoothSlider);
}

NoiseGateAudioProcessorEditor::~NoiseGateAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void NoiseGateAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Noise Gate", getLocalBounds(), juce::Justification::centredTop, 1);

    
}

void NoiseGateAudioProcessorEditor::resized()
{
    const int yOffset = 41;
    thresholdSlider.setBounds(82, yOffset, 90, 90);
    smoothSlider.setBounds(180, yOffset, 90, 90);


    powerButton.setBounds(16, yOffset +thresholdSlider.getHeight()/2 -25, 50, 50);

    thresholdLabel.setBounds(thresholdSlider.getX(), thresholdSlider.getY() + thresholdSlider.getHeight() - 2, thresholdSlider.getWidth(), 12);
    smoothLabel.setBounds(smoothSlider.getX(), smoothSlider.getY() + smoothSlider.getHeight() - 2, smoothSlider.getWidth(), 12);

}



int smoothFloatToInt(float val) {
    int intValue = 100 * val;
    return intValue;
}

int thresholdFloatToInt(float val) {
    int intValue = 200 * val;
    return (200 - intValue) *-1;
}

void NoiseGateAudioProcessorEditor::sliderValueChanged(Slider* slider) {
    if (slider == &thresholdSlider) {
        audioProcessor.threshold = (float) thresholdSlider.getValue();
        thresholdLabelValue.setText((String)thresholdFloatToInt(thresholdSlider.getValue()), juce::dontSendNotification);
    }
    else if(slider == &smoothSlider) {
        audioProcessor.smooth = (float) smoothSlider.getValue();
        smoothLabelValue.setText((String)smoothFloatToInt(smoothSlider.getValue()), juce::dontSendNotification);
    }
}
