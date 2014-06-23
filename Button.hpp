// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: Button.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines the Button class, derived from Widget. 
// ================================================ //

#ifndef __BUTTON_HPP__
#define __BUTTON_HPP__

// ================================================ //

#include "Widget.hpp"

// ================================================ //

// A GUI button. When pressed, it does something special (handled in the state
// function "processGUIAction()"). 
class Button : public Widget
{
public:
	// Calls Widget's constructor with id. Sets Widget type to BUTTON.
	// Allocates the Label object, and sets m_renderLabel to true.
	explicit Button(const int id);

	// Empty destructor.
	virtual ~Button(void);

	// Updates Button with delta time. 
	virtual void update(double dt);

private:
	
};

// ================================================ //

#endif

// ================================================ //