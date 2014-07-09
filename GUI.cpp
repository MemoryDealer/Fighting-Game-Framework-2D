// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: GUI.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements GUI and GUILayer classes. 
// ================================================ //

#include "GUI.hpp"
#include "Config.hpp"
#include "Engine.hpp"
#include "WidgetStatic.hpp"
#include "WidgetButton.hpp"
#include "WidgetTextbox.hpp"
#include "Label.hpp"

// ================================================ //

GUILayer::GUILayer(void) :
m_id(0),
m_widgets()
{

}

// ================================================ //

GUILayer::~GUILayer(void)
{

}

// ================================================ //

template<typename T>
void GUILayer::parse(Config& c, const int widgetType, const StringList& names)
{
	std::string widgetName("");
	std::string layer = "layer." + m_layerName;

	// The texture to assign the widget.
	std::shared_ptr<SDL_Texture> pTex = nullptr;

	switch (widgetType){
	default:
	case Widget::Type::STATIC:
		widgetName = "static.";
		break;

	case Widget::Type::BUTTON:
		widgetName = "button.";
		pTex = GUI::ButtonTexture[Widget::Appearance::IDLE];
		break;

	case Widget::Type::TEXTBOX:
		widgetName = "textbox.";
		break;
	}

	// Parse each setting for this Widget. 
	for (unsigned int i = 0; i < names.size(); ++i){
		// Allocate widget with ID i (the names list parameter should be in order).
		std::shared_ptr<Widget> pWidget(new T(i));
		std::string value = widgetName + names[i] + ":";

		pWidget->setAppearance(Widget::Appearance::IDLE);
		pWidget->setPosition(c.parseRect(layer, value + "pos"));
		pWidget->setLabel(c.parseValue(layer, value + "label", true), c.parseIntValue(layer, value + "labeloffset"));
		pWidget->parseLinks(c.parseValue(layer, value + "links"));

		this->addWidget(pWidget);
	}
}

// Explicitly instantiate template functions for each Widget type.
template void GUILayer::parse<WidgetStatic>(Config& c, const int widgetType, const StringList& names);
template void GUILayer::parse<WidgetButton>(Config& c, const int widgetType, const StringList& names);
template void GUILayer::parse<WidgetTextbox>(Config& c, const int widgetType, const StringList& names);

// ================================================ //

void GUILayer::resetAllWidgets(const int cursor)
{
	for (unsigned int i = 0; i < m_widgets.size(); ++i){
		if (i != cursor){
			m_widgets[i]->setAppearance(Widget::Appearance::IDLE);
		}
	}
}

// ================================================ //

void GUILayer::render(void)
{
	for (WidgetList::iterator itr = m_widgets.begin();
		itr != m_widgets.end();
		++itr){
		(*itr)->render();
	}
}

// ================================================ //

void GUILayer::update(double dt)
{
	for (WidgetList::iterator itr = m_widgets.begin();
		itr != m_widgets.end();
		++itr){
		(*itr)->update(dt);
	}
}

// ================================================ //
// ================================================ //

std::shared_ptr<SDL_Texture> GUI::ButtonTexture[] = { nullptr, nullptr, nullptr };
std::shared_ptr<SDL_Texture> GUI::TextboxTexture[] = { nullptr, nullptr, nullptr };
std::shared_ptr<SDL_Texture> GUI::TextboxCursor = nullptr;

// ================================================ //

GUI::GUI(void) :
m_layers(),
m_layerStack(),
m_selectedWidget(Widget::NONE),
m_cursor(Widget::NONE),
m_navMode(NavMode::MOUSE),
m_mouseX(0),
m_mouseY(0),
m_leftMouseDown(false),
m_rightMouseDown(false),
m_selectorPressed(false)
{
	
}

// ================================================ //

GUI::~GUI(void)
{

}

// ================================================ //

void GUI::clearSelector(void)
{
	if (m_selectedWidget != Widget::NONE){
		m_layers[m_layerStack.top()]->getWidgetPtr(m_selectedWidget)->setAppearance(Widget::Appearance::IDLE);
	}

	m_selectedWidget = 0;
	m_cursor = Widget::NONE;
}

// ================================================ //

void GUI::pushLayer(const int n)
{
	this->clearSelector();
	
	m_layerStack.push(n);

	// Set the default selected Widget's appearance to SELECTED.
	if (m_navMode == GUI::NavMode::SELECTOR){
		m_layers[m_layerStack.top()]->getWidgetPtr(m_selectedWidget)->setAppearance(Widget::Appearance::SELECTED);
	}
}

// ================================================ //

void GUI::popLayer(void)
{
	// Only pop if there is more than one layer.
	if (m_layerStack.size() > 1){
		this->clearSelector();

		m_layerStack.pop();

		if (m_navMode == GUI::NavMode::SELECTOR){
			m_layers[m_layerStack.top()]->getWidgetPtr(m_selectedWidget)->setAppearance(Widget::Appearance::SELECTED);
		}
	}
}

// ================================================ //

void GUI::handleTextInput(const char* text, const bool backspace)
{
	if (m_cursor != Widget::NONE){
		WidgetTextbox* pWidget = static_cast<WidgetTextbox*>(this->getWidgetPtr(m_cursor));
		pWidget->handleEditing(text, backspace);
	}
}

// ================================================ //

void GUI::setSelectedWidget(const int n)
{
	if (n != Widget::NONE){
		// Reset currently selected widget to IDLE appearance.
		if (m_selectedWidget != Widget::NONE){
			m_layers[m_layerStack.top()]->getWidgetPtr(m_selectedWidget)->setAppearance(Widget::Appearance::IDLE);
		}

		m_selectedWidget = n;

		// If the mouse is pressed on a button, don't reset the appearance back to SELECTED.
		if (m_navMode == NavMode::MOUSE && m_leftMouseDown){
			return;
		}

		// Set newly selected widget's appearance to SELECTED.
		if (m_cursor != n){
			m_layers[m_layerStack.top()]->getWidgetPtr(m_selectedWidget)->setAppearance(Widget::Appearance::SELECTED);
		}
	}
}

// ================================================ //

void GUI::setEditingText(const int n)
{
	static int lastActiveWidget = Widget::NONE;
	m_cursor = n;
	if (m_cursor == Widget::NONE){
		SDL_StopTextInput();
		if (lastActiveWidget != Widget::NONE){
			this->getWidgetPtr(lastActiveWidget)->setActive(false);
			this->getWidgetPtr(lastActiveWidget)->setAppearance(Widget::Appearance::IDLE);
		}
	}
	else{
		this->getWidgetPtr(n)->setAppearance(0, GUI::TextboxCursor);
		this->getWidgetPtr(n)->setActive(true);
		SDL_StartTextInput();
		lastActiveWidget = n;
	}
}

// ================================================ //

void GUI::update(double dt)
{
	if (m_navMode == NavMode::MOUSE){
		m_selectedWidget = Widget::NONE;

		// Determines if a reset check for all Widgets should take place.
		static bool resetAllWidgets = false;
		
		// Create a pixel to represent the mouse position for collision testing.
		SDL_Rect mouse;
		mouse.x = m_mouseX;
		mouse.y = m_mouseY;
		mouse.w = mouse.h = 1;

		// See if mouse is inside bounds of each widget.
		for (int i = 0; i < m_layers[m_layerStack.top()]->getNumWidgets(); ++i){
			if (SDL_HasIntersection(&mouse, &m_layers[m_layerStack.top()]->getWidgetPtr(i)->getPosition())){
				if (this->getWidgetPtr(i)->getType() == Widget::Type::BUTTON ||
					this->getWidgetPtr(i)->getType() == Widget::Type::TEXTBOX){
					this->setSelectedWidget(i);
				}

				// Allow a reset check.
				resetAllWidgets = true;
				break;
			}
		}

		// Reset all of the current layer's widgets if nothing is selected
		if (m_selectedWidget == Widget::NONE && resetAllWidgets){
			if (!m_leftMouseDown){
				// Pass the index of the Widget with the active cursor.
				m_layers[m_layerStack.top()]->resetAllWidgets(m_cursor);

				// Prevent resetAllWidgets() from being called when not necessary.
				resetAllWidgets = false; 
			}
		}
	}

	// Update and render the current layer.
	m_layers[m_layerStack.top()]->update(dt);
	m_layers[m_layerStack.top()]->render();
}

// ================================================ //

