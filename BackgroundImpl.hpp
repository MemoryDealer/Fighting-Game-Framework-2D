// ================================================ //

#ifndef __BACKGROUNDIMPL_HPP__
#define __BACKGROUNDIMPL_HPP__

// ================================================ //

#include "ObjectImpl.hpp"

// ================================================ //

class BackgroundImpl : public ObjectImpl
{
public:
	explicit BackgroundImpl(const char* textureFilename);
	virtual ~BackgroundImpl(void);

	virtual void update(double dt);

private:
	// additional textures...
};

// ================================================ //

#endif

// ================================================ //