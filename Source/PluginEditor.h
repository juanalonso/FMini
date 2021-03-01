/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class FMiniAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    FMiniAudioProcessorEditor (FMiniAudioProcessor&);
    ~FMiniAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
private:
    void setSliderParams(juce::Slider& slider);

    juce::ComboBox multSelector;
    juce::Slider indexSlider;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> indexAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> multAttachment;

    FMiniAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FMiniAudioProcessorEditor)
};
