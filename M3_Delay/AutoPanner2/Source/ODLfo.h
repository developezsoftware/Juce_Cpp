/*
  ==============================================================================

    ODLfo.h
    Created: 30 Jun 2019 10:06:45pm
    Author:  Johnny Lopez

  ==============================================================================
*/

#pragma once
#include "ODAudioHelpers.h"

class ODLfo
{
public:
    ODLfo();
    ~ODLfo();
    
    void reset();
    void setSampleRate(double inSampleRate);
    
    void process(float inRate, float inDepth, int inNumSamples);
    
    float* getBuffer();
    
private:
    double mSampleRate;
    
    float mPhase;
    
    float mBuffer[maxBufferDelaySize];
    
};
