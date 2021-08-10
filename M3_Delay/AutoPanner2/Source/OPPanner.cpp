/*
  ==============================================================================

    OPPanner.cpp
    Created: 2 Jul 2019 2:44:01pm
    Author:  Johnny Lopez

  ==============================================================================
*/

#include "OPPanner.h"
#include "ODDelay.h"


OPPanner::OPPanner()
{
    
}
OPPanner::~OPPanner()
{
    
}

void OPPanner::process(float* inAudio, oTypePanner, float* outAudio, float* modulationBuffer, bool inPanner, int numSamplesToRender, double panposOneToOne, int channel)
{
    mPanSmoothed = 0.0f;
    if(inPanner){
        for(int i = 0; i < numSamplesToRender; i++)
        {
            const double panModulation = modulationBuffer[i];
            //mPanSmoothed = mPanSmoothed - oParameterSmoothingCoeff_Fine*(mPanSmoothed - (panModulation));
            //const int modPos = mPanSmoothed;
            simpleLinearPan(panModulation);
            if(channel == 0)
            {
                outAudio[i] = inAudio[i] * mPanpos.left;
            } else
            {
                outAudio[i] = inAudio[i] * mPanpos.right;
            }
        }
    }
}

void OPPanner::simpleLinearPan(double sPanpos)
{
    sPanpos *= 0.5;
    mPanpos.left = sPanpos - 0.5;
    mPanpos.right = sPanpos + 0.5;
}

void OPPanner::constPowerPan(double sPanpos)
{
    
}
