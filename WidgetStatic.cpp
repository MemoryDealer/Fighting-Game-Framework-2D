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
// File: WidgetStatic.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements the WidgetStatic class.
// ================================================ //

#include "WidgetStatic.hpp"
#include "Label.hpp"

// ================================================ //

WidgetStatic::WidgetStatic(const int id) :
Widget(id)
{
	this->setType(Widget::Type::STATIC);

	m_renderLabel = true;
	m_pLabel.reset(new Label(true));
}

// ================================================ //

WidgetStatic::~WidgetStatic(void)
{

}

// ================================================ //

void WidgetStatic::update(double dt)
{

}

// ================================================ //

