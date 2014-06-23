// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: WidgetImpl.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements the WidgetImpl Pimpl idiom class for Widget. 
// ================================================ //

#include "WidgetImpl.hpp"
#include "GUI.hpp"

// ================================================ //

WidgetImpl::WidgetImpl(const int id) :
m_widgetID(id),
m_type(Widget::STATIC),
m_enabled(true)
{
	
}

// ================================================ //

WidgetImpl::~WidgetImpl(void)
{

}

// ================================================ //

