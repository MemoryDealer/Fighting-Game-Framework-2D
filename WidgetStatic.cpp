// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: WidgetStatic.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements the WidgetStatic class.
// ================================================ //

#include "WidgetStatic.hpp"
#include "Label.hpp"

// ================================================ //

WidgetStatic::WidgetStatic(const int id) :
Widget(id)
{
	this->setType(Widget::Type::STATIC);

	m_renderLabel = true;
	m_pLabel.reset(new Label(true));
}

// ================================================ //

WidgetStatic::~WidgetStatic(void)
{

}

// ================================================ //

void WidgetStatic::update(double dt)
{

}

// ================================================ //

