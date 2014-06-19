// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: ButtonImpl.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements ButtonImpl class. 
// ================================================ //

#include "ButtonImpl.hpp"

// ================================================ //

ButtonImpl::ButtonImpl(const int id) :
WidgetImpl(id)
{
	// m_pLabel is in ObjectImpl; tell this class to use it. 
	m_pLabel.reset(new Label());
	m_renderLabel = true;
}

// ================================================ //

ButtonImpl::~ButtonImpl(void)
{

}

// ================================================ //

void ButtonImpl::update(double dt)
{

}

// ================================================ //