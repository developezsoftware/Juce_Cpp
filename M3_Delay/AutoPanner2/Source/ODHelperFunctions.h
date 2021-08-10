/*
  ==============================================================================

    ODHelperFunctions.h
    Created: 1 Jul 2019 5:13:04pm
    Author:  Johnny Lopez

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

inline void paintComponent(Graphics& g, Component* inComponent)
{
    const int x = inComponent->getX() - (inComponent->getWidth() * 0.25f);
    const int y = inComponent->getY() + inComponent->getHeight();
    const int w = inComponent->getWidth() * 1.5f;
    const int h = 20;
    
    const String label = inComponent->getName();

    
    g.setColour(Colours::navajowhite);
    g.drawFittedText(label, x, y+3, w, h, Justification::centred, 1);
}
