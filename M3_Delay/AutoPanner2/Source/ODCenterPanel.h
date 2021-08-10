/*
  ==============================================================================

    ODCenterPanel.h
    Created: 1 Jul 2019 1:14:20am
    Author:  Johnny Lopez

  ==============================================================================
*/

#pragma once

#include "ODPanelBase.h"
#include "ODCenterPanelMenuBar.h"
#include "ODFxPanel.h"

class ODCenterPanel
: public ODPanelBase
{
public:
    
    ODCenterPanel(AutoPannerAudioProcessor* inProcessor);
    ~ODCenterPanel();
    
private:
    
    ScopedPointer<ODCenterPanelMenuBar> mMenuBar;
    ScopedPointer<ODFxPanel> mFxPanel;
};
