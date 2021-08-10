/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "ODMainPanel.h"
#include "LookAndFeel.h"

//==============================================================================
/**
*/
class AutoPannerAudioProcessorEditor  : public AudioProcessorEditor,
                                        public Button::Listener,
                                        public ComboBox::Listener
{
public:
    AutoPannerAudioProcessorEditor (AutoPannerAudioProcessor&);
    ~AutoPannerAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void buttonClicked(Button* button) override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AutoPannerAudioProcessor& processor;
    
    ToggleButton mPannerToggle;
    ToggleButton mDriveToggle;
    
    ScopedPointer<ODMainPanel> mMainPanel;
    ScopedPointer<ODLookAndFeel> mLookAndFeel;
    
    Image backgroundImage;
    
    //ComboBox* syncCombo;
    ComboBox syncVal;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AutoPannerAudioProcessorEditor)
};
