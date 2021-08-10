/*
 ==============================================================================
 
 LookAndFeel.h
 Created: 20 Jul 2019 1:51:27pm
 Author:  Johnny Lopez
 
 ==============================================================================
 */

#pragma once

#include "JuceHeader.h"
#include "ODInterfaceDefines.h"

class ODLookAndFeel :
public LookAndFeel_V4
{
public:
    
    ODLookAndFeel()
    {
        
        //store image assets
        mSliderImage = ImageCache::getFromMemory(BinaryData::Asset_8_png, BinaryData::Asset_8_pngSize);
 
    };
    virtual ~ODLookAndFeel(){};
    
    
    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, Slider& slider) override
    {
        const int numFrames = mSliderImage.getHeight() / mSliderImage.getWidth();
        const int frameIndex = (int)std::ceil(sliderPosProportional * (numFrames - 1));
        
        const float radius = jmin(width * 0.5, height * 0.5);
        const float centreX = x + width * 0.5f;
        const float centreY = y + height * 0.5f;
        const float rx = centreX - radius;
        const float ry = centreY - radius;
        
        g.drawImage(mSliderImage, rx, ry, 2*radius, 2*radius, 0, frameIndex * mSliderImage.getWidth(), mSliderImage.getWidth(), mSliderImage.getWidth());
    }
    
private:
    
    Image mSliderImage;
    
};
