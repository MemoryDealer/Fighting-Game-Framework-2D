// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: WidgetListbox.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements the WidgetListbox class, derived from Widget.
// ================================================ //

#include "WidgetListbox.hpp"
#include "Label.hpp"
#include "Engine.hpp"

// ================================================ //

WidgetListbox::WidgetListbox(const int id) :
Widget(id),
m_index(0),
m_font(0),
m_labels()
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
	label->create(str, this->getPosition().w);


	m_labels.push_back(label);
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
	Object::render();

	SDL_Rect pos = this->getPosition();
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
		if (pos.y >= (this->getPosition().h - this->getPosition().y)){
			m_index++;
			break;
		}
	}
}

// ================================================ //

