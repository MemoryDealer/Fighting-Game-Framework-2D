// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: WidgetHealthBar.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements the WidgetHealthBar class, derived from Widget.
// ================================================ //

#include "WidgetHealthBar.hpp"
#include "Engine.hpp"
#include "Config.hpp"

// ================================================ //

WidgetHealthBar::WidgetHealthBar(const int id) :
Widget(id),
m_percent(100)
{
	this->setType(Widget::Type::HEALTHBAR);

	Config e(Engine::getSingletonPtr()->getSettingsFile());
	Config theme(e.parseValue("GUI", "theme"));

	this->setTextureFile(theme.parseValue("healthbox", "tex"));
}

// ================================================ //

WidgetHealthBar::~WidgetHealthBar(void)
{

}

// ================================================ //

void WidgetHealthBar::update(double dt)
{
	
}

// ================================================ //

void WidgetHealthBar::render(void)
{
	SDL_RenderCopyEx(Engine::getSingletonPtr()->getRenderer(), m_pTexture, &m_src, &m_dst, 0, nullptr, m_flip);
}

// ================================================ //

void WidgetHealthBar::setPercent(const int percent)
{

}

// ================================================ //

