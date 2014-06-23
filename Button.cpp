// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: Button.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements Button class. 
// ================================================ //

#include "Button.hpp"
#include "Label.hpp"

// ================================================ //

Button::Button(const int id) :
Widget(id)
{
	this->setType(Widget::Type::BUTTON);

	// m_pLabel is in ObjectImpl; tell this class to use it.
	m_renderLabel = true;
	m_pLabel.reset(new Label());
}

// ================================================ //

Button::~Button(void)
{

}

// ================================================ //

void Button::update(double dt)
{
	
}

// ================================================ //