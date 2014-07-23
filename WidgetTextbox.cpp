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
m_offset(0),
m_text(),
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
	if (backspace){
		// An empty label is one space, so don't operate on it if so.
		if (m_text != " " && !m_text.empty()){
			m_text.pop_back();
			if (m_offset > 0){
				std::string scrolledText = m_text.substr(--m_offset, m_text.length());
				Object::setLabel(scrolledText, m_pLabel->getOffset());
			}
			else{
				Object::setLabel(m_text, m_pLabel->getOffset());
			}
		}
	}
	else{
		// Test for number only text if the style is set.
		if (this->getStyle() & Widget::TB_NUMBER){
			for (unsigned int i = 0; i < std::strlen(text); ++i){
				if (!isdigit(text[i])){
					return;
				}
			}
		}

		m_text += text;
		Object::setLabel(m_text, m_pLabel->getOffset());

		// Prevent text from going outside of widget by scrolling it.
		if (m_pLabel->getWidth() > m_dst.w){
			std::string scrolledText = m_text.substr(++m_offset, m_text.length());
			Object::setLabel(scrolledText, m_pLabel->getOffset());
		}
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
		rc.y = m_dst.y + m_dst.h / 10;
		rc.w = 2;
		rc.h = m_dst.h - (m_dst.h / 5);
		SDL_RenderFillRect(Engine::getSingletonPtr()->getRenderer(), &rc);
	}
}

// ================================================ //

void WidgetTextbox::setLabel(const std::string& label, const int offset)
{
	m_offset = 0;
	m_text = label;

	Object::setLabel(label, offset);
	// Scroll text to end of string if needed.
	while (m_pLabel->getWidth() > m_dst.w){
		std::string scrolledText = m_text.substr(++m_offset, m_text.length());
		Object::setLabel(scrolledText, m_pLabel->getOffset());
	}
}

// ================================================ //

