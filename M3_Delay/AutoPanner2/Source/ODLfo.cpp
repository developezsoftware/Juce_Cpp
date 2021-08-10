/*
  ==============================================================================

    ODLfo.cpp
    Created: 30 Jun 2019 10:06:45pm
    Author:  Johnny Lopez

  ==============================================================================
*/

#include "ODLfo.h"

#include "JuceHeader.h"

ODLfo::ODLfo()
{
    reset();
}

ODLfo::~ODLfo()
{
    
}

void ODLfo::reset()
{
    mPhase = 0.0f;
    zeromem(mBuffer, sizeof(float) * maxBufferDelaySize);
}
void ODLfo::setSampleRate(double inSampleRate)
{
    mSampleRate = inSampleRate;
}

void ODLfo::process(float inRate, float inDepth, int inNumSamples)
{
    const float rate = jmap(inRate, 0.0f, 1.0f, 0.01f, 10.0f);
    
    for(int i = 0; i < inNumSamples; i++)
    {
        mPhase = mPhase + (rate / mSampleRate);
        
        if(mPhase > 1.0f)
        {
            mPhase = mPhase - 1.0f;
        }
        
        const float lfoPosition = sinf(mPhase * o2PI) * inDepth;
        mBuffer[i] = lfoPosition;
    }
    
    
}

float* ODLfo::getBuffer()
{
    return mBuffer;
}
