/*
  ==============================================================================

    ODGain.cpp
    Created: 30 Jun 2019 10:06:56pm
    Author:  Johnny Lopez

  ==============================================================================
*/

#include "ODGain.h"

#include "JuceHeader.h"

ODGain::ODGain()
{
    
}

ODGain::~ODGain()
{
    
}

void ODGain::process(float *inAudio, float inGain, float *outAudio, int inNumSamplesToRender)
{
    float gainMapped = jmap(inGain, 0.0f, 1.0f, -24.0f, 24.0f);
    gainMapped = Decibels::decibelsToGain(gainMapped, -24.0f);
    
    for(int i = 0; i < inNumSamplesToRender; i++)
    {
        outAudio[i] = inAudio[i] * gainMapped;
    }
}

