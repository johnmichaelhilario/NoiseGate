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
    thresholdSlider.setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    thresholdSlider.setRange(0.0f,1.0f);
    thresholdSlider.setTextBoxStyle(Slider::TextBoxRight, false, 90, 0);
    thresholdSlider.setPopupDisplayEnabled(true, false, this);
    thresholdSlider.setValue(0.0f);
    thresholdSlider.addListener(this);

    //Smooth
    smoothSlider .setSliderStyle(Slider::SliderStyle::LinearBarVertical);
    smoothSlider.setRange(0.0f, 1.0f);
    smoothSlider.setTextBoxStyle(Slider::TextBoxRight, false, 90, 0);
    smoothSlider.setPopupDisplayEnabled(true, false, this);
    smoothSlider.setValue(0.0f);
    smoothSlider.addListener(this);
    
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
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    thresholdSlider.setBounds(40, 30, 20, getHeight()-60);
    smoothSlider.setBounds(70, 30, 20, getHeight() - 60);
}

void NoiseGateAudioProcessorEditor::sliderValueChanged(Slider* slider) {
    if (slider == &thresholdSlider) {
        audioProcessor.thresholdCopy = thresholdSlider.getValue();
    }
    else if(slider == &smoothSlider) {
        audioProcessor.smoothCopy = smoothSlider.getValue();
    }
}