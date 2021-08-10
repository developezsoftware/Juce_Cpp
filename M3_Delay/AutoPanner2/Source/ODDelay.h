/*
  ==============================================================================

    ODDelay.h
    Created: 30 Jun 2019 10:07:05pm
    Author:  Johnny Lopez
 
    Delay class with distortion on the delayed signal
    the type of distortion used is rectification
    and with the option to control tone thru a one pole lowpass filter

  ==============================================================================
*/

#pragma once
#include "ODAudioHelpers.h"
#include "DAFilters.h"
#include "memory"

enum ODDelayType
{
    oODDelayType_Delay = 0,
    ODDelayType_Chorus
    //oDDelayType_Panner
};
class ODDelay
{
public:
    ODDelay();
    ~ODDelay();
    
    
    void setSampleRate(double inSampleRate);
    void reset();
    
    //This is the main process to which all the necessary parameters are passed
    //in PluginProcessor and PluginEditor this process should be passed the audio buffers
    // and required parameters.
    void process(float* inAudio,
                 float inTime,
                 float feedBack,
                 float inWetDry,
                 float inType,
                 bool isRect,
                 float rectValue,
                 float* inModulationBuffer,
                 float* outAudio,
                 int inNumSamplesToRender,
                 float cutOff,
                 float syncVal);
    
    
    
private:
    
    /* internal */
    // Function is used to obtain interpolated samples
    // This part of the code was inspired by work from Bruce Dawson
    // Who uses interpolation to obtain better time modulation for the delay
    double getInterpolatedSample(float inDelayTimeInSamples);
    
    double mSampleRate;
    //double mBuffer[maxBufferDelaySize];
    float* mBuffer;
    double mFeedBackSample;
    
    float mTimeSmoothed;
    
    int mDelayIndex;
    
    
    //////
    
    float m_del {0.0};
    float m_a{0}, m_b{0};
    float m_sr, m_freq;
    ///////////
    
   // std::unique_ptr<IirLowpass> mLowPass;
    
};
