/*
  ==============================================================================

    ODCenterPanelMenuBar.cpp
    Created: 1 Jul 2019 1:14:33am
    Author:  Johnny Lopez

  ==============================================================================
*/

#include "ODCenterPanelMenuBar.h"
#include "ODParameters.h"
#include "ODFxPanel.h"


ODCenterPanelMenuBar::ODCenterPanelMenuBar(AutoPannerAudioProcessor* inProcessor) :
ODPanelBase(inProcessor)
{
    setSize(CENTER_PANEL_MENU_BAR_WIDTH, CENTER_PANEL_MENU_BAR_HEIGHT);
    
    const int width = 85;
    
    mFxTypeComboBox = new ODParameterComboBox(mProcessor->parameters, ODParameterID[oParameter_DelayType]);
    
    mFxTypeComboBox->setBounds(getWidth() - width, 0, width - 7, getHeight()-7);
    
    mFxTypeComboBox->addItem("DELAY", 1);
    mFxTypeComboBox->addItem("CHORUS", 2);
    mFxTypeComboBox->addItem("Sweet Pan", 3);
    mFxTypeComboBox->setSelectedItemIndex((int)mProcessor->getParameter(oParameter_DelayType), dontSendNotification);
    addAndMakeVisible(mFxTypeComboBox);
    
}
ODCenterPanelMenuBar::~ODCenterPanelMenuBar()
{
    
}

void ODCenterPanelMenuBar::addFxTypeComboBoxListener(ComboBox::Listener* inListener)
{
    mFxTypeComboBox->addListener(inListener);
}
void ODCenterPanelMenuBar::removeFxTypeComboBoxListener(ComboBox::Listener* inListener)
{
    mFxTypeComboBox->removeListener(inListener);
}
