// ================================================ //

#ifndef __BACKGROUND_HPP__
#define __BACKGROUND_HPP__

// ================================================ //

#include "Object.hpp"

// ================================================ //

class BackgroundImpl;

// ================================================ //

class Background : public Object
{
public:
	explicit Background(unsigned int type);
	virtual ~Background(void);

	virtual void update(double dt);

private:
	std::tr1::shared_ptr<BackgroundImpl> m_pImpl;
};

// ================================================ //

#endif

// ================================================ //