// ================================================ //

#include "Button.hpp"
#include "ButtonImpl.hpp"

// ================================================ //

Button::Button(void) :
m_pImpl(new ButtonImpl())
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
	printf("Updating button...\n");
}

// ================================================ //