// ========================================================================= //
// Fighting game framework (2D) with online multiplayer.
// Copyright(C) 2014 Jordan Sparks <unixunited@live.com>
//
// This program is free software; you can redistribute it and / or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 3
// of the License, or(at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
// ========================================================================= //
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

// A polymorphic, abstract class to derive GUI widgets from. A GUILayer holds 
// a list of Widget objects.
// Sample usage: N/A (see Button.hpp, for an example)
class Widget : public Object
{
public:
	// Initializes the Widget ID to id, assigns the type to STATIC by default,
	// and sets it to enabled by default. Sets all links to Widget::NONE. 
	explicit Widget(const int id);

	// Automatically destructs m_pImpl.
	virtual ~Widget(void);

	// Every type of widget used by the GUI is enumerated here. 
	enum Type{
		STATIC = 0,
		BUTTON,
		TEXTBOX,
		LISTBOX,
		HEALTHBAR
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

	// Widget styles (for all child widgets).
	enum Style{
		DEFAULT = 0x00000000,
		// Textbox.
		TB_NUMBER,
		TB_MULTILINE
	};

	// Tokenizes a string containing a list of link values (e.g., "-1,0,-1,2") and 
	// assigns the link values to this Widget's links. This string is retrieved from
	// a button map (.bmap) file. 
	void parseLinks(const std::string& links);

	// Empty functions for derived widgets.

	virtual void addString(const std::string& str){}
	virtual void setEntry(const int n, const std::string& str){}
	virtual void removeEntry(const std::string& str){}
	virtual void clear(void){}
	virtual void setPercent(const int percent){}
	
	// Getters

	// Returns the local ID for this Widget. Each GUILayer contains its own Widget IDs 
	// starting at 0. 
	const int getWidgetID(void) const; 

	// Returns the type of widget (e.g., STATIC, BUTTON, etc.). 
	const int getType(void) const;

	// Returns the style value.
	const int getStyle(void) const;

	// Returns true if the Widget is enabled. 
	const bool isEnabled(void) const;

	// Returns true if the Widget is active (selected).
	const bool isActive(void) const;

	// Returns the link value (another Widget's ID) for the specific direction. 
	// Parameters:
	// direction - the direction of the link (e.g., UP, DOWN, LEFT, or RIGHT)
	const int getLinkID(const int direction) const;

	// Should be overriden if a widget needs to return any text it holds.
	virtual const std::string getText(void) const;

	// Setters

	// Sets the type value of the Widget. Should be called in the constructor of 
	// any derived class. 
	// Parameters:
	// type - Type of widget (e.g., STATIC, BUTTON, etc)
	void setType(const int type);

	// Sets the style value.
	void setStyle(const int style);

	// Sets the Widget to enabled or disabled (can it be interacted with). 
	void setEnabled(const bool enabled);

	// Sets the Widget to active if true.
	void setActive(const bool active);

	// Sets the link value (another Widget's ID) for the specified direction. 
	// Parameters:
	// direction - direction of the link (e.g., UP, DOWN, LEFT, or RIGHT)
	// id - the ID of the Widget to link 
	void setLinkID(const int direction, const int id);

	// Sets the graphical appearance of the Widget. 
	// Parameters:
	// appearance - the enumerated value for the appearance, such as Appearance::IDLE
	// pTex - if specified, the widget will use this texture, otherwise it will use
	//  the GUI's theme texture for the appearance value.
	virtual void setAppearance(const int appearance, std::shared_ptr<SDL_Texture> pTex = nullptr);

	// --- //

	// Update the Widget using delta time. 
	virtual void update(double dt) = 0;

private:
	int m_widgetID;
	int m_type;
	int m_style;
	bool m_enabled;
	bool m_active;

	// Assocations between this widget and other widgets for SELECTOR navigation. 
	int m_links[4];
};

// ================================================ //

inline void Widget::parseLinks(const std::string& links) {
	// Get each link ID, delimited by commas
	char* p = strtok(const_cast<char*>(links.c_str()), ",");
	int direction = Widget::Link::UP;
	while (p && direction < 4){
		int linkID = std::stoi(p);
		this->setLinkID(direction++, linkID);
		p = strtok(nullptr, ",");
	}
}

// Getters

inline const int Widget::getWidgetID(void) const{
	return m_widgetID;
}

inline const int Widget::getType(void) const{
	return m_type;
}

inline const int Widget::getStyle(void) const{
	return m_style;
}

inline const bool Widget::isEnabled(void) const{
	return m_enabled;
}

inline const bool Widget::isActive(void) const{
	return m_active;
}

inline const int Widget::getLinkID(const int direction) const{
	return m_links[direction];
}

inline const std::string Widget::getText(void) const{
	return std::string("");
}

// Setters

inline void Widget::setType(const int type){
	m_type = type;
}

inline void Widget::setStyle(const int style){
	m_style = style;
}

inline void Widget::setEnabled(const bool enabled){
	m_enabled = enabled;
}

inline void Widget::setActive(const bool active){
	m_active = active;
}

inline void Widget::setLinkID(const int direction, const int id){
	m_links[direction] = id;
}

// ================================================ //

#endif

// ================================================ //