/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
using namespace juce;

//==============================================================================
/**
*/
class NoiseGateAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                       public Slider::Listener
{
public:
    NoiseGateAudioProcessorEditor (NoiseGateAudioProcessor&);
    ~NoiseGateAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider* slider) override;


private:

    NoiseGateAudioProcessor& audioProcessor;
    ToggleButton powerButton;
    Slider thresholdSlider;
    Slider smoothSlider; //also known as return
    Label  thresholdLabel;
    Label  smoothLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoiseGateAudioProcessorEditor)
};
