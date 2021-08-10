/*
  ==============================================================================

    ODFxPanel.h
    Created: 1 Jul 2019 1:14:40am
    Author:  Johnny Lopez

  ==============================================================================
*/

#pragma once

#include "ODPanelBase.h"
#include "ODParameterSlider.h"
#include "ODParameterComboBox.h"

enum ODFxPanelStyle
{
    oODFxPanelStyle_Delay,
    oODFxPanelStyle_Chorus,
    oODFxPanelStyle_Panner,
    oODFxPanelStyle_TotalNumStyles
};

enum ODFxDelaySync
{
    ODFxDelaySync_Free = 1,
    ODFxDelaySync_half,
    ODFxDelaySync_quater,
    ODFxDelaySync_eigth,
    ODFxDelaySync_sixteenth
};

class ODFxPanel :
    public ODPanelBase,
    public ComboBox::Listener
{
public:
    ODFxPanel(AutoPannerAudioProcessor* inProcessor);
    ~ODFxPanel();
    
    void paint(Graphics& g) override;
    
    void setFxPanelStyle(ODFxPanelStyle inStyle);
    
    void setSyncVal(ODFxDelaySync syncVal);
    
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    
//    void addFxTypeComboBoxListener(ComboBox::Listener* inListener);
//    void removeFxTypeComboBoxListener(ComboBox::Listener* inListener);
    
    
    private :
    
    ODFxPanelStyle mStyle;
    ODFxDelaySync mSyncVal;
    
    ScopedPointer<ODParameterComboBox> syncCombo;
    
    
    
    float syncIndex;
    
    OwnedArray<ODParameterSlider> mSliders;
    
};
