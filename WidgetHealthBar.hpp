// ========================================================================= //
// Fighting game framework (2D) with online multiplayer.
// Copyright(C) 2014 Jordan Sparks <unixunited@live.com>
//
// This program is free software; you can redistribute it and / or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 3
// of the License, or(at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
// ========================================================================= //
// File: WidgetHealthBar.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines the WidgetHealthBar class, derived from Widget.
// ================================================ //

#ifndef __WIDGETHEALTHBAR_HPP__
#define __WIDGETHEALTHBAR_HPP__

// ================================================ //

#include "Widget.hpp"

// ================================================ //

class WidgetHealthBar : public Widget
{
public:
	// Calls Widget's constructor, sets type to HEALTHBAR, loads texture.
	explicit WidgetHealthBar(const int id);

	// Empty destructor.
	virtual ~WidgetHealthBar(void);

	// Sets the position and calculates offset.
	virtual void setPosition(const SDL_Rect& pos);

	// Updates with delta time.
	virtual void update(double dt);

	virtual void render(void);

	// Sets the percentage of the health bar that is full.
	virtual void setPercent(const int percent);

private:
	int m_percent;
	int m_outlineWidth;
	SDL_Rect m_outline;
	SDL_Rect m_renderSrc, m_renderDst;
};

// ================================================ //

inline void WidgetHealthBar::setPosition(const SDL_Rect& pos){
	Object::setPosition(pos);
	m_outline = m_dst;
	m_outline.x -= m_outlineWidth;
	m_outline.y -= m_outlineWidth;
	m_outline.w += (m_outlineWidth * 2);
	m_outline.h += (m_outlineWidth * 2);
	m_renderDst = m_dst;
}

// ================================================ //

#endif

// ================================================ //