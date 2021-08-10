/*
  ==============================================================================

    ODGainPanel.cpp
    Created: 1 Jul 2019 1:14:47am
    Author:  Johnny Lopez

  ==============================================================================
*/

#include "ODGainPanel.h"
#include "ODParameters.h"
#include "ODHelperFunctions.h"


ODGainPanel::ODGainPanel(AutoPannerAudioProcessor* inProcessor) :
ODPanelBase(inProcessor)
{
    setSize(GAIN_PANEL_WIDTH, GAIN_PANEL_HEIGHT);
}


ODGainPanel::~ODGainPanel()
{
    
}

void ODGainPanel::paint(Graphics& g)
{
    ODPanelBase::paint(g);
    
    if(mSlider)
    {
        paintComponent(g, mSlider);
    }
}
void ODGainPanel::setParameterID(int inParameterID)
{
    mSlider = new ODParameterSlider(mProcessor->parameters, ODParameterID[inParameterID]);
    const int slider_size = 65;
    
    mSlider->setBounds((getWidth() * 0.5) - (slider_size * 0.5), (getHeight() * 0.5) - (slider_size * 0.5), slider_size, slider_size);
    
    addAndMakeVisible(mSlider);
}
