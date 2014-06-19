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
#include "WidgetImpl.hpp"

// ================================================ //

Widget::Widget(const int id) :
m_pImpl(nullptr) // TODO: this should be left nullptr and child widgets called Widget::setPImpl(), I believe
{
	
}

// ================================================ //

Widget::~Widget(void)
{

}

// ================================================ //

void Widget::parseLinks(const std::string& links)
{
	return m_pImpl->parseLinks(links);
}

// ================================================ //
// Getter functions
// ================================================ //

const int Widget::getWidgetID(void) const
{
	return m_pImpl->getWidgetID();
}

// ================================================ //

const int Widget::getType(void) const
{
	return m_pImpl->getType();
}

// ================================================ //

const bool Widget::isEnabled(void) const
{
	return m_pImpl->isEnabled();
}

// ================================================ //

const int Widget::getLinkID(const int direction) const
{
	return m_pImpl->getLinkID(direction);
}

// ================================================ //
// Setter functions
// ================================================ //

void Widget::setType(const int type)
{
	return m_pImpl->setType(type);
}

// ================================================ //

void Widget::setEnabled(const bool enabled)
{
	return m_pImpl->setEnabled(enabled);
}

// ================================================ //

void Widget::setLinkID(const int direction, const int id)
{
	return m_pImpl->setLinkID(direction, id);
}

// ================================================ //

void Widget::setAppearance(const int appearance)
{
	return m_pImpl->setAppearance(appearance);
}

// ================================================ //