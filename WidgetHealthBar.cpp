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
#include "GUI.hpp"
#include "Engine.hpp"
#include "Config.hpp"

// ================================================ //

WidgetHealthBar::WidgetHealthBar(const int id) :
Widget(id),
m_percent(100),
m_outline(),
m_renderSrc(),
m_renderDst()
{
	this->setType(Widget::Type::HEALTHBAR);
	this->setTexture(GUITheme::getSingletonPtr()->HealthbarTexture);
	Config e(Engine::getSingletonPtr()->getSettingsFile());
	Config theme(Engine::getSingletonPtr()->getDataDirectory() + "/" + e.parseValue("GUI", "theme"));

	m_renderSrc = m_src;

	m_outlineWidth = theme.parseIntValue("healthbar", "outlineWidth");
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
	// Render border around texture.
	SDL_SetRenderDrawColor(Engine::getSingletonPtr()->getRenderer(), 255, 255, 255, 255);
	SDL_RenderDrawRect(Engine::getSingletonPtr()->getRenderer(), &m_outline);

	SDL_RenderCopyEx(Engine::getSingletonPtr()->getRenderer(), m_pTexture, &m_renderSrc, &m_renderDst, 0, nullptr, m_flip);
}

// ================================================ //

void WidgetHealthBar::setPercent(const int percent)
{
	if (percent > 100 || percent < 0){
		Log::getSingletonPtr()->logMessage("Invalid percentage in WidgetHealthBar::setPercent() => " +
			Engine::toString(percent));
		return;
	}

	double width = static_cast<double>(m_src.w);
	double newWidth = width * static_cast<double>(percent / 100.0);
	m_renderSrc.w = static_cast<int>(newWidth);

	width = static_cast<double>(m_dst.w);
	newWidth = width * static_cast<double>(percent / 100.0);
	m_renderDst.w = static_cast<int>(newWidth);
}

// ================================================ //

