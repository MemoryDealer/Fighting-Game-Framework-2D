// ================================================ //

#ifndef __PLAYERIMPL_HPP__
#define __PLAYERIMPL_HPP__

// ================================================ //

#include "ObjectImpl.hpp"

// ================================================ //

class PlayerImpl : public ObjectImpl
{
public:
	explicit PlayerImpl(const char* textureFilename);
	virtual ~PlayerImpl(void);

	virtual void update(double dt);

private:

};

// ================================================ //

#endif

// ================================================ //