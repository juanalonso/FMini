/*
  ==============================================================================

    SynthSound.h
    Created: 28 Feb 2021 10:39:10am
    Author:  Juan Alonso

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class FMiniSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote (int midiNoteNumber) override
    {
        return true;
    }
    
    bool appliesToChannel (int midiChannel) override
    {
        return true;
    }
    
};
