/*
  ==============================================================================

    ODPanelBase.h
    Created: 1 Jul 2019 1:13:40am
    Author:  Johnny Lopez

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

#include "PluginProcessor.h"
#include "ODInterfaceDefines.h"

class ODPanelBase
: public Component
{
public:
    ODPanelBase(AutoPannerAudioProcessor* inProcessor);
    ~ODPanelBase();
    
    void paint(Graphics& g) override;
    
protected:
    
    AutoPannerAudioProcessor* mProcessor;
    
};
