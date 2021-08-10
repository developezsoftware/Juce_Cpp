/*
  ==============================================================================

    ODParameterSlider.cpp
    Created: 1 Jul 2019 10:45:56am
    Author:  Johnny Lopez

  ==============================================================================
*/

#include "ODParameterSlider.h"

ODParameterSlider::ODParameterSlider(AudioProcessorValueTreeState& stateToControl,
                                   const String& parameterID)
: juce::Slider(parameterID)
{
    setSliderStyle(SliderStyle::RotaryHorizontalVerticalDrag);
    setColour(3, Colours::navajowhite);
    setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 0, 0);
    //setPopupDisplayEnabled(true, true, this);
    
    setRange(0.0f, 1.0f, 0.001f);
    
    mAttachment = new AudioProcessorValueTreeState::SliderAttachment(stateToControl, parameterID, *this);
}

ODParameterSlider::~ODParameterSlider()
{
    
}
