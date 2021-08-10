/*
  ==============================================================================

    ODGain.h
    Created: 30 Jun 2019 10:06:56pm
    Author:  Johnny Lopez

  ==============================================================================
*/

#pragma once

class ODGain {
public:
    ODGain();
    ~ODGain();
    
    //function that applies gain
    void process(float* inAudio, float inGain, float* outAudio, int inNumSamplesToRender);
    
private:
    
};
