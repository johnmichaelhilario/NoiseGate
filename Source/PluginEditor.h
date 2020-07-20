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

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
   


    NoiseGateAudioProcessor& audioProcessor;
    Slider thresholdSlider;
    Slider smoothSlider; //also known as return
    Label  thresholdLabel;
    Label  smoothLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoiseGateAudioProcessorEditor)
};
