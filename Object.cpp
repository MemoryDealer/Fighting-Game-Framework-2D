// ================================================ //

#include "Object.hpp"
#include "ObjectImpl.hpp"

// ================================================ //

Object::Object(const char* textureFilename)
	:	m_pImpl(new ObjectImpl(textureFilename))
{

}

// ================================================ //

Object::~Object(void)
{

}

// ================================================ //
// Setter functions
// ================================================ //

bool Object::setTextureFile(const char* filename)
{
	return m_pImpl->setTextureFile(filename);
}

// ================================================ //

void Object::setPosition(const int x, const int y)
{
	return m_pImpl->setPosition(x, y);
}

// ================================================ //

void Object::setPosition(const SDL_Rect& pos)
{
	return m_pImpl->setPosition(pos);
}

// ================================================ //
// Getter functions
// ================================================ //

SDL_Texture* Object::getTexturePtr(void) const
{ 
	return m_pImpl->getTexturePtr(); 
}

// ================================================ //

const SDL_Rect& Object::getPosition(void) const
{
	return m_pImpl->getPosition();
}

// ================================================ //

void Object::update(double dt)
{
	return m_pImpl->update(dt);
}

// ================================================ //