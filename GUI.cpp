// ================================================ //

#include "GUI.hpp"
#include "Config.hpp"
#include "Engine.hpp"
#include "Button.hpp"

// ================================================ //

std::shared_ptr<SDL_Texture> GUI::ButtonTexture[] = { nullptr, nullptr, nullptr };

// ================================================ //

GUI::GUI(void) :
m_layers(),
m_pCurrentLayer(nullptr),
m_selectedWidget(0),
m_navMode(NavMode::MOUSE),
m_mouseX(0),
m_mouseY(0)
{
	
}

// ================================================ //

GUI::~GUI(void)
{

}

// ================================================ //

void GUI::setSelectedWidget(const int n)
{
	if (n != Widget::NONE){
		// Reset currently selected widget to idle appearance
		if (m_selectedWidget != Widget::NONE){
			m_pCurrentLayer->getWidget(m_selectedWidget)->setAppearance(Widget::Appearance::IDLE);
		}

		// Store new selected widget index
		m_selectedWidget = n;

		// Set newly selected widget's appearance to selected
		m_pCurrentLayer->getWidget(m_selectedWidget)->setAppearance(Widget::Appearance::SELECTED);
	}
}

// ================================================ //

void GUI::update(double dt)
{
	if (m_navMode == NavMode::MOUSE){
		static int lastSelectedWidget = 0;

		// Reset selected widget
		m_selectedWidget = Widget::NONE;

		SDL_Rect mouse;
		mouse.x = m_mouseX;
		mouse.y = m_mouseY;
		mouse.w = mouse.h = 1;

		// See if mouse is inside bounds of each widget
		for (int i = 0; i < m_pCurrentLayer->getNumWidgets(); ++i){
			if (SDL_HasIntersection(&mouse, &m_pCurrentLayer->getWidget(i)->getPosition())){
				this->setSelectedWidget(i);
				lastSelectedWidget = i;
				break;
			}
		}

		// Reset last selected widget's texture if nothing is selected
		if (m_selectedWidget == Widget::NONE){
			m_pCurrentLayer->getWidget(lastSelectedWidget)->setAppearance(Widget::Appearance::IDLE);
		}
	}

	// Update the current layer
	this->getCurrentLayer()->update(dt);
	this->getCurrentLayer()->render();
}

// ================================================ //
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
	}

	for (unsigned int i = 0; i < names.size(); ++i){
		// Allocate widget with ID i (the names list should be in order)
		std::shared_ptr<Widget> pWidget(new T(i));
		std::string value = widgetName + names[i] + ":";

		pWidget->setAppearance(Widget::Appearance::IDLE);
		pWidget->setPosition(c.parseRect(layer, value + "pos"));
		pWidget->setLabel(c.parseValue(layer, value + "label"), c.parseIntValue(layer, value + "labeloffset"));
		pWidget->parseLinks(c.parseValue(layer, value + "links"));

		this->addWidget(pWidget);
	}
}

// Explicitly instantiate template functions for each Widget type
template void GUILayer::parse<Button>(Config& c, const int widgetType, const std::vector<std::string>& names);

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