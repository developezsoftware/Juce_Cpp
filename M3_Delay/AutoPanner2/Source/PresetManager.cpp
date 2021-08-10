/*
  ==============================================================================

    PresetManager.cpp
    Created: 2 Jul 2019 11:28:30am
    Author:  Johnny Lopez

  ==============================================================================
*/

#include "PresetManager.h"

#if JUCE_WINDOWS
static const String directorySeparator = "\\";
#elif JUCE_MAC
static const String directorySeparator = "/";
#endif

OPPresetManager::OPPresetManager(AudioProcessor* inProcessor) :
    mCurrentPresetIsSaved(false),
    mCurrentPresetName("Untitled"),
    mProcessor(inProcessor)
{
    const String pluginName = (String) mProcessor->getName();
    
    //Here to set file directory
    mPresetDirectory =
    (File::getSpecialLocation(File::userDesktopDirectory)).getFullPathName()+ directorySeparator + pluginName;
    
    if(!File(mPresetDirectory).exists()){
        File(mPresetDirectory).createDirectory();
    }
    
    storeLocalPreset();
}
OPPresetManager::~OPPresetManager(){
    
}

void OPPresetManager::getXmlForPreset(XmlElement* inElement)
{
    const int numParameters = mProcessor->getNumParameters();
    
    for(int i = 0; i < numParameters; i++)
    {
        inElement->setAttribute(mProcessor->getParameterName(i), mProcessor->getParameter(i));
    }
}

void OPPresetManager::loadPresetForXml(XmlElement* inElement)
{
    mCurrentPresetXml = inElement;
    
    for(int i = 0; i < mCurrentPresetXml->getNumAttributes(); i++)
    {
        const String name = mCurrentPresetXml->getAttributeName(i);
        const float value = mCurrentPresetXml->getDoubleAttribute(name);
        
        for(int j = 0; j < mProcessor->getNumParameters(); j++)
        {
            if(mProcessor->getParameterName(j) == name)
            {
                mProcessor->setParameterNotifyingHost(j, value);
            }
        }
    }
}

int OPPresetManager::getNumberOfPresets()
{
    return mLocalPresets.size();
}

String OPPresetManager::getPresetName(int inPresetIndex)
{
    return mLocalPresets[inPresetIndex].getFileNameWithoutExtension();
}

void OPPresetManager::createNewPreset()
{
    const int numParameters = mProcessor->getNumParameters();
    
    for(int i = 0; i < numParameters; i++)
    {
        mProcessor->setParameterNotifyingHost(i, mProcessor->getParameterDefaultValue(i));
    }
    
    mCurrentPresetIsSaved = false;
    mCurrentPresetName = "Untitled";
}

void OPPresetManager::savePreset()
{
    MemoryBlock destinationData;
    mProcessor->getStateInformation(destinationData);
    
    mCurrentlyLoadedPreset.deleteFile();
    
    mCurrentlyLoadedPreset.appendData(destinationData.getData(), destinationData.getSize());
    
    mCurrentPresetIsSaved = true;
}

void OPPresetManager::saveAsPreset(String inPresetName)
{
    File presetFile = File(mPresetDirectory + directorySeparator + inPresetName +PRESET_FILE_EXTENTION);
    
    if(!presetFile.exists()){
        presetFile.create();
    } else {
        presetFile.deleteFile();
    }
    
    MemoryBlock destinationData;
    mProcessor->getStateInformation(destinationData);
    
    presetFile.appendData(destinationData.getData(), destinationData.getSize());
    
    mCurrentPresetIsSaved = true;
    mCurrentPresetName = inPresetName;
    
    storeLocalPreset();
}

void OPPresetManager::loadPreset(int inPresetIndex)
{
    mCurrentlyLoadedPreset = mLocalPresets[inPresetIndex];
    MemoryBlock presetBinary;
    
    if(mCurrentlyLoadedPreset.loadFileAsData(presetBinary))
    {
        mCurrentPresetIsSaved = true;
        mCurrentPresetName = getPresetName(inPresetIndex);
        mProcessor->setStateInformation(presetBinary.getData(), (int)presetBinary.getSize());
    }
}

bool OPPresetManager::getIsCurrentPresetSaved()
{
    return mCurrentPresetIsSaved;
}

String OPPresetManager::getCurrentPresetName()
{
    return mCurrentPresetName;
}

void OPPresetManager::storeLocalPreset()
{
    mLocalPresets.clear();
    
    for(DirectoryIterator di (File(mPresetDirectory),
                              false,
                              "*"+(String)PRESET_FILE_EXTENTION,
                            File::TypesOfFileToFind::findFiles); di.next();)
    {
        File preset = di.getFile();
        mLocalPresets.add(preset);
    }
}
