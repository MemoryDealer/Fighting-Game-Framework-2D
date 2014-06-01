// ================================================ //

#include "Object.hpp"
#include "ObjectImpl.hpp"
#include "MessageRouter.hpp"

// ================================================ //

Object::Object(void) :
m_pImpl(nullptr)
{
	MessageRouter::getSingletonPtr()->addObject(static_cast<Object*>(this));
}

// ================================================ //

Object::~Object(void)
{
	MessageRouter::getSingletonPtr()->removeObject(m_pImpl->getID());
}

// ================================================ //
// Setter functions
// ================================================ //

bool Object::setTextureFile(const std::string& filename)
{
	return m_pImpl->setTextureFile(filename);
}

void Object::setTextureCoordinates(const int x, const int y, const int w, const int h)
{
	return m_pImpl->setTextureCoordinates(x, y, w, h);
}

// ================================================ //

void Object::setLabel(const std::string& label)
{
	return m_pImpl->setLabel(label);
}

// ================================================ //

void Object::setPosition(const int x, const int y)
{
	return m_pImpl->setPosition(x, y);
}

// ================================================ //

void Object::setPosition(const int x, const int y, const int w, const int h)
{
	return m_pImpl->setPosition(x, y, w, h);
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

const int Object::getID(void) const
{
	return m_pImpl->getID();
}

// ================================================ //

const bool Object::isDead(void) const
{ 
	return m_pImpl->isDead();
}

// ================================================ //
// Other functions
// ================================================ //

void Object::sendMessage(const Message& msg)
{
	return m_pImpl->sendMessage(msg);
}

// ================================================ //

void Object::render(void)
{
	return m_pImpl->render();
}

// ================================================ //