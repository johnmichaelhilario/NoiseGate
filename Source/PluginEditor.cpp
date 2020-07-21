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
    thresholdSlider.setSliderStyle(Slider::SliderStyle:: LinearBar);
    thresholdSlider.setRange(0.0f,1.0f);
    thresholdSlider.setTextBoxStyle(Slider::TextBoxRight, false, 90, 0);
    addAndMakeVisible (thresholdLabel);
    thresholdLabel.setText ("Threshold", juce::dontSendNotification);
    thresholdLabel.attachToComponent (&thresholdSlider, true);
    thresholdSlider.setPopupDisplayEnabled(true, false, this);
    thresholdSlider.setValue(0.0f);
    thresholdSlider.addListener(this);

    //Smooth
    smoothSlider .setSliderStyle(Slider::SliderStyle:: LinearBar);
    smoothSlider.setRange(0.0f, 1.0f);
    smoothSlider.setTextBoxStyle(Slider::TextBoxRight, false, 90, 0);
    addAndMakeVisible (thresholdLabel);
    smoothLabel.setText ("Smooth", juce::dontSendNotification);
    smoothLabel.attachToComponent (&smoothSlider, true);
    smoothSlider.setPopupDisplayEnabled(true, false, this);
    smoothSlider.setValue(0.0f);
    smoothSlider.addListener(this);
    

    //Power button
    powerButton.setButtonText("Power");

    addAndMakeVisible(&powerButton);
    powerButton.onClick = [this] {
        audioProcessor.isPowerOn = powerButton.getToggleState();
    };
    addAndMakeVisible(&thresholdSlider);
    addAndMakeVisible(&smoothSlider);
    setSize (400, 300);
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
    auto sliderLeft = 120;
    powerButton.setBounds(sliderLeft, 0, 100, 50);
    thresholdSlider.setBounds (sliderLeft, 50, getWidth() - sliderLeft - 10, 20);
    smoothSlider .setBounds (sliderLeft, 70, getWidth() - sliderLeft - 10, 20);
  
}

void NoiseGateAudioProcessorEditor::sliderValueChanged(Slider* slider) {
    if (slider == &thresholdSlider) {
        audioProcessor.threshold = (float) thresholdSlider.getValue();
    }
    else if(slider == &smoothSlider) {
        audioProcessor.smooth = (float) smoothSlider.getValue();
    }
}