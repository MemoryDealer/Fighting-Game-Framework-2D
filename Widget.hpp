// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: Widget.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines the Widget class.  
// ================================================ //

#ifndef __WIDGET_HPP__
#define __WIDGET_HPP__

// ================================================ //

#include "stdafx.hpp"
#include "Object.hpp"

// ================================================ //

class WidgetImpl;

// ================================================ //

// A polymorphic, abstract class to derive GUI widgets from. A GUILayer holds 
// a list of Widget objects. This class uses the pImpl idiom (WidgetImpl). 
// Sample usage: N/A (see Button.hpp, for an example)
class Widget : public Object
{
public:
	// Assigns m_pImpl to nullptr (child classes should call Widget::setPImpl()).
	explicit Widget(const int id);

	// Automatically destructs m_pImpl.
	virtual ~Widget(void);

	// Every type of widget used by the GUI is enumerated here. 
	enum Type{
		STATIC = 0,
		BUTTON
	};

	// Links connect GUI widgets to other GUI widgets. This is used only when the GUI
	// is in SELECTOR navigation mode (keyboard/gamepad input). 
	enum Link{
		UP = 0,
		DOWN,
		LEFT,
		RIGHT
	};

	// The graphical appearance of a widget can be any of these. Typically, these will be 
	// textures. 
	enum Appearance{
		IDLE = 0,
		SELECTED,
		PRESSED
	};

	// Enumerates an easily recognizable value for no currently selected widget. Used by GUI
	// and game states. 
	enum{
		NONE = -1
	};

	// Tokenizes a string containing a list of link values (e.g., "-1,0,-1,2") and 
	// assigns the link values to this Widget's links. This string is retrieved from
	// a button map (.bmap) file. 
	void parseLinks(const std::string& links);

	// Getters

	// Returns the local ID for this Widget. Each GUILayer contains its own Widget IDs 
	// starting at 0. 
	const int getWidgetID(void) const; 

	// Returns the type of widget (e.g., STATIC, BUTTON, etc.). 
	const int getType(void) const;

	// Returns true if the Widget is enabled. 
	const bool isEnabled(void) const;

	// Returns the link value (another Widget's ID) for the specific direction. 
	// Parameters:
	// direction - the direction of the link (e.g., UP, DOWN, LEFT, or RIGHT)
	const int getLinkID(const int direction) const;

	// Setters

	// Sets the type value of the Widget. Should be called in the constructor of 
	// any derived class. 
	// Parameters:
	// type - Type of widget (e.g., STATIC, BUTTON, etc)
	void setType(const int type);

	// Sets the Widget to enabled or disabled. 
	void setEnabled(const bool enabled);

	// Sets the link value (another Widget's ID) for the specified direction. 
	// Parameters:
	// direction - direction of the link (e.g., UP, DOWN, LEFT, or RIGHT)
	// id - the ID of the Widget to link 
	void setLinkID(const int direction, const int id);

	// Sets the graphical appearance of the Widget. 
	// Parameters:
	// appearance - the enumerated value for the appearance, such as Appearance::IDLE
	virtual void setAppearance(const int appearance);

	// Update the Widget using delta time. 
	virtual void update(double dt) = 0;

protected:

	// Sets the Widget's m_pImpl to another m_pImpl. This is required by all derived classes
	// of Widget. First Widget::setPImpl() should be called, then Object::setPImpl(), 
	// passing the parameter "m_pImpl". 
	virtual void setPImpl(std::shared_ptr<WidgetImpl> pImpl);

private:
	// Pimpl idiom for proper inheritance. 
	std::shared_ptr<WidgetImpl> m_pImpl;
};

// ================================================ //

inline void Widget::setPImpl(std::shared_ptr<WidgetImpl> pImpl){
	m_pImpl = pImpl;
}

// ================================================ //

#endif

// ================================================ //