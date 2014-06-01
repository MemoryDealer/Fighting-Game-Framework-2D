// ================================================ //

#include "Widget.hpp"
#include "WidgetImpl.hpp"

// ================================================ //

Widget::Widget(const int id) :
m_pImpl(nullptr) // Widget is abstract so leave m_pImpl nullptr
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
// Setter functions
// ================================================ //

void Widget::setEnabled(const bool enabled)
{
	return m_pImpl->setEnabled(enabled);
}

// ================================================ //