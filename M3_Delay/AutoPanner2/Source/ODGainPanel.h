/*
  ==============================================================================

    ODGainPanel.h
    Created: 1 Jul 2019 1:14:47am
    Author:  Johnny Lopez

  ==============================================================================
*/

#pragma once

#include "ODPanelBase.h"
#include "ODParameterSlider.h"

class ODGainPanel :
   public ODPanelBase
{
public:
    ODGainPanel(AutoPannerAudioProcessor* inProcessor);
    ~ODGainPanel();
    
    void setParameterID(int inParameterID);
    
    void paint(Graphics& g) override;
    
    
    
private:
    
    ScopedPointer<ODParameterSlider> mSlider;
    
};
