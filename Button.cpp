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
#include "ButtonImpl.hpp"

// ================================================ //

Button::Button(const int id) :
Widget(id),
m_pImpl(new ButtonImpl(id))
{
	Widget::setPImpl(m_pImpl);
	Object::setPImpl(m_pImpl);

	this->setType(Widget::Type::BUTTON);
}

// ================================================ //

Button::~Button(void)
{

}

// ================================================ //

void Button::update(double dt)
{
	return m_pImpl->update(dt);
}

// ================================================ //