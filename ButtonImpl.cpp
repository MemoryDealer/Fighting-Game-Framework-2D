// ================================================ //

#include "ButtonImpl.hpp"

// ================================================ //

ButtonImpl::ButtonImpl(const int id) :
WidgetImpl(id)
{
	m_pLabel.reset(new Label());
	m_renderLabel = true;
}

// ================================================ //

ButtonImpl::~ButtonImpl(void)
{

}

// ================================================ //

void ButtonImpl::update(double dt)
{

}

// ================================================ //