/*
  ==============================================================================

    OPPanner.h
    Created: 2 Jul 2019 2:44:01pm
    Author:  Johnny Lopez

  ==============================================================================
*/

#pragma once

#include "ODAudioHelpers.h"

enum oTypePanner
{
    oSimpleLinear
};

class OPPanner
{
public:
    
    OPPanner();
    ~OPPanner();
    
    void process(float* inAudio, oTypePanner, float* outAudio, float* modulationBuffer, bool inPanner, int numSamplesToRender, double panposOneToOne, int channel);
    
    void simpleLinearPan(double sPanpos);
    
    void constPowerPan(double sPanpos);
    
    
private:
    
    PANPOS mPanpos;
    
    double mPanSmoothed;
    
};
