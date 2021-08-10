/*
  ==============================================================================

    PresetManager.h
    Created: 2 Jul 2019 11:28:30am
    Author:  Johnny Lopez

  ==============================================================================
*/

// Stores presets into an xml

#pragma once

#include "JuceHeader.h"

#define PRESET_FILE_EXTENTION ".opf"

class OPPresetManager
{
public:
    OPPresetManager(AudioProcessor* inProcessor);
    ~OPPresetManager();
    
    //gets the xml ready for storing
    void getXmlForPreset(XmlElement* inElement);
    
    void loadPresetForXml(XmlElement* inElement);
    
    int getNumberOfPresets();
    
    String getPresetName(int inPresetIndex);
    
    void createNewPreset();
    
    void savePreset();
    
    void saveAsPreset(String inPresetName);
    
    void loadPreset(int inPresetIndex);
    
    bool getIsCurrentPresetSaved();
    
    String getCurrentPresetName();
    
private:
    
    void storeLocalPreset();
    
    bool mCurrentPresetIsSaved;
    
    File mCurrentlyLoadedPreset;
    
    Array<File> mLocalPresets;
    
    String mCurrentPresetName;
    
    String mPresetDirectory;
    
    
    XmlElement* mCurrentPresetXml;
    AudioProcessor* mProcessor;
    
};
