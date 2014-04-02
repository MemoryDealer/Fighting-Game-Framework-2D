// ================================================ //

#include "Background.hpp"
#include "BackgroundImpl.hpp"

// ================================================ //

Background::Background(unsigned int type)
	:	m_pImpl(new BackgroundImpl(type))
{
	Object::setPImpl(m_pImpl);
}

// ================================================ //

Background::~Background(void)
{

}

// ================================================ //

void Background::update(double dt)
{
	return m_pImpl->update(dt);
}

// ================================================ //