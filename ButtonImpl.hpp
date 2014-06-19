// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: ButtonImpl.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines ButtonImpl Pimpl idiom class. 
// ================================================ //

#ifndef __BUTTONIMPL_HPP__
#define __BUTTONIMPL_HPP__

// ================================================ //

#include "WidgetImpl.hpp"

// ================================================ //

// Pimpl class for Button. 
class ButtonImpl : public WidgetImpl
{
public:
	// Calls WidgetImpl's constructor with id. Allocates the Label
	// object, and sets m_renderLabel to true. 
	explicit ButtonImpl(const int id);

	// Empty destructor. 
	virtual ~ButtonImpl(void);

	// See Button.hpp.
	virtual void update(double dt);

private:

};

// ================================================ //

#endif

// ================================================ //