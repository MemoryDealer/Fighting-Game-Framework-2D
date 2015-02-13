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
// File: Hitbox.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines Hitbox class.
// ================================================ //

#ifndef __HITBOX_HPP__
#define __HITBOX_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

// A hitbox for use by a Player object. Can be tested for collision
// with other hitboxes, and debug rendered.
class Hitbox
{
public:
	// Sets up the color of the hitbox, depending on its type.
	explicit Hitbox(const int type);

	// Empty destructor.
	virtual ~Hitbox(void);

	// Hitbox types.
	enum Type{
		NORMAL = 0,
		DAMAGE,
		THROW,
		COUNTER
	};

	// Hitbox indices for use by Player class.
	enum{
		HBOX_LOWER = 0,
		HBOX_MIDDLE,
		HBOX_UPPER,
		HBOX_HEAD,
		TBOX,
		DBOX1,
		DBOX2,
		CBOX1,
		CBOX2,
	};

	// Returns true if this Hitbox intersects Hitbox b.
	const bool intersects(const Hitbox* b);

	// Renders the hitbox using internal SDL_Rect coordinates.
	void render(void);

	// Getters

	// Returns the SDL_Rect for the Hitbox.
	virtual const SDL_Rect& getRect(void) const;

	// Setters

	// Sets the internal SDL_Rect values for rendering.
	virtual void setRect(const int x, const int y, const int w = 0, const int h = 0);

	// Sets the internal SDL_Rect for rendering.
	virtual void setRect(const SDL_Rect& pos);

	// --- //

	// Returns true if Hitboxes a and b intersect.
	static const bool HitboxIntersect(const Hitbox* a, const Hitbox* b);

private:
	SDL_Rect	m_rc;
	int			m_type;
	bool		m_active;
	SDL_Color	m_color;
	SDL_Color	m_outline;
};

// ================================================ //

// Getters

inline const SDL_Rect& Hitbox::getRect(void) const{ 
	return m_rc; 
}

// Setters

inline void Hitbox::setRect(const int x, const int y, const int w , const int h){ 
	m_rc.x = x; m_rc.y = y; 
	m_rc.w = w; m_rc.h = h;
}

inline void Hitbox::setRect(const SDL_Rect& pos){ 
	m_rc = pos; 
}

// ================================================ //

#endif

// ================================================ //