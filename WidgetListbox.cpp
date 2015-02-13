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
// File: WidgetListbox.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements the WidgetListbox class, derived from Widget.
// ================================================ //

#include "WidgetListbox.hpp"
#include "GUI.hpp"
#include "Label.hpp"
#include "Engine.hpp"

// ================================================ //

WidgetListbox::WidgetListbox(const int id) :
Widget(id),
m_index(0),
m_font(0),
m_labels(),
m_pBorder(GUITheme::getSingletonPtr()->ListboxBorder.get()),
m_borderOffset(5)
{
	this->setType(Widget::Type::LISTBOX);
}

// ================================================ //

WidgetListbox::~WidgetListbox(void)
{

}

// ================================================ //

void WidgetListbox::addString(const std::string& str)
{
	// Empty textboxes hold a single space.
	if (str.empty() || str == " "){
		return;
	}

	std::shared_ptr<Label> label(new Label());
	label->setFont(m_font);
	label->build(str, this->getPosition().w);

	m_labels.push_back(label);
}

// ================================================ //

void WidgetListbox::setEntry(const int n, const std::string& str)
{
	m_labels[n]->build(str, this->getPosition().w);
}

// ================================================ //

void WidgetListbox::removeEntry(const std::string& str)
{
	for (std::vector<std::shared_ptr<Label>>::iterator itr = m_labels.begin();
		itr != m_labels.end();
		++itr){
		if (str.compare(itr->get()->getText()) == 0){
			itr = m_labels.erase(itr);
			return;
		}
	}
}

// ================================================ //

void WidgetListbox::update(double dt)
{

}

// ================================================ //

void WidgetListbox::render(void)
{
	SDL_Rect pos = m_dst;
	
	// Render border.
	SDL_RenderCopyEx(Engine::getSingletonPtr()->getRenderer(), m_pBorder, &m_src, &pos, 0, nullptr, m_flip);

	// Render listbox texture.
	pos.x += m_borderOffset;
	pos.y += m_borderOffset;
	pos.w -= (m_borderOffset * 2);
	pos.h -= (m_borderOffset * 2);
	SDL_RenderCopyEx(Engine::getSingletonPtr()->getRenderer(), m_pTexture, &m_src, &pos, 0, nullptr, m_flip);

	pos = this->getPosition();
	pos.y += 5;
	pos.x += 5;

	for (unsigned int i = 0 + m_index; i < m_labels.size(); ++i){
		pos.w = m_labels[i]->getWidth();
		pos.h = m_labels[i]->getHeight();

		SDL_RenderCopyEx(Engine::getSingletonPtr()->getRenderer(), m_labels[i]->getTexturePtr(),
			nullptr, &pos, 0, nullptr, SDL_FLIP_NONE);

		// Prepare for next line by moving the y component of destination rect.
		pos.y += m_labels[i]->getHeight();

		// If the listbox is full, hide first message and display the next
		// one at the bottom.
		if (pos.y >= (this->getPosition().y + this->getPosition().h)){
			m_index++;
			break;
		}
	}
}

// ================================================ //

