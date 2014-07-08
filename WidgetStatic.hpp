// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: WidgetStatic.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines the WidgetStatic class, derived from Widget.
// ================================================ //

#ifndef __WIDGETSTATIC_HPP__
#define __WIDGETSTATIC_HPP__

// ================================================ //

#include "Widget.hpp"

// ================================================ //

// A static GUI widget that can hold text and/or a picture. Does not allow
// direct interaction from user.
class WidgetStatic : public Widget
{
public:
	// Calls Widget's constructor, sets type to STATIC, allocates Label.
	explicit WidgetStatic(const int id);

	// Empty destructor.
	virtual ~WidgetStatic(void);

	// Updates with delta time.
	virtual void update(double dt);

private:

};

// ================================================ //

#endif

// ================================================ //