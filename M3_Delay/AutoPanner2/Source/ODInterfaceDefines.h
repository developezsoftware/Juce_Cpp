/*
  ==============================================================================

    ODInterfaceDefines.h
    Created: 1 Jul 2019 1:22:36am
    Author:  Johnny Lopez

  ==============================================================================
*/

#pragma once

#define MAIN_PANEL_WIDTH   550
#define MAIN_PANEL_HEIGHT   500

#define TOP_PANEL_WIDTH   MAIN_PANEL_WIDTH
#define TOP_PANEL_HEIGHT   45

#define GAIN_PANEL_WIDTH   100
#define GAIN_PANEL_HEIGHT   MAIN_PANEL_HEIGHT - TOP_PANEL_HEIGHT

#define CENTER_PANEL_WIDTH   MAIN_PANEL_WIDTH - (GAIN_PANEL_WIDTH*2)
#define CENTER_PANEL_HEIGHT   GAIN_PANEL_HEIGHT

#define CENTER_PANEL_MENU_BAR_WIDTH   CENTER_PANEL_WIDTH
#define CENTER_PANEL_MENU_BAR_HEIGHT   35

#define FX_PANEL_WIDTH   CENTER_PANEL_WIDTH
#define FX_PANEL_HEIGHT   CENTER_PANEL_HEIGHT - CENTER_PANEL_MENU_BAR_HEIGHT
