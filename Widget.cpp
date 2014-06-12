// ================================================ //

#include "Widget.hpp"
#include "WidgetImpl.hpp"

// ================================================ //

Widget::Widget(const int id) :
m_pImpl(nullptr/*new WidgetImpl(id)*/) // should this be left nullptr and child widgets called Widget::setPImpl()?
{
	//Object::setPImpl(m_pImpl);
}

// ================================================ //

Widget::~Widget(void)
{

}

// ================================================ //
// Helper functions
// ================================================ //

void Widget::parseLinks(const std::string& links)
{
	return m_pImpl->parseLinks(links);
}

// ================================================ //
// Getter functions
// ================================================ //

const int Widget::getWidgetID(void) const
{
	return m_pImpl->getWidgetID();
}

// ================================================ //

const int Widget::getType(void) const
{
	return m_pImpl->getType();
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

void Widget::setType(const int type)
{
	return m_pImpl->setType(type);
}

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

void Widget::setAppearance(const int appearance)
{
	return m_pImpl->setAppearance(appearance);
}

// ================================================ //