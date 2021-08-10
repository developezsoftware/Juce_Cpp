/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ODFxPanel.h"
#include "ODParameters.h"


//==============================================================================
AutoPannerAudioProcessorEditor::AutoPannerAudioProcessorEditor (AutoPannerAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(MAIN_PANEL_WIDTH, MAIN_PANEL_HEIGHT);
    
    mMainPanel = new ODMainPanel(&processor);
    addAndMakeVisible(mMainPanel);
    
    mPannerToggle.setButtonText ("Linear Pan");
    mPannerToggle.addListener(this);
    addAndMakeVisible (mPannerToggle);
    
    mDriveToggle.setButtonText ("Drive");
    mDriveToggle.addListener(this);
    addAndMakeVisible (mDriveToggle);
    
    processor.getParameter(oParameter_DelayType);
    
    
//    int mIsDelay = processor.isDelay;
//    if(processor.getParameter(oParameter_DelayType) == oODDelayType_Delay)
//    {
        syncVal.setBounds(125, 132, 70, 20);
        syncVal.addItem("Free", 1);
        syncVal.addItem("half", 2);
        syncVal.addItem("quarter", 3);
        syncVal.addItem("eight", 4);
        syncVal.addItem("sixteenth", 5);
        
        syncVal.setSelectedItemIndex(0, sendNotification);
        addAndMakeVisible(syncVal);
        
        syncVal.addListener(this);
//    }
//    else if(processor.getParameter(oParameter_DelayType) == ODDelayType_Chorus)
//    {
//        syncVal.removeListener(this);
//        syncVal.setBounds(0, 0, 0, 0);
//        std::cout << "this happened" << std::endl;
//    }
    mLookAndFeel = new ODLookAndFeel();
    LookAndFeel::setDefaultLookAndFeel(mLookAndFeel);
    
    
    
    
    backgroundImage = ImageCache::getFromMemory(BinaryData::Background3_png, BinaryData::Background3_pngSize);
    

    
}

AutoPannerAudioProcessorEditor::~AutoPannerAudioProcessorEditor()
{
}

//==============================================================================
void AutoPannerAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.drawImage(backgroundImage, getLocalBounds().toFloat());
}

void AutoPannerAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    auto area = getLocalBounds();
    
    
    mPannerToggle.setBounds(getWidth()/2.0 + 75, 275, 70, 70);
    mDriveToggle.setBounds(getWidth()/2.0 + 75, 375, 70, 70);
    
}

void AutoPannerAudioProcessorEditor::buttonClicked(Button *button)
{
    if ( button == &mPannerToggle)
    {
        processor.isPanner = mPannerToggle.getToggleState();
    }
    if ( button == &mDriveToggle)
    {
        processor.isDrive = mDriveToggle.getToggleState();
    }
}

void AutoPannerAudioProcessorEditor::comboBoxChanged(ComboBox *comboBoxThatHasChanged)
{
    if(comboBoxThatHasChanged == &syncVal)
    {
        const int thisSync = (int)syncVal.getSelectedItemIndex();
        
        std::cout<< thisSync << std::endl;
        switch (thisSync) {
            case 0:
                std::cout << "free tempo" << std::endl;
                processor.syncVal = 0;
                //ODFxPanel::thisSyncVal = 0;
                break;
            case 1:
                processor.syncVal = 1.0;
                break;
            case 2:
                processor.syncVal = 2.0;
                break;
            case 3:
                processor.syncVal = 3.0;
                break;
            case 4:
                processor.syncVal = 4.0;
                break;
            case 5:
                processor.syncVal = 5.0;
                break;
            default:
                std::cout << "error unknown val" << std::endl;
                processor.syncVal = 0;
                break;
        }
    }
}
