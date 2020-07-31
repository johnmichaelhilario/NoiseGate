/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "PowerButtonLookAndFeel.h"
#include "AboutButtonLookandFeel.h"
#include "AppInc.h"
#include "DialogComponent.h"

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
    void callAlertWindows(String title, String description, String company, String copyright);

private:
    
    int knobWidth = 70;
    int knobHeight = 70;
    int knobX = 56;
    int knobY = 30;

    NoiseGateAudioProcessor& audioProcessor;
    PowerButtonLookAndFeel powerbuttonLookandFeel;
    AboutButtonLookandFeel aboutbuttonLookandFeel;
    AlertWindow alertWindow;
    AppLookAndFeelCls appLookAndFeel;
    PluginDialog pluginDialog;
    ToggleButton powerButton;
    ToggleButton aboutButton;
    Slider thresholdSlider;
    Slider smoothSlider; //also known as return

    Label thresholdLabelValue;
    Label smoothLabelValue;

    Label  thresholdLabel;
    Label  smoothLabel;

    Label pluginTitle;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoiseGateAudioProcessorEditor)
};
