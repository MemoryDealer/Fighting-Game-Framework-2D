// ================================================ //

#include "Button.hpp"
#include "ButtonImpl.hpp"

// ================================================ //

Button::Button(const int id) :
Widget(id),
m_pImpl(new ButtonImpl(id))
{
	Object::setPImpl(m_pImpl);
}

// ================================================ //

Button::~Button(void)
{

}

// ================================================ //

void Button::update(double dt)
{
	return m_pImpl->update(dt);
}

// ================================================ //