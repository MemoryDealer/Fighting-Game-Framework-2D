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
// File: WidgetStatic.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines the WidgetStatic class, derived from Widget.
// ================================================ //

#ifndef __WIDGETSTATIC_HPP__
#define __WIDGETSTATIC_HPP__

// ================================================ //

#include "Widget.hpp"

// ================================================ //

// A static GUI widget that can hold text and/or a picture. Does not allow
// direct interaction from user.
class WidgetStatic : public Widget
{
public:
	// Calls Widget's constructor, sets type to STATIC, allocates Label.
	explicit WidgetStatic(const int id);

	// Empty destructor.
	virtual ~WidgetStatic(void);

	// Updates with delta time.
	virtual void update(double dt);

private:

};

// ================================================ //

#endif

// ================================================ //