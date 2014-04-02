// ================================================ //

#include "Object.hpp"
#include "ObjectImpl.hpp"

// ================================================ //

Object::Object(const unsigned int type)
	:	m_pImpl(nullptr)
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

void Object::setTextureCoordinates(int x, int y, int w, int h)
{
	return m_pImpl->setTextureCoordinates(x, y, w, h);
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

const std::string& Object::getName(void) const
{
	return m_pImpl->getName();
}

// ================================================ //

void Object::render(void)
{
	return m_pImpl->render();
}

// ================================================ //