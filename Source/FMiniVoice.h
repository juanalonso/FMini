/*
  ==============================================================================

    SynthVoice.h
    Created: 28 Feb 2021 10:38:56am
    Author:  Juan Alonso

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "FMiniSound.h"

class FMiniVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound (juce::SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote (float velocity, bool allowTailOff) override;
    void pitchWheelMoved (int newPitchWheelValue) override;
    void controllerMoved (int controllerNumber, int newControllerValue) override;
    void renderNextBlock (juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override;
private:
};