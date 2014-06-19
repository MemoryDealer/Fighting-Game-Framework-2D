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
#include "Widget.hpp"

// ================================================ //

class GUILayer;
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

	// Returns the number of Widgets in GUILayer
	const int getNumWidgets(void) const;

	// Setters

	// Set the ID of the GUILayer
	void setID(const int id);

	// Set the name of the GUILayer
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
/* An object for each game state to process all GUI operations */
class GUI
{
public:
	explicit GUI(void);
	virtual ~GUI(void) = 0;

	enum NavMode{
		MOUSE = 0,
		SELECTOR
	};

	enum Action{
		NAVIGATE = 0,
		BEGIN_PRESS,
		FINISH_PRESS
	};

	void addLayer(std::shared_ptr<GUILayer> layer);
	void clearSelector(void);
	
	// Setter functions
	void setCurrentLayer(const int n);
	void setNavigationMode(const int mode);
	void setMousePos(const int x, const int y);
	void setLeftMouseDown(const bool down);
	void setRightMouseDown(const bool down);
	void setSelectorPressed(const bool pressed);
	void setSelectedWidget(const int n);

	// Getter functions
	GUILayer* getCurrentLayer(void) const;
	const int getNavigationMode(void) const;
	const int getSelectedWidget(void) const;
	const int getLastSelectedWidget(void) const;
	const bool getSelectorPressed(void) const;
	Widget* getWidgetPtr(const int n) const;
	Widget* getSelectedWidgetPtr(void) const;

	virtual void update(double dt);

	// Static strings to store theme data across all GUI states (useful within GUILayer::parse())
	static std::shared_ptr<SDL_Texture> ButtonTexture[3];

private:
	GUILayerList m_layers;
	GUILayer* m_pCurrentLayer;
	int m_selectedWidget;
	int m_navMode;
	int m_mouseX, m_mouseY;
	bool m_leftMouseDown, m_rightMouseDown;
	bool m_selectorPressed; // RETURN on keyboard, A/Start on gamepad, etc. 
};

// ================================================ //

inline void GUI::addLayer(std::shared_ptr<GUILayer> layer){
	m_layers.push_back(layer);
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

// ================================================ //

#endif

// ================================================ //