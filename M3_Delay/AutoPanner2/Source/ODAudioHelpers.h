/*
  ==============================================================================

    ODAudioHelpers.h
    Created: 30 Jun 2019 10:06:14pm
    Author:  Johnny Lopez

  ==============================================================================
*/

#pragma once

#define oParameterSmoothingCoeff_Generic 0.04
#define oParameterSmoothingCoeff_Fine 0.002

const int maxBufferDelaySize = 192000;

const static double oPI = 3.14159265359;
const static double o2PI = 6.28318530718;

inline float od_linear_interp(float v0, float v1, float t)
{
    return (1 - t) * v0 + (t * v1);
}

//struct fo panning

typedef struct panpos
{
    double left;
    double right;
} PANPOS;
