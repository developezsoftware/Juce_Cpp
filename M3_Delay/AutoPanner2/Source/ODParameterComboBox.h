/*
  ==============================================================================

    ODParameterComboBox.h
    Created: 1 Jul 2019 10:46:24am
    Author:  Johnny Lopez

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class ODParameterComboBox
: public ComboBox
{
public:
    ODParameterComboBox(AudioProcessorValueTreeState& stateToControl, const String& parameterID);
    ~ODParameterComboBox();
    
private:
    
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> mAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ODParameterComboBox);
};
