/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PowerButtonLookAndFeel.h"
#include "AppInc.h"

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
    void createTitle(juce::Label* label, juce::String title);
    void createSliderValueLabel(juce::Label& label, juce::Slider& slider);
private:

    NoiseGateAudioProcessor& audioProcessor;
    PowerButtonLookAndFeel powerbuttonLookandFeel;
    AppLookAndFeelCls appLookAndFeel;


    ToggleButton powerButton;
    Slider thresholdSlider;
    Slider smoothSlider; //also known as return

    Label thresholdLabelValue;
    Label smoothLabelValue;

    Label  thresholdLabel;
    Label  smoothLabel;

    Label pluginTitle;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoiseGateAudioProcessorEditor)
};
