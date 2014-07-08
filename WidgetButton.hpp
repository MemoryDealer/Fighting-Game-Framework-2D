// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: WidgetButton.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines the WidgetButton class, derived from Widget. 
// ================================================ //

#ifndef __WIDGETBUTTON_HPP__
#define __WIDGETBUTTON_HPP__

// ================================================ //

#include "Widget.hpp"

// ================================================ //

// A GUI button. When pressed, it does something special (handled in the state
// function "processGUIAction()"). 
class WidgetButton : public Widget
{
public:
	// Calls Widget's constructor with id. Sets Widget type to BUTTON.
	// Allocates the Label object, and sets m_renderLabel to true.
	explicit WidgetButton(const int id);

	// Empty destructor.
	virtual ~WidgetButton(void);

	// Updates Button with delta time. 
	virtual void update(double dt);

private:
	
};

// ================================================ //

#endif

// ================================================ //