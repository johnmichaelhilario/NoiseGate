/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NoiseGateAudioProcessorEditor::NoiseGateAudioProcessorEditor (NoiseGateAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{

    //Threshold
    thresholdSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    thresholdSlider.setRange(0.0f,1.0f);
    thresholdSlider.setTextBoxStyle(Slider::TextBoxRight, false, 90, 0);

    thresholdLabel.setText ("Threshold", juce::dontSendNotification);
    //addAndMakeVisible(thresholdLabel);


    //thresholdLabel.attachToComponent (&thresholdSlider, true);
    thresholdSlider.setPopupDisplayEnabled(false, false, this);
    thresholdSlider.setEnabled(false);
    thresholdSlider.setValue(0.0f);
    thresholdSlider.addListener(this); 

    //Smooth
    smoothSlider .setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    smoothSlider.setRange(0.0f, 1.0f);
    smoothSlider.setTextBoxStyle(Slider::TextBoxRight, false, 90, 0);
  
    smoothLabel.setText ("Smooth", juce::dontSendNotification);
    //smoothLabel.attachToComponent (&smoothSlider, true);
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

    //pluginTitle
    pluginTitle.setText("GATE", juce::dontSendNotification);
    pluginTitle.setColour(juce::Label::textColourId, juce::Colours::orange);
    pluginTitle.setFont(juce::Font(23.0f, juce::Font::bold));

   // setLookAndFeel(&appLookAndFeel);
    //Power button
   // powerButton.setButtonText("Power");


    powerButton.setLookAndFeel(&powerbuttonLookandFeel);
    
    addAndMakeVisible(&powerButton);

    powerButton.onClick = [this] {
        audioProcessor.isPowerOn = powerButton.getToggleState();
        smoothSlider.setEnabled(powerButton.getToggleState());
        thresholdSlider.setEnabled(powerButton.getToggleState());
    };

    addAndMakeVisible(&pluginTitle);

    addAndMakeVisible(&thresholdSlider);
    addAndMakeVisible(thresholdLabel);

    addAndMakeVisible(&smoothSlider);
    addAndMakeVisible(&smoothLabel);

    addAndMakeVisible(&thresholdLabelValue);
    addAndMakeVisible(&smoothLabelValue);

    setSize (300, 150);
}

NoiseGateAudioProcessorEditor::~NoiseGateAudioProcessorEditor()
{
 
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
    //Title
    pluginTitle.setBounds(10, 10, 100, 25);

    //PowerButton
    powerButton.setBounds(10, 50, 50, 50);

    //threshold objects position
    thresholdSlider.setBounds(70, -20, 180, 180);
    thresholdLabelValue.setBounds(89, 101, 50, 20);
    thresholdLabel.setBounds(80, 120, 100, 20);

    //smooth objects position
    smoothSlider.setBounds(180, -20, 180, 180);
    smoothLabelValue.setBounds(200, 101, 50, 20);
    smoothLabel.setBounds(196, 120, 100, 20);


}



int smoothFloatToInt(float val) {
    int intValue = 100 * val;
    return intValue;
}

int thresholdFloatToInt(float val) {
    int intValue = 100 * val;
    const int negativeVal = 200;
    return (intValue * 2) - negativeVal;
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
