/*
  ==============================================================================

    ODParameterComboBox.cpp
    Created: 1 Jul 2019 10:46:24am
    Author:  Johnny Lopez

  ==============================================================================
*/

#include "ODParameterComboBox.h"

ODParameterComboBox::ODParameterComboBox(AudioProcessorValueTreeState& stateControl, const String& parameterID)
:   juce::ComboBox(parameterID)
{
    mAttachment = new AudioProcessorValueTreeState::ComboBoxAttachment(stateControl, parameterID, *this);
    
}

ODParameterComboBox::~ODParameterComboBox()
{
    
}
