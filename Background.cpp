// ================================================ //

#include "Background.hpp"
#include "BackgroundImpl.hpp"

// ================================================ //

Background::Background(const char* textureFilename)
	:	m_pImpl(new BackgroundImpl(textureFilename))
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