/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ODParameters.h"

//==============================================================================
AutoPannerAudioProcessor::AutoPannerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
                    parameters(*this, nullptr)
#endif
{
    initializeParameters();
    initializeDSP();
    
    mPresetManager = new OPPresetManager(this);
}

AutoPannerAudioProcessor::~AutoPannerAudioProcessor()
{
}

//==============================================================================
const String AutoPannerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AutoPannerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AutoPannerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AutoPannerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AutoPannerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AutoPannerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AutoPannerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AutoPannerAudioProcessor::setCurrentProgram (int index)
{
}

const String AutoPannerAudioProcessor::getProgramName (int index)
{
    return {};
}

void AutoPannerAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void AutoPannerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    for(int i = 0; i < 2; i++)
    {
        mDelay[i]->setSampleRate(sampleRate);
        mLfo[i]->setSampleRate(sampleRate);
        mPLfo[i]->setSampleRate(sampleRate);
    }
    
}

void AutoPannerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    for(int i = 0; i < 2; i++)
    {
        mDelay[i]->reset();
        mLfo[i]->reset();
        mPLfo[i]->reset();
    }
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AutoPannerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void AutoPannerAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    //AudioPlayHead* getPlayHead();
    //getPlayHead();
    myPlayHead = getPlayHead();
    myPlayHead->getCurrentPosition(myStruct);
    double mBpm = myStruct.bpm;
    //std::cout << mBpm;
    //std::cout << syncIndex << std::endl;
    
    

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
        if (syncVal != 0)
        {
            
            mDelayTime = (60.0/mBpm * 1000.0) / syncVal;
            setParameter(oParameter_DelayTime, mDelayTime / 1000.0);
        
        }
        mInputGain[channel]->process(channelData, getParameter(oParameter_InputGain), channelData, buffer.getNumSamples());
        
        /// to have asymetric rate on chorus mod
        float rate = (channel == 0) ? (0.21*getParameter(oParameter_ModulationRate)) : getParameter(oParameter_ModulationRate);
        
        /// Chorus Lfo which will get used only if selected in comboBox
        mLfo[channel]->process(rate, getParameter(oParameter_ModulationDepth), buffer.getNumSamples());
        
        mDelay[channel]->process(channelData, getParameter(oParameter_DelayTime), getParameter(oParameter_DelayFeedback), getParameter(oParameter_DelayWetdry),getParameter(oParameter_DelayType), isDrive, getParameter(oParameter_Ddrive),mLfo[channel]->getBuffer(), channelData, buffer.getNumSamples(), getParameter(oParameter_driveTone), syncVal);
        
        /// Panner LFO which will get used only if Panner is checked
        mPLfo[channel]->process(getParameter(oParameter_PanModulationRate), getParameter(oParameter_PanModulationDepth), buffer.getNumSamples());
        
        mPanner[channel]->process(channelData, oSimpleLinear, channelData, mPLfo[channel]->getBuffer(), isPanner, buffer.getNumSamples(), 1.0, channel);
        
        mOutputGain[channel]->process(channelData, getParameter(oParameter_OutPutGain), channelData, buffer.getNumSamples());

        // ..do something to the data...
    }
}

//==============================================================================
bool AutoPannerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* AutoPannerAudioProcessor::createEditor()
{
    return new AutoPannerAudioProcessorEditor (*this);
}

//==============================================================================
void AutoPannerAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    XmlElement preset("OD_StateInfo");
    
    XmlElement* presetBody = new XmlElement("OD_Preset");
    
    mPresetManager->getXmlForPreset(presetBody);
    
    preset.addChildElement(presetBody);
    copyXmlToBinary(preset, destData);
    
}

void AutoPannerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    XmlElement* xmlState = getXmlFromBinary(data, sizeInBytes);
    
    if(xmlState){
        forEachXmlChildElement(*xmlState, subChild){
            mPresetManager->loadPresetForXml(subChild);
        }
    }
    else{
        jassertfalse;
    }
}

void AutoPannerAudioProcessor::initializeDSP()
{
    /// Default state is panner off
    isPanner = false;
    isDrive = false;
    
    for(int i = 0; i < 2; i++)
    {
        mInputGain[i] = new ODGain();
        mOutputGain[i] = new ODGain();
        mDelay[i] = new ODDelay();
        mLfo[i] = new ODLfo();
        mPLfo[i] = new ODLfo();
        mPanner[i] = new OPPanner();
    }
}

void AutoPannerAudioProcessor::initializeParameters()
{
    for(int i = 0; i < oParameter_TotalNumParameters; i++)
    {
        if(i == oParameter_DelayTime)
        {
            parameters.createAndAddParameter(ODParameterID[i], ODParameterID[i], ODParameterID[i], NormalisableRange<float> (0.0f, 2000.0f), 500.0f, nullptr, nullptr);
        }
        else{
        parameters.createAndAddParameter(ODParameterID[i], ODParameterID[i], ODParameterID[i], NormalisableRange<float> (0.0f, 1.0f), 0.5f, nullptr, nullptr);
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AutoPannerAudioProcessor();
}
