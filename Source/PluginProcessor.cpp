/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FMiniAudioProcessor::FMiniAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts (*this, nullptr, "Parameters", createParams())
#endif
{
    synth.addSound(new FMiniSound());
    synth.addVoice(new FMiniVoice());

}

FMiniAudioProcessor::~FMiniAudioProcessor()
{
}

//==============================================================================
const juce::String FMiniAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FMiniAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FMiniAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FMiniAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FMiniAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FMiniAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FMiniAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FMiniAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String FMiniAudioProcessor::getProgramName (int index)
{
    return {};
}

void FMiniAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void FMiniAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
    for (int v=0; v<synth.getNumVoices();v++)
    {
            if(auto voice = dynamic_cast<FMiniVoice*>(synth.getVoice(v)))
            {
                voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
            }
    }
}

void FMiniAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FMiniAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void FMiniAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int v = 0; v < synth.getNumVoices(); v++)
    {
        if (auto voice = dynamic_cast<FMiniVoice*>(synth.getVoice(v)))
        {
            auto& index = *apvts.getRawParameterValue("IDX");
            auto& mult = *apvts.getRawParameterValue("MULT");
            voice->updateModulator(index.load(), mult.load());
        }
    }
    
    for (const juce::MidiMessageMetadata metadata: midiMessages)
    {
        if (metadata.numBytes==3)
        {
            juce::Logger::writeToLog(metadata.getMessage().getDescription());
        }
    }
    
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    
}

//==============================================================================
bool FMiniAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FMiniAudioProcessor::createEditor()
{
    return new FMiniAudioProcessorEditor (*this);
}

//==============================================================================
void FMiniAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FMiniAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FMiniAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout FMiniAudioProcessor::createParams()
{
    //Modulator index
    
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
   
    //Modulator index
    params.push_back(std::make_unique<juce::AudioParameterFloat>("IDX", "Index", juce::NormalisableRange<float>{0.0f, 10.0f, 1.0f}, 0.0f));

    //Modulator mult
    params.push_back(std::make_unique<juce::AudioParameterChoice>("MULT", "Freq. mult", juce::StringArray{"x0.5", "x1", "x2"}, 1));

    return {params.begin(), params.end()};
}
