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
// File: Widget.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements the Widget class. 
// ================================================ //

#include "Widget.hpp"
#include "GUI.hpp"

// ================================================ //

Widget::Widget(const int id) :
m_widgetID(id),
m_type(Widget::STATIC),
m_style(DEFAULT),
m_enabled(true)
{
	std::fill_n(m_links, 4, Widget::NONE);
}

// ================================================ //

Widget::~Widget(void)
{

}

// ================================================ //

void Widget::setAppearance(const int appearance, std::shared_ptr<SDL_Texture> pTex)
{
	// Store current position. Setting the texture will reset position information. 
	SDL_Rect pos = this->getPosition();

	if (pTex == nullptr){
		switch (this->getType()){
		default:
			break;

		case Widget::Type::STATIC:
			break;

		case Widget::Type::BUTTON:
			this->setTexture(GUITheme::getSingletonPtr()->ButtonTexture[appearance]);
			break;

		case Widget::Type::TEXTBOX:
			this->setTexture(GUITheme::getSingletonPtr()->TextboxTexture[appearance]);
			break;

		case Widget::Type::LISTBOX:
			this->setTexture(GUITheme::getSingletonPtr()->ListboxTexture);
			break;

		case Widget::Type::HEALTHBAR:

			break;
		}
	}
	else{
		this->setTexture(pTex);
	}

	// Restore original position.
	this->setPosition(pos);
}

// ================================================ //

void Widget::update(double dt)
{

}

// ================================================ //