// ================================================ //

#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

class ObjectImpl;

// ================================================ //

class Object
{
public:
	/** \brief An Object is *anything* that can be rendered and/or interacted with.
		An abstract class to derive from for any new object in the game. */
	explicit Object(const char* textureFilename = "");
	virtual ~Object(void);

	// Setter functions
	virtual bool setTextureFile(const char* filename);

	virtual void setPosition(const int x, const int y);
	virtual void setPosition(const SDL_Rect& pos);

	// Getter functions
	virtual SDL_Texture* getTexturePtr(void) const;
	virtual const SDL_Rect& getPosition(void) const;
	virtual const std::string& getName(void) const;

	virtual void update(double dt) = 0;

protected:
	/** \brief This should be called in the constructor of any child class of Object,
		passing the local m_pImpl of the child class as the argument. This basically
		allows "pointer to implementation" polymorphism. */
	virtual void setPImpl(std::tr1::shared_ptr<ObjectImpl> pImpl);

private:
	std::tr1::shared_ptr<ObjectImpl> m_pImpl;
};

// ================================================ //

inline void Object::setPImpl(std::tr1::shared_ptr<ObjectImpl> pImpl)
{ m_pImpl = pImpl; }

// ================================================ //

#endif

// ================================================ //