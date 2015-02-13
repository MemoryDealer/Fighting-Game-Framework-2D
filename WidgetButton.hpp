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
// File: WidgetButton.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines the WidgetButton class, derived from Widget. 
// ================================================ //

#ifndef __WIDGETBUTTON_HPP__
#define __WIDGETBUTTON_HPP__

// ================================================ //

#include "Widget.hpp"

// ================================================ //

// A GUI button. When pressed, it does something special (handled in the state
// function "processGUIAction()"). 
class WidgetButton : public Widget
{
public:
	// Calls Widget's constructor with id. Sets Widget type to BUTTON.
	// Allocates the Label object, and sets m_renderLabel to true.
	explicit WidgetButton(const int id);

	// Empty destructor.
	virtual ~WidgetButton(void);

	// Updates Button with delta time. 
	virtual void update(double dt);

private:
	
};

// ================================================ //

#endif

// ================================================ //