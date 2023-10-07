/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    // Mu45 2a) Create a pointer to the AudioParameters in the AudioProcessor
    auto& processorParams = processor.getParameters();
     
    // Mu45 2b) Set the attributes of the slider
    mVolumeSlider.setBounds(160, 20, 80, 200); // x, y, width, height (in pixels)
    mVolumeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBarVertical);
    //mVolumeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 30); // readOnly,w,h
    mVolumeSlider.setPopupDisplayEnabled (true, true, this);
    mVolumeSlider.setNumDecimalPlacesToDisplay(1);
    mVolumeSlider.setTextValueSuffix ("db");
    
    //increase/ decrease button for volume
    mVolumeButton.setBounds(60, 80, 60, 80);
    mVolumeButton.setSliderStyle(juce::Slider::SliderStyle::IncDecButtons);
    mVolumeButton.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 40);
    mVolumeButton.setIncDecButtonsMode (juce::Slider::incDecButtonsDraggable_Vertical);
    mVolumeButton.setTextValueSuffix ("db");
    
    mPanSlider.setBounds(100,240,200,40);
    mPanSlider.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    mPanSlider.setPopupDisplayEnabled (true, true, this);
    mPanSlider.setNumDecimalPlacesToDisplay(1);
    //mPanSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 30);
    
    //increase/ decrease button for panning
    mPanButton.setBounds(280, 80, 60, 80);
    mPanButton.setSliderStyle(juce::Slider::SliderStyle::IncDecButtons);
    mPanButton.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 40);
    mPanButton.setIncDecButtonsMode (juce::Slider::incDecButtonsDraggable_Vertical);
    
    volumeLabel.setBounds(60, 40, 60, 40);
    volumeLabel.setText("Volume", juce::dontSendNotification);
    volumeLabel.setFont(juce::Font(16.0f));
    
    panLabel.setBounds(295, 40, 60, 40);
    panLabel.setText("Pan", juce::dontSendNotification);
    panLabel.setFont(juce::Font(16.0f));
    
    // Mu45 2c) Set the range of the slider to the range of the AudioParameter
    // first get a pointer to the parameter object...
    juce::AudioParameterFloat* volumeprocParam =
    (juce::AudioParameterFloat*)processorParams.getUnchecked(0);
    mVolumeSlider.setRange(volumeprocParam->range.start, volumeprocParam->range.end);
    mVolumeSlider.setValue(*volumeprocParam);
    mVolumeButton.setRange(volumeprocParam->range.start, volumeprocParam->range.end,0.1f);
    mVolumeButton.setValue(*volumeprocParam);
    
    
    juce::AudioParameterFloat* panProcParam = (juce::AudioParameterFloat*)processorParams.getUnchecked(1);
    mPanSlider.setRange(panProcParam->range.start, panProcParam->range.end);
    mPanSlider.setValue(*panProcParam);
    mPanButton.setRange(panProcParam->range.start, panProcParam->range.end,1.0f);
    mPanButton.setValue(*panProcParam);
    
    // Mu45 7) Set the ProcessorEditor to be a listener for our slider
    mVolumeSlider.addListener(this);
    mPanSlider.addListener(this);
    mVolumeButton.addListener(this);
    mPanButton.addListener(this);
    
    // Mu45 3) Add the slider. (It will now be a child of the AudioProcessorEditor object
    addAndMakeVisible(mVolumeSlider);
    addAndMakeVisible(mVolumeButton);
    addAndMakeVisible(volumeLabel);
    
    addAndMakeVisible(mPanSlider);
    addAndMakeVisible(mPanButton);
    addAndMakeVisible(panLabel);
    
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

// 6) Mu45: This will get called whenever any slider is changed
void NewProjectAudioProcessorEditor::sliderValueChanged(juce::Slider* slider){
    // A) This will point to AudioParameters in the AudioProcessor
     auto& proccessorParams = processor.getParameters();
     
     // B) Compare the pointer to the slider that was changed with the address of our slider
     if (slider == &mVolumeSlider){
     // C) Get a pointer to the first parameter in the Processor
         juce::AudioParameterFloat* volumeParam = (juce::AudioParameterFloat*)proccessorParams.getUnchecked(0);
         // D) Use the value from our slider to set the parameter in the Processor

         float sliderValue = mVolumeSlider.getValue();
         if (mVolumeButton.getValue() != sliderValue)
                     mVolumeButton.setValue(sliderValue);
         *volumeParam = sliderValue; // set the param
     
         // E) We can use DBG() for simple print debugging
         DBG("Volume Slider Changed to " << sliderValue);
     }else if (slider == &mVolumeButton){
         // C) Get a pointer to the first parameter in the Processor
             juce::AudioParameterFloat* volumeParam = (juce::AudioParameterFloat*)proccessorParams.getUnchecked(0);
             // D) Use the value from our slider to set the parameter in the Processor

             float sliderValue = mVolumeButton.getValue();
             if (mVolumeSlider.getValue() != sliderValue)
                         mVolumeSlider.setValue(sliderValue);
             *volumeParam = sliderValue; // set the param
         
             DBG("Volume Slider Changed to " << sliderValue);
         }
    
    if (slider == &mPanSlider){

        juce::AudioParameterFloat* panParam = (juce::AudioParameterFloat*)proccessorParams.getUnchecked(1);
        float sliderValue = mPanSlider.getValue();
        if (mPanButton.getValue() != sliderValue){
            mPanButton.setValue(sliderValue);
        }
        *panParam = sliderValue; // set the param
    

        DBG("Panning Slider Changed to " << sliderValue);
    }else if (slider == &mPanButton){
            juce::AudioParameterFloat* panParam = (juce::AudioParameterFloat*)proccessorParams.getUnchecked(1);
            float sliderValue = mPanButton.getValue();
            if (mPanSlider.getValue() != sliderValue){
                mPanSlider.setValue(sliderValue);
            }
            *panParam = sliderValue; // set the param
        
            DBG("Panning Slider Changed to " << sliderValue);
        }
}


//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    //g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void NewProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
