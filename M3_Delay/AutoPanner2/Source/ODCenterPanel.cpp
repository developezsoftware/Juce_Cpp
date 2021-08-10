/*
  ==============================================================================

    ODCenterPanel.cpp
    Created: 1 Jul 2019 1:14:20am
    Author:  Johnny Lopez

  ==============================================================================
*/

#include "ODCenterPanel.h"

ODCenterPanel::ODCenterPanel(AutoPannerAudioProcessor* inProcessor) :
    ODPanelBase(inProcessor)
{
    setSize(CENTER_PANEL_WIDTH, CENTER_PANEL_HEIGHT);
    
    mMenuBar = new ODCenterPanelMenuBar(inProcessor);
    mMenuBar->setTopLeftPosition(0, 0);
    addAndMakeVisible(mMenuBar);
    
    mFxPanel = new ODFxPanel(inProcessor);
    mFxPanel->setTopLeftPosition(0, CENTER_PANEL_MENU_BAR_HEIGHT);
    addAndMakeVisible(mFxPanel);
    
    mMenuBar->addFxTypeComboBoxListener(mFxPanel);

    //mMenuBar->addFxTypeComboBoxListener(syncCombo);
}

ODCenterPanel::~ODCenterPanel()
{
    mMenuBar->removeFxTypeComboBoxListener(mFxPanel);
}
