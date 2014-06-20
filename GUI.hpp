// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: GUI.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines GUI class, and GUILayer class. 
// ================================================ //

#ifndef __GUI_HPP__
#define __GUI_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

class GUILayer;
class Widget;
class Config;

// ================================================ //

typedef std::vector<std::shared_ptr<Widget>> WidgetList;
typedef std::vector<std::shared_ptr<GUILayer>> GUILayerList;
typedef std::vector<std::string> StringList;

// ================================================ //

// A polymorphic, abstract class defining a layer within a GUI system. 
// A GUI object holds a list of GUILayers, and only displays one GUILayer at a time. 
// GUILayer holds a list of Widgets which are updated each frame, and rendered if 
// it's the active GUILayer. 
class GUILayer
{
public:
	// Initializes ID to zero. 
	explicit GUILayer(void);

	// Empty destructor. 
	virtual ~GUILayer(void);

	// Adds a new Widget smart pointer to the list of Widgets. 
	// Parameters:
	// widget - a derived object of Widget (smart pointer)
	void addWidget(std::shared_ptr<Widget> widget);

	// Parses all Widgets of type T for the GUILayer and adds them to the Widget list. 
	// This should be called from a GUI object's constructor. 
	template<typename T>
	void parse(Config& c, const int widgetType, const StringList& names);

	// Getters

	// Returns the ID of the GUILayer. 
	const int getID(void) const;

	// Returns a Widget pointer for specified widget. 
	// Parameters:
	// n - Index of Widget in GUILayer
	Widget* getWidgetPtr(const int n) const;

	// Returns the number of Widgets in GUILayer.
	const int getNumWidgets(void) const;

	// Setters

	// Sets the ID of the GUILayer.
	void setID(const int id);

	// Sets the name of the GUILayer.
	void setLayerName(const std::string& name);

	// Resets all Widget's appearances in GUILayer to Appearance::IDLE. 
	void resetAllWidgets(void);

	// Render every Widget.
	virtual void render(void);

	// Update all Widgets with delta time. 
	virtual void update(double dt) = 0;

private:
	// Unique ID for a GUILayer. 
	int m_id;

	WidgetList m_widgets;

	// Set by derived classes so GUILayer::parse() knows where to look. 
	std::string m_layerName;
};

// ================================================ //

inline void GUILayer::addWidget(std::shared_ptr<Widget> widget){
	m_widgets.push_back(widget);
}

// Getters

inline const int GUILayer::getID(void) const{
	return m_id;
}

inline Widget* GUILayer::getWidgetPtr(const int n) const{
	return m_widgets[n].get();
}

inline const int GUILayer::getNumWidgets(void) const{
	return m_widgets.size();
}

// Setters

inline void GUILayer::setID(const int id){
	m_id = id;
}

inline void GUILayer::setLayerName(const std::string& name){
	m_layerName = name;
}

// ================================================ //
// ================================================ //

// Represents a single GUI (e.g, main menu, pause menu). Holds a list of
// GUILayer objects. Assists in navigation of menu widgets using mouse and keyboard
// or gamepad.
class GUI
{
public:
	// Default initializes all member variables. Navigation mode is MOUSE.
	explicit GUI(void);

	// Empty destructor, used to make this class abstract.
	virtual ~GUI(void) = 0;

	// The type of navigation currently in use by the user.
	enum NavMode{
		MOUSE = 0,
		SELECTOR
	};

	// Navigation actions, used during both navigation modes.
	enum Action{
		NAVIGATE = 0,
		BEGIN_PRESS,
		FINISH_PRESS
	};

	// Adds a GUILayer to the GUI's layer list.
	void addLayer(std::shared_ptr<GUILayer> layer);

	// Sets the currently selected Widget's appearance to IDLE.
	// Useful for switching from SELECTOR to MOUSE navigation.
	void clearSelector(void);

	// Getters

	// Returns a pointer to the current GUILayer in use.
	GUILayer* getCurrentLayer(void) const;

	// Returns the navigation mode currently in use (e.g., SELECTOR or MOUSE).
	const int getNavigationMode(void) const;

	// Returns the index of the currently selected Widget. Index is determined
	// by the current GUILayer's index for the Widget. 
	const int getSelectedWidget(void) const;

	// Returns true if the selector button is being held.
	const bool getSelectorPressed(void) const;

	// Returns a Widget pointer for the Widget at index n.
	Widget* getWidgetPtr(const int n) const;

	// Returns a Widget pointer for the currently selected Widget. An easier
	// way to say: gui->WidgetPtr(gui->getSelectedWidget());
	Widget* getSelectedWidgetPtr(void) const;
	
	// Setters

	// Clears the selector, sets the currently selected widget to 0,
	// and points m_pCurrentLayer to layer n in the layer list. If navigating
	// in SELECTOR mode, it sets the appearance of Widget 0 to SELECTED. 
	void setCurrentLayer(const int n);

	// Changes the navigation mode. Valid arguments are SELECTOR and MOUSE.
	void setNavigationMode(const int mode);

	// Sets the GUI's internal mouse coordinates. These should be retrieved from
	// SDL_Event in an update loop.
	void setMousePos(const int x, const int y);

	// Sets the GUI's internal left mouse down boolean.
	void setLeftMouseDown(const bool down);

	// Sets the GUI's internal right mouse down boolean.
	void setRightMouseDown(const bool down);

	// Sets the GUI's internal selectedPressed boolean. Useful for preventing
	// the user from navigating away from a widget while it's selected.
	void setSelectorPressed(const bool pressed);

	// Sets the currently selected Widget's appearance to IDLE and changes the 
	// value of m_selectedWidget to n. Sets newly selected Widget to appearance
	// SELECTED as long as the left mouse button is not pressed on the Widget.
	void setSelectedWidget(const int n);

	// Update the GUI and current GUILayer with delta time.
	virtual void update(double dt);

	// Static strings to store theme data across all GUI states.
	// Used in GUILayer::parse().
	static std::shared_ptr<SDL_Texture> ButtonTexture[3];

private:
	// List of all GUILayer's used by this GUI.
	GUILayerList m_layers;

	// Pointers to the current GUILayer in use from m_layers.
	GUILayer* m_pCurrentLayer;

	// Index of currently selected Widget from the current GUILayer.
	int m_selectedWidget;

	// Stores navigation mode (e.g., SELECTOR or MOUSE).
	int m_navMode;

	// The mouse's relative X and Y coordinates.
	int m_mouseX, m_mouseY;

	// Stores true if left/right mouse button is pressed.
	bool m_leftMouseDown, m_rightMouseDown;

	// Stores true if RETURN on keyboard, A/Start on gamepad is pressed.
	bool m_selectorPressed;
};

// ================================================ //

inline void GUI::addLayer(std::shared_ptr<GUILayer> layer){
	m_layers.push_back(layer);
}

// Getters

inline GUILayer* GUI::getCurrentLayer(void) const{
	return m_pCurrentLayer;
}

inline const int GUI::getNavigationMode(void) const{
	return m_navMode;
}

inline const int GUI::getSelectedWidget(void) const{
	return m_selectedWidget;
}

inline const bool GUI::getSelectorPressed(void) const{
	return m_selectorPressed;
}

inline Widget* GUI::getWidgetPtr(const int n) const{
	return m_pCurrentLayer->getWidgetPtr(n);
}

inline Widget* GUI::getSelectedWidgetPtr(void) const{
	return m_pCurrentLayer->getWidgetPtr(m_selectedWidget);
}

// Setters

inline void GUI::setNavigationMode(const int mode){
	m_navMode = mode;
}

inline void GUI::setMousePos(const int x, const int y){
	m_mouseX = x; m_mouseY = y;
}

inline void GUI::setLeftMouseDown(const bool down){
	m_leftMouseDown = down;
}

inline void GUI::setRightMouseDown(const bool down){
	m_rightMouseDown = down;
}

inline void GUI::setSelectorPressed(const bool pressed){
	m_selectorPressed = pressed;
}

// ================================================ //

#endif

// ================================================ //