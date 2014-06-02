// ================================================ //

#include "WidgetImpl.hpp"

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

void WidgetImpl::update(double dt)
{

}

// ================================================ //