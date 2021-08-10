/*
  ==============================================================================

    ODParameters.h
    Created: 1 Jul 2019 10:25:21am
    Author:  Johnny Lopez

  ==============================================================================
*/

#pragma once

enum ODParameter
{
    oParameter_InputGain = 0,
    oParameter_DelayTime,
    oParameter_DelayFeedback,
    oParameter_DelayWetdry,
    oParameter_DelayType,
//    oParameter_tempoSync,
    oParameter_OutPutGain,
    oParameter_ModulationRate,
    oParameter_ModulationDepth,
    oParameter_PanModulationRate,
    oParameter_PanModulationDepth,
    oParameter_Ddrive,
    oParameter_driveTone,
    oParameter_TotalNumParameters
    
};

static String ODParameterID [oParameter_TotalNumParameters] =
{
    "InputGain",
    "Time",
    "Feedback",
    "WetDry",
    "Type",
//    "TempoSync",
    "OutputGain",
    "ModRate",
    "ModDepth",
    "PanRate",
    "PanDepth",
    "Drive",
    "DriveTone"
};
