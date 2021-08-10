/*
  ==============================================================================

    ODTopPanel.h
    Created: 1 Jul 2019 1:15:09am
    Author:  Johnny Lopez

  ==============================================================================
*/

#pragma once

#include "ODPanelBase.h"

class ODTopPanel
: public ODPanelBase,
  public Button::Listener,
  public ComboBox::Listener
{
public:
    ODTopPanel(AutoPannerAudioProcessor* inProcessor);
    ~ODTopPanel();
    
    void paint(Graphics& g) override;
    
    void buttonClicked(Button* b) override;
    
    void comboBoxChanged(ComboBox* comboBoxThatHasChanged) override;
    
private:
    
    void displaySaveAsPopup();
    
    void updatePresetComboBox();
    
    ScopedPointer<ComboBox> mPresetDisplay;
    
    ScopedPointer<TextButton> mNewPreset, mSavePreset, mSaveAsPreset;
    
    
};
