// ================================================ //

#include "GUI.hpp"
#include "Config.hpp"
#include "Engine.hpp"
#include "Button.hpp"

// ================================================ //

std::string GUI::m_buttonTheme = "";

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

void GUI::renderSelector(void)
{
	// Render selector around active widget
	SDL_Rect selector = m_pCurrentLayer->getWidget(m_selectedWidget)->getPosition();
	const int offset = 0;
	selector.x -= offset; selector.y -= offset;
	selector.w += offset * 2; selector.h += offset * 2;

	SDL_SetRenderDrawColor(const_cast<SDL_Renderer*>(Engine::getSingletonPtr()->getRenderer()), 155, 255, 255, 255);
	SDL_RenderDrawRect(const_cast<SDL_Renderer*>(Engine::getSingletonPtr()->getRenderer()), &selector);

	// ..temporary
	SDL_SetRenderDrawColor(const_cast<SDL_Renderer*>(Engine::getSingletonPtr()->getRenderer()), 0, 0, 0, 255);
}

// ================================================ //

void GUI::update(double dt)
{
	if (m_navMode == NavMode::MOUSE){
		// Reset selected widget
		m_selectedWidget = -1;

		SDL_Rect mouse;
		mouse.x = m_mouseX;
		mouse.y = m_mouseY;
		mouse.w = mouse.h = 1;

		// See if mouse is inside bounds of each widget
		for (int i = 0; i < m_pCurrentLayer->getNumWidgets(); ++i){
			if (SDL_HasIntersection(&mouse, &m_pCurrentLayer->getWidget(i)->getPosition())){
				m_selectedWidget = i;
				this->renderSelector();
				break;
			}
		}
	}
	else{
		this->renderSelector();
	}
}

// ================================================ //
// ================================================ //

GUILayer::GUILayer(void) :
m_widgets()
{

}

// ================================================ //

GUILayer::~GUILayer(void)
{

}

// ================================================ //

template<typename T>
void GUILayer::parse(Config& c, const int widgetType, const std::vector<std::string>& names)
{
	std::string widgetName;
	std::string layer = "layer." + m_layerName;
	switch (widgetType){
	default:
	case Widget::Type::STATIC:
		widgetName = "static.";
		break;

	case Widget::Type::BUTTON:
		widgetName = "button.";
		break;
	}

	std::string tex = GUI::m_buttonTheme;

	for (unsigned int i = 0; i < names.size(); ++i){
		// Allocate widget with ID i (the names list should be in order)
		std::shared_ptr<Widget> pWidget(new T(i));
		std::string value = widgetName + names[i] + ":";

		pWidget->setTextureFile(tex);
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