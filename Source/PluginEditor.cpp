/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FMiniAudioProcessorEditor::FMiniAudioProcessorEditor (FMiniAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{

    setSize (400, 300);
    
    indexAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "IDX", indexSlider);
    multAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "MULT", multSelector);

    setSliderParams(indexSlider);
    
}

FMiniAudioProcessorEditor::~FMiniAudioProcessorEditor()
{
}

//==============================================================================
void FMiniAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void FMiniAudioProcessorEditor::resized()
{
    const auto padding = 20;
    const auto bounds = getLocalBounds().reduced(padding);
    const auto sliderWidth = bounds.getWidth();
    const auto sliderHeight = 45;
    const auto sliderStartX = padding;
    const auto sliderStartY = padding;
    
    indexSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
}

void FMiniAudioProcessorEditor::setSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    slider.setTextBoxStyle(juce::Slider::TextBoxRight, true, 50, 25);
    addAndMakeVisible(slider);
}
