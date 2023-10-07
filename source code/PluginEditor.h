/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include <cmath>

//==============================================================================
/**
*/
class NewProjectAudioProcessorEditor  : public juce::AudioProcessorEditor,
public juce::Slider::Listener
{
public:
    NewProjectAudioProcessorEditor (NewProjectAudioProcessor&);
    ~NewProjectAudioProcessorEditor() override;
    
    // 5) Mu45: Add this method so that we get called when a slider changes
    void sliderValueChanged(juce::Slider * slider) override;
    
    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NewProjectAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewProjectAudioProcessorEditor)
    
    juce::Slider mVolumeSlider;
    juce::Slider mVolumeButton;
    
    juce::Slider mPanSlider;
    juce::Slider mPanButton;
    
    juce::Label volumeLabel;
    juce::Label panLabel;
};
