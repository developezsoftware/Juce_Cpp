/*
  ==============================================================================

    ODCenterPanelMenuBar.h
    Created: 1 Jul 2019 1:14:33am
    Author:  Johnny Lopez

  ==============================================================================
*/

///// Deals with center panel including the fx combo box which
/// allows switching between the delay and chorus
#pragma once

#include "ODPanelBase.h"
#include "ODParameterComboBox.h"

class ODCenterPanelMenuBar
: public ODPanelBase
{
public:
    ODCenterPanelMenuBar(AutoPannerAudioProcessor* inProcessor);
    ~ODCenterPanelMenuBar();
    
    void addFxTypeComboBoxListener(ComboBox::Listener* inListener);
    void removeFxTypeComboBoxListener(ComboBox::Listener* inListener);
    
    
private:
    
    ScopedPointer<ODParameterComboBox> mFxTypeComboBox;
    
    
};
