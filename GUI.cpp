// ================================================ //

#include "GUI.hpp"
#include "Config.hpp"
#include "Engine.hpp"

// ================================================ //

GUI::GUI(void) :
m_layers(),
m_pCurrentLayer(nullptr),
m_selectedWidget(-1),
m_navMode(NavMode::MOUSE)
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
	// Reset selected widget
	m_selectedWidget = -1;

	if (m_navMode == NavMode::MOUSE){
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

void GUILayer::render(void)
{
	for (WidgetList::iterator itr = m_widgets.begin();
		itr != m_widgets.end();
		++itr){
		(*itr)->render();
	}
}

// ================================================ //