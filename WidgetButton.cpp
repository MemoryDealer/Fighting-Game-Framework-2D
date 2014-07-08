// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: WidgetButton.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements Button class. 
// ================================================ //

#include "WidgetButton.hpp"
#include "Label.hpp"

// ================================================ //

WidgetButton::WidgetButton(const int id) :
Widget(id)
{
	this->setType(Widget::Type::BUTTON);

	// m_pLabel is in ObjectImpl; tell this class to use it.
	m_renderLabel = true;
	m_pLabel.reset(new Label());
}

// ================================================ //

WidgetButton::~WidgetButton(void)
{

}

// ================================================ //

void WidgetButton::update(double dt)
{
	
}

// ================================================ //