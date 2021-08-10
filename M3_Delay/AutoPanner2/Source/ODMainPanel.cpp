/*
  ==============================================================================

    ODMainPanel.cpp
    Created: 1 Jul 2019 1:13:50am
    Author:  Johnny Lopez

  ==============================================================================
*/

#include "ODMainPanel.h"
#include "ODParameters.h"

ODMainPanel::ODMainPanel(AutoPannerAudioProcessor* inProcessor) :
 ODPanelBase(inProcessor)
{
    setSize(MAIN_PANEL_WIDTH, MAIN_PANEL_HEIGHT);
    
    thisSyncVal = 0.0;
    
    mTopPanel = new ODTopPanel(inProcessor);
    mTopPanel->setTopLeftPosition(0, 0);
    addAndMakeVisible(mTopPanel);
    
    mInputGainPanel = new ODGainPanel(inProcessor);
    mInputGainPanel->setTopLeftPosition(0, TOP_PANEL_HEIGHT);
    mInputGainPanel->setParameterID(oParameter_InputGain);
    addAndMakeVisible(mInputGainPanel);
    
    mOutputGainPanel = new ODGainPanel(inProcessor);
    mOutputGainPanel->setTopLeftPosition(MAIN_PANEL_WIDTH - GAIN_PANEL_WIDTH, TOP_PANEL_HEIGHT);
    mOutputGainPanel->setParameterID(oParameter_OutPutGain);
    addAndMakeVisible(mOutputGainPanel);
    
    mCenterPanel = new ODCenterPanel(inProcessor);
    mCenterPanel->setTopLeftPosition(GAIN_PANEL_WIDTH, TOP_PANEL_HEIGHT);
    addAndMakeVisible(mCenterPanel);
    
}
ODMainPanel::~ODMainPanel()
{
    
}
