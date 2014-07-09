// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: WidgetTextbox.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements the WidgetTextbox class, derived from Widget.
// ================================================ //

#include "WidgetTextbox.hpp"
#include "Label.hpp"
#include "Timer.hpp"
#include "Engine.hpp"

// ================================================ //

WidgetTextbox::WidgetTextbox(const int id) :
Widget(id),
m_cursorPos(0),
m_pCursorTimer(new Timer()),
m_renderCursor(true)
{
	this->setType(Widget::Type::TEXTBOX);

	m_renderLabel = true;
	m_pLabel.reset(new Label());

	m_pCursorTimer->restart();
}

// ================================================ //

WidgetTextbox::~WidgetTextbox(void)
{

}

// ================================================ //

void WidgetTextbox::handleEditing(const char* text, const bool backspace)
{
	// The change in the offset.
	const int offsetDiff = 0;
	std::string label = m_pLabel->getText();
	if (backspace){
		// An empty label is one space.
		if (label != " "){
			label.erase(label.length() - 1, 1);
			this->setLabel(label, m_pLabel->getOffset() + offsetDiff);
		}
	}
	else{
		label.append(text);
		this->setLabel(label, m_pLabel->getOffset() - offsetDiff);
		m_cursorPos = label.length();
	}
}

// ================================================ //

void WidgetTextbox::update(double dt)
{
	if (m_pCursorTimer->getTicks() > 500){
		m_renderCursor = !m_renderCursor;
		m_pCursorTimer->restart();
	}
}

// ================================================ //

void WidgetTextbox::render(void)
{
	Object::render();

	// Render the blinking cursor.
	if (this->isActive() && m_renderCursor){
		SDL_Color color = m_pLabel->getColor();

		SDL_SetRenderDrawBlendMode(Engine::getSingletonPtr()->getRenderer(), SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(Engine::getSingletonPtr()->getRenderer(), color.r, color.g, color.b, 200);
		
		SDL_Rect rc;
		rc.x = m_dst.x + m_pLabel->getWidth();
		rc.y = m_dst.y + 7;
		rc.w = 2;
		rc.h = m_pLabel->getHeight();
		SDL_RenderFillRect(Engine::getSingletonPtr()->getRenderer(), &rc);
	}
}

// ================================================ //


