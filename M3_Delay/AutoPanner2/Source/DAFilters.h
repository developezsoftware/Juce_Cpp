/*
  ==============================================================================

    DAFilters.h
    Created: 1 Aug 2019 1:04:52pm
    Author:  Johnny Lopez

  ==============================================================================
*/

#pragma once

class IirLowpass
{
public:
    IirLowpass();
    IirLowpass(double mSapleRate);
    ~IirLowpass();
    
    void process(float* inBuffer, float* outBuffer, int totalNumSamples, float cutOff);
    void update();
    void setSampleRate(double mSampleRate);
private:
    float m_del {0.0};
    float m_a{0}, m_b{0};
    float m_sr, m_freq{5000.0};
    
    
};
