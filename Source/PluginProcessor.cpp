/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

ADSR adsr;

//==============================================================================
NoiseGateAudioProcessor::NoiseGateAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties().withInput("Input", juce::AudioChannelSet::stereo())          
                                        .withOutput("Output", juce::AudioChannelSet::stereo())
                                        .withInput("Sidechain", juce::AudioChannelSet::stereo())
                       ), 
    threshold("threshold", "Threshold", 0.0f, 1.0f, 0.0f),
    smooth("smooth", "Smooth", 0.0f, 1.0f, 0.8f)
#endif
{
    addParameter(&threshold);
    addParameter(&smooth);
   

}

NoiseGateAudioProcessor::~NoiseGateAudioProcessor()
{
   
}

//==============================================================================
const juce::String NoiseGateAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NoiseGateAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NoiseGateAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool NoiseGateAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double NoiseGateAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NoiseGateAudioProcessor::getNumPrograms()
{
    return 1;   
}

int NoiseGateAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NoiseGateAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String NoiseGateAudioProcessor::getProgramName (int index)
{
    return {};
}

void NoiseGateAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void NoiseGateAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    lowPassCoeff = 0.0f;    
    sampleCountDown = 0;    

}

void NoiseGateAudioProcessor::releaseResources()
{

}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NoiseGateAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
  
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;


   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void NoiseGateAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    if (!isPowerOn)
        return;

    auto mainInputOutput = getBusBuffer(buffer, true, 0);
    auto sideChainInput = getBusBuffer(buffer, true, 1);

    auto thresholdCopy = threshold.get();
    auto smoothCopy = smooth.get();

    for (auto j = 0; j < buffer.getNumSamples(); ++j)
    {
        auto mixedSamples = 0.0f;

        for (auto i = 0; i < sideChainInput.getNumChannels(); ++i)
            mixedSamples += sideChainInput.getReadPointer(i)[j];

        mixedSamples /= static_cast<float> (sideChainInput.getNumChannels());
        lowPassCoeff = (smoothCopy * lowPassCoeff) + ((1.0f - smoothCopy) * mixedSamples);



        if (lowPassCoeff >= thresholdCopy)
            sampleCountDown = (int)getSampleRate();

        for (auto i = 0; i < mainInputOutput.getNumChannels(); ++i)
            *mainInputOutput.getWritePointer(i, j) = sampleCountDown > 0 ? *mainInputOutput.getReadPointer(i, j)
            : 0;

        if (sampleCountDown > 0)
            --sampleCountDown;
    }
}

//==============================================================================
bool NoiseGateAudioProcessor::hasEditor() const
{
    return true; 
}

juce::AudioProcessorEditor* NoiseGateAudioProcessor::createEditor()
{
    return new NoiseGateAudioProcessorEditor  (*this);
}

//==============================================================================
void NoiseGateAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{

    MemoryOutputStream stream(destData, true);

    stream.writeFloat(threshold);
    stream.writeFloat(smooth);
}

void NoiseGateAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    MemoryInputStream stream(data, static_cast<size_t> (sizeInBytes), false);

    threshold.setValueNotifyingHost(stream.readFloat());
    smooth.setValueNotifyingHost(stream.readFloat());

}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NoiseGateAudioProcessor();
}