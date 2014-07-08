// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: WidgetTextbox.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements the WidgetTextbox class, derived from Widget.
// ================================================ //

#include "WidgetTextbox.hpp"
#include "Label.hpp"

// ================================================ //

WidgetTextbox::WidgetTextbox(const int id) :
Widget(id)
{
	this->setType(Widget::Type::TEXTBOX);

	m_renderLabel = true;
	m_pLabel.reset(new Label());
}

// ================================================ //

WidgetTextbox::~WidgetTextbox(void)
{

}

// ================================================ //

void WidgetTextbox::update(double dt)
{

}

// ================================================ //


