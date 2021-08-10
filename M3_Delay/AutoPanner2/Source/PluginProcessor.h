/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "ODGain.h"
#include "ODDelay.h"
#include "ODLfo.h"
#include "OPPanner.h"

#include "PresetManager.h"

//==============================================================================
/**
*/
class AutoPannerAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    AutoPannerAudioProcessor();
    ~AutoPannerAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    AudioProcessorValueTreeState parameters;
    
    OPPresetManager* getPresetManager()
    {
        return mPresetManager;
    }
    
    bool isPanner;
    bool isDrive;
    float syncIndex;
    double syncVal{0};
    float mDelayTime;
    
    int isDelay{0};
    //struct JUCE_API  CurrentPositionInfo;
    //AudioPlayHead* getPlayHead();
    AudioPlayHead::CurrentPositionInfo myStruct;
    AudioPlayHead* myPlayHead;
 // const AudioPlayHead::CurrentPositionInfo* result;

private:
    
    /** internal */
    void initializeDSP();
    void initializeParameters();
    
    
    
    ScopedPointer<ODGain> mInputGain[2];
    ScopedPointer<ODGain> mOutputGain[2];
    ScopedPointer<ODDelay> mDelay[2];
    ScopedPointer<ODLfo> mLfo[2];
    ScopedPointer<ODLfo> mPLfo[2];
    ScopedPointer<OPPanner> mPanner[2];
   
    
    
    ScopedPointer<OPPresetManager> mPresetManager;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AutoPannerAudioProcessor)
};
