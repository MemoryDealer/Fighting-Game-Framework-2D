// ================================================ //

#include "Object.hpp"
#include "ObjectImpl.hpp"

// ================================================ //

Object::Object(void)
	:	m_pImpl(new ObjectImpl())
{

}

// ================================================ //

Object::~Object(void)
{

}

// ================================================ //

bool Object::setTextureFile(const char* filename)
{
	return m_pImpl->setTextureFile(filename);
}

// ================================================ //
// Getter functions
// ================================================ //

SDL_Texture* Object::getTexturePtr(void) const
{ return m_pImpl->getTexturePtr(); }

// ================================================ //

void Object::update(double dt)
{
	return m_pImpl->update(dt);
}

// ================================================ //