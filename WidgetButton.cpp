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
// File: WidgetButton.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements Button class. 
// ================================================ //

#include "WidgetButton.hpp"
#include "Label.hpp"

// ================================================ //

WidgetButton::WidgetButton(const int id) :
Widget(id)
{
	this->setType(Widget::Type::BUTTON);

	// m_pLabel is in ObjectImpl; tell this class to use it.
	m_renderLabel = true;
	m_pLabel.reset(new Label(true));
}

// ================================================ //

WidgetButton::~WidgetButton(void)
{

}

// ================================================ //

void WidgetButton::update(double dt)
{
	
}

// ================================================ //