// ================================================ //

#include "Widget.hpp"
#include "WidgetImpl.hpp"

// ================================================ //

Widget::Widget(const int id) :
m_pImpl(new WidgetImpl(id)) // Widget is abstract so leave m_pImpl nullptr
{
	
}

// ================================================ //

Widget::~Widget(void)
{

}

// ================================================ //
// Getter functions
// ================================================ //

const int Widget::getWidgetID(void) const
{
	return m_pImpl->getWidgetID();
}

// ================================================ //

const bool Widget::isEnabled(void) const
{
	return m_pImpl->isEnabled();
}

// ================================================ //

const int Widget::getLinkID(const int direction) const
{
	return m_pImpl->getLinkID(direction);
}

// ================================================ //
// Setter functions
// ================================================ //

void Widget::setEnabled(const bool enabled)
{
	return m_pImpl->setEnabled(enabled);
}

// ================================================ //

void Widget::setLinkID(const int direction, const int id)
{
	return m_pImpl->setLinkID(direction, id);
}

// ================================================ //