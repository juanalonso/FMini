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

}

void FMiniVoice::stopNote (float velocity, bool allowTailOff)
{
    
}

void FMiniVoice::pitchWheelMoved (int newPitchWheelValue)
{
    
}

void FMiniVoice::controllerMoved (int controllerNumber, int newControllerValue)
{
    
}

void FMiniVoice::renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples)
{
    
}
