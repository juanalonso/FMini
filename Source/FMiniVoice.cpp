/*
  ==============================================================================

    SynthVoice.cpp
    Created: 28 Feb 2021 10:38:56am
    Author:  Juan Alonso

  ==============================================================================
*/

#include "FMiniVoice.h"

bool FMiniVoice::canPlaySound (juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void FMiniVoice::startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition)
{
    osc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    adsr.noteOn();
}

void FMiniVoice::stopNote (float velocity, bool allowTailOff)
{
    adsr.noteOff();
}

void FMiniVoice::pitchWheelMoved (int newPitchWheelValue)
{
    
}

void FMiniVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}

void FMiniVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels){
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    
    adsr.setSampleRate(sampleRate);
    osc.prepare(spec);
    gain.prepare(spec);
    
    gain.setGainLinear(0.1f);
    
    isPrepared = true;
}

void FMiniVoice::renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);
    
    juce::dsp::AudioBlock<float> audioBlock {outputBuffer};
    
    osc.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    adsr.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);
    
}
