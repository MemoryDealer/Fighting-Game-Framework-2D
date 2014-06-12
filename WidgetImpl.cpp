// ================================================ //

#include "WidgetImpl.hpp"
#include "GUI.hpp"

// ================================================ //

WidgetImpl::WidgetImpl(const int id) :
m_widgetID(id),
m_type(Widget::STATIC),
m_enabled(true)
{
	// Set all links to NONE
	std::fill_n(m_links, 4, Widget::NONE);
}

// ================================================ //

WidgetImpl::~WidgetImpl(void)
{

}

// ================================================ //

void WidgetImpl::setAppearance(const int appearance)
{
	// Store current position
	SDL_Rect pos = this->getPosition();

	switch (this->getType()){
	default:
		break;

	case Widget::Type::BUTTON:
		this->setTexture(GUI::ButtonTexture[appearance]);
		break;
	}

	// Restore original position
	this->setPosition(pos);
}

// ================================================ //

void WidgetImpl::update(double dt)
{

}

// ================================================ //