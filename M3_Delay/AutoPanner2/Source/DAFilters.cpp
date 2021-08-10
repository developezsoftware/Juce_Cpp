/*
  ==============================================================================

    DAFilters.cpp
    Created: 1 Aug 2019 1:04:52pm
    Author:  Johnny Lopez

  ==============================================================================
*/

#include "DAFilters.h"
#include "JuceHeader.h"

IirLowpass::IirLowpass() : m_sr(44100.0), m_freq(5000)
{
    update();
}
IirLowpass::IirLowpass(double mSampleRate) : m_sr(mSampleRate), m_freq(5000)
{
    update();
}

IirLowpass::~IirLowpass()
{
    
}

void IirLowpass::setSampleRate(double mSampleRate)
{
    m_sr = mSampleRate;
}
void IirLowpass::update()
{
    double costh = 2.0 - cos(2.0 * M_PI * m_freq / m_sr);
    m_b = sqrt(costh * costh - 1.0) - costh;
    m_a = (1.0 + m_b);
}

void IirLowpass::process(float *inBuffer, float *outBuffer, int totalNumSamples, float cutOff)
{
    
    if (cutOff != m_freq)
    {
        m_freq = cutOff;
        update();
    }
    for(int i = 0; i < totalNumSamples; i++) {
        m_del = m_a * inBuffer[i] - m_b * m_del;
        outBuffer[i] = m_del;
    }
}
