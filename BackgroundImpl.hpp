// ================================================ //

#ifndef __BACKGROUNDIMPL_HPP__
#define __BACKGROUNDIMPL_HPP__

// ================================================ //

#include "ObjectImpl.hpp"

// ================================================ //

class BackgroundImpl : public ObjectImpl
{
public:
	explicit BackgroundImpl(unsigned int type);
	virtual ~BackgroundImpl(void);

	// Setter functions
	virtual bool setTextureFile(const char* filename);

	virtual void update(double dt);

private:
	unsigned int m_type;
};

// ================================================ //

#endif

// ================================================ //