/*
  ==============================================================================

    ODDelay.cpp
    Created: 30 Jun 2019 10:07:05pm
    Author:  Johnny Lopez

  ==============================================================================
*/

#include "ODDelay.h"
#include "JuceHeader.h"
#include "ODAudioHelpers.h"

ODDelay::ODDelay()
: mSampleRate(-1),
  mFeedBackSample(0.0),
  mTimeSmoothed(0),
  mDelayIndex(0)

{
    mBuffer = new float[maxBufferDelaySize];
    //mLowPass = std::make_unique<IirLowpass>();

}

ODDelay::~ODDelay()
{
    delete [] mBuffer;
}

void ODDelay::setSampleRate(double inSampleRate)
{
    mSampleRate = inSampleRate;
    //mLowPass->setSampleRate(inSampleRate);
}

void ODDelay::reset()
{
    mTimeSmoothed = 0.0f;
    zeromem(mBuffer, (sizeof(float) * maxBufferDelaySize));
}

////Main Process Block
void ODDelay::process(float *inAudio, float inTime, float feedBack, float inWetDry, float inType, bool isRect,
                      float rectValue, float* inModulationBuffer, float *outAudio, int inNumSamplesToRender, float cutOff, float syncVal)
{
    const float wet = inWetDry;
    const float dry = 1.0f - wet;
    const float feedbackMapped = jmap(feedBack, 0.0f, 1.0f, 0.0f, 0.95f);
    
    const float mCutoff = jmap(cutOff, 0.0f, 1.0f, 400.0f, 10000.0f);
    
    const float rectification = (isRect) ? jmap(rectValue, 0.0f,1.0f,0.1f,1.0f) : -1.0;
   
    const float inTimeMapped = inTime * 2.0;
    
    for(int i = 0; i < inNumSamplesToRender; i++)
    {
        if (syncVal != 0 && (int)inType == oODDelayType_Delay)
        {
            mTimeSmoothed = inTimeMapped;
            //std::cout << mTimeSmoothed << std::endl;
        }
        
        else if((int)inType == oODDelayType_Delay)
        {
            mTimeSmoothed = mTimeSmoothed - oParameterSmoothingCoeff_Fine *(mTimeSmoothed - inTimeMapped);
        } else if((int)inType == ODDelayType_Chorus) {
            const double delayTimeModulation = (0.003 + (0.002 * inModulationBuffer[i]));
            mTimeSmoothed = mTimeSmoothed - oParameterSmoothingCoeff_Fine*(mTimeSmoothed - (delayTimeModulation));
        }
//        const double delayTimeModulation = (inTime + (0.002 * inModulationBuffer[i]));
//        mTimeSmoothed = mTimeSmoothed - oParameterSmoothingCoeff_Fine * (mTimeSmoothed - (delayTimeModulation));
        const double delayTimeInSamples =  (mTimeSmoothed * mSampleRate);
        
        ///// This is mainly where the rectification happens
        const double sample = (getInterpolatedSample(delayTimeInSamples) <= 0) ? getInterpolatedSample(delayTimeInSamples) * (-rectification) : getInterpolatedSample(delayTimeInSamples);
        
        
        ///////////////
        /////Checks if rectification is activated to activate onepole filter filter
        /////////////
        if(isRect)
        {
        
            if (mCutoff != m_freq)
            {
                m_freq = mCutoff;
                double costh = 2.0 - cos(2.0 * M_PI * m_freq / mSampleRate);
                m_b = sqrt(costh * costh - 1.0) - costh;
                m_a = (1.0 + m_b);
            }
            
            m_del = m_a * inAudio[i] - m_b * m_del;
            //outAudio[i] = m_del;
            
            
            
            
            ///////////////////
            mBuffer[mDelayIndex] = m_del + (mFeedBackSample * feedbackMapped);
        }
        
        else if(!isRect)
        {
        ///// PUT INAUDIO[I] BACK IF THIS DOESN't Work!!!!!!!!!!!!!!!!!!!!!!!!!
        mBuffer[mDelayIndex] = inAudio[i] + (mFeedBackSample * feedbackMapped);
        
        }
        
        mFeedBackSample = sample;
        
        
        
        outAudio[i] = (inAudio[i]*dry + sample*wet);
        
        mDelayIndex = mDelayIndex + 1;
        
        if(mDelayIndex >= maxBufferDelaySize){
            mDelayIndex = mDelayIndex - maxBufferDelaySize;
        }
    }

}

double ODDelay::getInterpolatedSample(float inDelayTimeInSamples)
{
    double readPosition = (double)mDelayIndex - inDelayTimeInSamples;
    
    if(readPosition < 0)
    {
        readPosition = readPosition + maxBufferDelaySize;
    }
    
    int index_y0 = (int)readPosition - 1;
    if(index_y0 <= 0)
    {
        index_y0 = index_y0 + maxBufferDelaySize;
    }
    
    int index_y1 = readPosition;
    if(index_y1 > maxBufferDelaySize)
    {
        index_y1 = index_y1 - maxBufferDelaySize;
    }
    
    const float sample_y0 = mBuffer[index_y0];
    const float sample_y1 = mBuffer[index_y1];
    const float t = readPosition - (int)readPosition;
    
    /////////////////// the od_linear_interp uses a function defined in a different file which
    ////////////////// takes care of the interpolation
    double outSample = od_linear_interp(sample_y0, sample_y1, t);
    
    return outSample;
}
