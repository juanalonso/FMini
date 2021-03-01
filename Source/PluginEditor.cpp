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
    
    attackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "ATT", attackSlider);
    decayAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DEC", decaySlider);
    sustainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "SUS", sustainSlider);
    releaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "REL", releaseSlider);
    
    setSliderParams(attackSlider);
    setSliderParams(decaySlider);
    setSliderParams(sustainSlider);
    setSliderParams(releaseSlider);
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
    const auto padding = 10;
    const auto bounds = getLocalBounds().reduced(padding*4);
    const auto sliderWidth = bounds.getWidth();
    const auto sliderHeight = 30;
    const auto sliderStartX = padding*4;
    const auto sliderStartY = padding;
    
    indexSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    attackSlider.setBounds(sliderStartX, indexSlider.getY()+sliderHeight+padding*4, sliderWidth, sliderHeight);
    decaySlider.setBounds(sliderStartX, attackSlider.getY()+sliderHeight+padding, sliderWidth, sliderHeight);
    sustainSlider.setBounds(sliderStartX, decaySlider.getY()+sliderHeight+padding, sliderWidth, sliderHeight);
    releaseSlider.setBounds(sliderStartX, sustainSlider.getY()+sliderHeight+padding, sliderWidth, sliderHeight);
    
}

void FMiniAudioProcessorEditor::setSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    slider.setTextBoxStyle(juce::Slider::TextBoxRight, true, 50, 25);
    addAndMakeVisible(slider);
}
