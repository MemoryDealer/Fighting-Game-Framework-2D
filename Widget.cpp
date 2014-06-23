// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: Widget.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements the Widget class. 
// ================================================ //

#include "Widget.hpp"
#include "GUI.hpp"

// ================================================ //

Widget::Widget(const int id) :
m_widgetID(id),
m_type(Widget::STATIC),
m_enabled(true)
{
	std::fill_n(m_links, 4, Widget::NONE);
}

// ================================================ //

Widget::~Widget(void)
{

}

// ================================================ //

void Widget::setAppearance(const int appearance)
{
	// Store current position. Setting the texture will reset position information. 
	SDL_Rect pos = this->getPosition();

	switch (this->getType()){
	default:
		break;

	case Widget::Type::BUTTON:
		this->setTexture(GUI::ButtonTexture[appearance]);
		break;
	}

	// Restore original position.
	this->setPosition(pos);
}

// ================================================ //

void Widget::update(double dt)
{

}

// ================================================ //