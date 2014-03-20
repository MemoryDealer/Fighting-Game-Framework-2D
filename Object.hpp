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
	explicit Object(void);
	virtual ~Object(void);

	bool setTextureFile(const char* filename);

	// Getter functions
	SDL_Texture* getTexturePtr(void) const;

	void update(double dt);

private:
	std::tr1::shared_ptr<ObjectImpl> m_pImpl;
};

// ================================================ //

#endif

// ================================================ //