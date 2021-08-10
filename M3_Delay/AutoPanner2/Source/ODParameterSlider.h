/*
  ==============================================================================

    ODParameterSlider.h
    Created: 1 Jul 2019 10:45:56am
    Author:  Johnny Lopez

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class ODParameterSlider
: public Slider
{
public:
    ODParameterSlider(AudioProcessorValueTreeState& stateToControl,
                     const String& parameterID);
    ~ODParameterSlider();
    
private:
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ODParameterSlider);
    
};
