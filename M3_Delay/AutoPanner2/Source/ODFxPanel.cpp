/*
  ==============================================================================

    ODFxPanel.cpp
    Created: 1 Jul 2019 1:14:40am
    Author:  Johnny Lopez

  ==============================================================================
*/

#include "ODFxPanel.h"

#include "ODParameters.h"
#include "ODHelperFunctions.h"
#include "ODParameterComboBox.h"
#include "ODCenterPanel.h"


ODFxPanel::ODFxPanel(AutoPannerAudioProcessor* inProcessor) :
    ODPanelBase(inProcessor)
    //mStyle(oODFxPanelStyle_Delay)
{
    setSize(FX_PANEL_WIDTH, FX_PANEL_HEIGHT);
    
    const int currentStyle = (int)mProcessor->getParameter(oParameter_DelayType);
    setFxPanelStyle((ODFxPanelStyle)currentStyle);
    
    
//    syncCombo = new ODParameterComboBox(mProcessor->parameters, ODParameterID[oParameter_tempoSync]);
//    syncCombo->setSelectedItemIndex((int)mProcessor->getParameter(oParameter_tempoSync), dontSendNotification);
}

ODFxPanel::~ODFxPanel()
{
    
}

///DRAWS text depending on the style selected from the menu
void ODFxPanel::paint(Graphics& g)
{
    ODPanelBase::paint(g);
    
    
    switch (mStyle) {
        case oODFxPanelStyle_Delay:
            g.setFont(35);
            g.drawFittedText("DELAY", 0, 0, getWidth(), getHeight() * 0.25, Justification::centred, 1);
            std::cout << "Delay" << std::endl;
            g.setFont(15);
                        break;
        case oODFxPanelStyle_Chorus:
             g.setFont(35);
            g.drawFittedText("CHORUS", 0, 0, getWidth(), getHeight() * 0.25, Justification::centred, 1);
            std::cout << "CHORUS" << std::endl;
            g.setFont(15);
            break;
            
        case oODFxPanelStyle_Panner:
             g.setFont(31);
            g.drawFittedText("Sweet Pan", 0, 0, getWidth(), getHeight() * 0.10, Justification::centred, 1);
            g.setFont(15);
            break;
        default:
        case oODFxPanelStyle_TotalNumStyles:
            g.drawFittedText("ERRor", 0, 0, getWidth(), getHeight(), Justification::centred, 1);
            jassert(false);
            break;
            
    }
    
    //To paint the labels for Sliders
    for(int i = 0; i < mSliders.size(); i++)
    {
        paintComponent(g, mSliders[i]);
    }
}

//void ODFxPanel::setSyncVal(ODFxDelaySync syncVal)
//{
//    switch (syncVal) {
//        case ODFxDelaySync_Free:
//        {
//            mProcessor->syncVal = 1.0;
//            break;
//        }
//        case ODFxDelaySync_half:
//        {
//            mProcessor->syncVal = 0.5;
//            break;
//        }
//        case ODFxDelaySync_quater:
//        {
//            mProcessor->syncVal = 1.0;
//            break;
//        }
//        case ODFxDelaySync_eigth:
//        {
//            mProcessor->syncVal = 2.0;
//            break;
//        }
//        case ODFxDelaySync_sixteenth:
//        {
//            mProcessor->syncVal = 4.0;
//            break;
//        }
//
//        default:
//        {
//            std::cout << "error updating sync value" << std::endl;
//            break;
//        }
//    }
//}

void ODFxPanel::setFxPanelStyle(ODFxPanelStyle inStyle)
{
    mStyle = inStyle;
    
    mSliders.clear();
    
    const int slider_size = 65;
    int x = 30;
    int y = (getHeight()*0.25) - (slider_size * 0.5);
    
    
    
//    syncCombo->setBounds(x, y - 20, slider_size, 20);
//    syncCombo->addItem("Free", 1);
//    syncCombo->addItem("half", 2);
//    syncCombo->addItem("quater", 3);
//    syncCombo->addItem("eight", 4);
//    syncCombo->addItem("sixteenth", 5);
//
    switch (mStyle) {
        case oODFxPanelStyle_Delay:
        {
            
            // syncIndex = syncCombo->getSelectedItemIndex();
            //mProcessor->syncIndex = (int)syncCombo->getSelectedItemIndex();
            //addAndMakeVisible(syncCombo);
            // syncCombo->addListener(this);
            
            mProcessor->isDelay = 0;
            
            ODParameterSlider* time =
            new ODParameterSlider(mProcessor->parameters, ODParameterID[oParameter_DelayTime]);
            time->setBounds(x, y, slider_size, slider_size);
            //time->setRange(0, 1000,1);
            addAndMakeVisible(time);
            time->setRange(10.0f, 2000.0f, 1.0f);
            
            mSliders.add(time);
            
            
            time->setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, true, 100, 15);
//            if(mProcessor->syncVal != 0)
//            {
//                time->setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 0, 0);
//            }
            x = x + slider_size*1.75;
            
            //feedback slider
            ODParameterSlider* feedback =
            new ODParameterSlider(mProcessor->parameters, ODParameterID[oParameter_DelayFeedback]);
            feedback->setBounds(x, y, slider_size, slider_size);
            addAndMakeVisible(feedback);
            feedback->setRange(0.0f, 1.0f, 0.1f);
            
            mSliders.add(feedback);
            
            feedback->setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, true, 100, 15);
            x = x + slider_size*1.75;
            
           
            
            //wetDry Slider
            ODParameterSlider* wetDry = new ODParameterSlider(mProcessor->parameters, ODParameterID[oParameter_DelayWetdry]);
            
            wetDry->setBounds(x, y, slider_size, slider_size);
            addAndMakeVisible(wetDry);
            wetDry->setRange(0.0f, 1.0f, 0.1f);
            
            
            mSliders.add(wetDry);
            
            wetDry->setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, true, 100, 15);
            
            y = y + 125;
            x = 30;
            ODParameterSlider* prate =
            new ODParameterSlider(mProcessor->parameters, ODParameterID[oParameter_PanModulationRate]);
            prate->setBounds(x, y, slider_size, slider_size);
            addAndMakeVisible(prate);
            mSliders.add(prate);
            x = x + (slider_size*1.75);
            
            ODParameterSlider* pdepth =
            new ODParameterSlider(mProcessor->parameters, ODParameterID[oParameter_PanModulationDepth]);
            pdepth->setBounds(x, y, slider_size, slider_size);
            addAndMakeVisible(pdepth);
            mSliders.add(pdepth);
            x = x + (slider_size*1.75);
            
            y = y + 100;
            x = 30;
            
            ODParameterSlider* d_drive =
            new ODParameterSlider(mProcessor->parameters, ODParameterID[oParameter_Ddrive]);
            d_drive->setBounds(x, y, slider_size, slider_size);
            addAndMakeVisible(d_drive);
            mSliders.add(d_drive);
            x = x + (slider_size*1.75);
            
            //Drive tone knob
            ODParameterSlider* drive_t =
            new ODParameterSlider(mProcessor->parameters, ODParameterID[oParameter_driveTone]);
            drive_t->setBounds(x, y, slider_size, slider_size);
            addAndMakeVisible(drive_t);
            mSliders.add(drive_t);
            x = 30;

            
            
        }
            break;
        case oODFxPanelStyle_Chorus:
        {
            mProcessor->isDelay = 1;
            ODParameterSlider* rate =
            new ODParameterSlider(mProcessor->parameters, ODParameterID[oParameter_ModulationRate]);
            rate->setBounds(x, y, slider_size, slider_size);
            addAndMakeVisible(rate);
            mSliders.add(rate);
            x = x + (slider_size*1.75);
            
            ODParameterSlider* depth =
            new ODParameterSlider(mProcessor->parameters, ODParameterID[oParameter_ModulationDepth]);
            depth->setBounds(x, y, slider_size, slider_size);
            addAndMakeVisible(depth);
            mSliders.add(depth);
            x = x + (slider_size*1.75);
            
            ODParameterSlider* wetDry = new ODParameterSlider(mProcessor->parameters, ODParameterID[oParameter_DelayWetdry]);
            
            wetDry->setBounds(x, y, slider_size, slider_size);
            addAndMakeVisible(wetDry);
            wetDry->setRange(0.0f, 1.0f, 0.1f);
            
            mSliders.add(wetDry);
            wetDry->setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, true, 100, 15);
            
            y = y + 125;
            x = 30;
            ODParameterSlider* prate =
            new ODParameterSlider(mProcessor->parameters, ODParameterID[oParameter_PanModulationRate]);
            prate->setBounds(x, y, slider_size, slider_size);
            addAndMakeVisible(prate);
            mSliders.add(prate);
            x = x + (slider_size*1.75);
            
            ODParameterSlider* pdepth =
            new ODParameterSlider(mProcessor->parameters, ODParameterID[oParameter_PanModulationDepth]);
            pdepth->setBounds(x, y, slider_size, slider_size);
            addAndMakeVisible(pdepth);
            mSliders.add(pdepth);
            x = x + (slider_size*1.75);
            
            y = y + 100;
            x = 30;
            
            ODParameterSlider* d_drive =
            new ODParameterSlider(mProcessor->parameters, ODParameterID[oParameter_Ddrive]);
            d_drive->setBounds(x, y, slider_size, slider_size);
            addAndMakeVisible(d_drive);
            mSliders.add(d_drive);
            x = x + (slider_size*1.75);
            
            //Drive tone knob
            ODParameterSlider* drive_t =
            new ODParameterSlider(mProcessor->parameters, ODParameterID[oParameter_driveTone]);
            drive_t->setBounds(x, y, slider_size, slider_size);
            addAndMakeVisible(drive_t);
            mSliders.add(drive_t);
            x = 30;
        }
            break;
        case oODFxPanelStyle_Panner:
        {
            ODParameterSlider* rate =
            new ODParameterSlider(mProcessor->parameters, ODParameterID[oParameter_ModulationRate]);
            rate->setBounds(x, y, slider_size, slider_size);
            addAndMakeVisible(rate);
            mSliders.add(rate);
            x = x + (slider_size*2);
            
            ODParameterSlider* depth =
            new ODParameterSlider(mProcessor->parameters, ODParameterID[oParameter_ModulationDepth]);
            depth->setBounds(x, y, slider_size, slider_size);
            addAndMakeVisible(depth);
            mSliders.add(depth);
            x = x + (slider_size*2);
            
            ODParameterSlider* wetDry = new ODParameterSlider(mProcessor->parameters, ODParameterID[oParameter_DelayWetdry]);
            
            wetDry->setBounds(x, y, slider_size, slider_size);
            addAndMakeVisible(wetDry);
            
            mSliders.add(wetDry);
        }
            
            break;
        default:
        case oODFxPanelStyle_TotalNumStyles:
            
            jassert(false);
            break;
            
    }
    
    repaint();
}

//void ODFxPanel::addFxTypeComboBoxListener(ComboBox::Listener* inListener)
//{
//    syncCombo->addListener(inListener);
//}
//void ODFxPanel::removeFxTypeComboBoxListener(ComboBox::Listener* inListener)
//{
//    syncCombo->removeListener(inListener);
//}


void ODFxPanel::comboBoxChanged(ComboBox* comboBoxThatHasChanged)
{
    std::cout << comboBoxThatHasChanged->getName() << std::endl;
    
    
//        ODFxDelaySync syncVal = (ODFxDelaySync)comboBoxThatHasChanged->getSelectedItemIndex();
//        setSyncVal(syncVal);
    
        ODFxPanelStyle style = (ODFxPanelStyle)comboBoxThatHasChanged->getSelectedItemIndex();
        setFxPanelStyle(style);

    
}
