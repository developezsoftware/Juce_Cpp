/*
  ==============================================================================

    ODMainPanel.h
    Created: 1 Jul 2019 1:13:50am
    Author:  Johnny Lopez

  ==============================================================================
*/

#pragma once

#include "ODPanelBase.h"
#include "ODTopPanel.h"
#include "ODGainPanel.h"
#include "ODCenterPanel.h"


//// takes care of setting up the main panels
class ODMainPanel
: public ODPanelBase
{
public:
    ODMainPanel(AutoPannerAudioProcessor* inProcessor);
    ~ODMainPanel();
    
    float thisSyncVal;
private:
    
    ScopedPointer<ODTopPanel> mTopPanel;
    ScopedPointer<ODGainPanel> mInputGainPanel;
    ScopedPointer<ODGainPanel> mOutputGainPanel;
    ScopedPointer<ODCenterPanel> mCenterPanel;
    
};
