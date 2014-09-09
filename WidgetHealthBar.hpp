// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: WidgetHealthBar.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines the WidgetHealthBar class, derived from Widget.
// ================================================ //

#ifndef __WIDGETHEALTHBAR_HPP__
#define __WIDGETHEALTHBAR_HPP__

// ================================================ //

#include "Widget.hpp"

// ================================================ //

class WidgetHealthBar : public Widget
{
public:
	// Calls Widget's constructor, sets type to HEALTHBAR, loads texture.
	explicit WidgetHealthBar(const int id);

	// Empty destructor.
	virtual ~WidgetHealthBar(void);

	// Updates with delta time.
	virtual void update(double dt);

	virtual void render(void);

	// Sets the percentage of the health bar that is full.
	virtual void setPercent(const int percent);

private:
	int m_percent;
};

// ================================================ //

#endif

// ================================================ //