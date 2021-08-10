/*
  ==============================================================================

    ODTopPanel.cpp
    Created: 1 Jul 2019 1:15:09am
    Author:  Johnny Lopez

  ==============================================================================
*/

#include "ODTopPanel.h"


ODTopPanel:: ODTopPanel(AutoPannerAudioProcessor* inProcessor) :
    ODPanelBase(inProcessor)
{
    setSize(TOP_PANEL_WIDTH, TOP_PANEL_HEIGHT);
    
    int button_x = 15;
    int button_y = 10;
    int button_w = 55;
    int button_h = 25;
    
    mNewPreset = new TextButton();
    mNewPreset->setButtonText("NEW");
    mNewPreset->setBounds(button_x, button_y, button_w, button_h);
    mNewPreset->addListener(this);
    addAndMakeVisible(mNewPreset);
    button_x = button_x + button_w;
    
    mSavePreset = new TextButton();
    mSavePreset->setButtonText("SAVE");
    mSavePreset->setBounds(button_x, button_y, button_w, button_h);
    mSavePreset->addListener(this);
    addAndMakeVisible(mSavePreset);
    button_x = button_x + button_w;
    
    mSaveAsPreset = new TextButton();
    mSaveAsPreset->setButtonText("SAVE AS");
    mSaveAsPreset->setBounds(button_x, button_y, button_w, button_h);
    mSaveAsPreset->addListener(this);
    addAndMakeVisible(mSaveAsPreset);
    button_x = button_x + button_w;
    
    const int comboBox_w = 150;
    const int comboBox_x = TOP_PANEL_WIDTH * 0.5 - comboBox_w * 0.5;
    
    mPresetDisplay = new ComboBox();
    mPresetDisplay->setBounds(comboBox_x, button_y, comboBox_w, button_h);
    mPresetDisplay->addListener(this);
    addAndMakeVisible(mPresetDisplay);
    
    updatePresetComboBox();
}
ODTopPanel::~ODTopPanel()
{
    
}

void ODTopPanel::paint(Graphics& g)
{
    ODPanelBase::paint(g);
    
    g.drawFittedText("DA MoDelay .", 0, 0, getWidth(), getHeight(), Justification::centredRight, 1);
}

void ODTopPanel::buttonClicked(Button* b)
{
    OPPresetManager* presetManager = mProcessor->getPresetManager();
    if(b == mNewPreset)
    {
        presetManager->createNewPreset();
        updatePresetComboBox();
    }
    else if(b == mSavePreset)
    {
        presetManager->savePreset();
    }
    else if(b == mSaveAsPreset)
    {
        displaySaveAsPopup();
        
    }
}

void ODTopPanel::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
{
    if(comboBoxThatHasChanged == mPresetDisplay)
    {
        OPPresetManager* presetManager = mProcessor->getPresetManager();
        const int index = mPresetDisplay->getSelectedItemIndex();
        presetManager->loadPreset(index);
    }
}


/// Poup when save as is selceted
void ODTopPanel::displaySaveAsPopup()
{
    OPPresetManager* presetManager = mProcessor->getPresetManager();
    
    String currentPresetName = presetManager->getCurrentPresetName();
    
    AlertWindow window("Save As", "Please enter a name for your Preset", AlertWindow::NoIcon);
    
    window.centreAroundComponent(this, getWidth(), getHeight());
    window.addTextEditor("presetName", currentPresetName, "preset name: ");
    window.addButton("Confirm", 1);
    window.addButton("Cancle", 0);
    
    if(window.runModalLoop()){
        
        String presetName = window.getTextEditor("presetName")->getText();
        presetManager->saveAsPreset(presetName);
        
        updatePresetComboBox();
    }
}

void ODTopPanel::updatePresetComboBox()
{
    OPPresetManager* presetManager = mProcessor->getPresetManager();
    String presetName = presetManager->getCurrentPresetName();
    
    mPresetDisplay->clear(dontSendNotification);
    
    
    const int numPresets = presetManager->getNumberOfPresets();
    
    for(int i = 0; i < numPresets; i++)
    {
        mPresetDisplay->addItem(presetManager->getPresetName(i), (i+1));
    }
    
    mPresetDisplay->setText(presetManager->getCurrentPresetName());
}
