// ================================================ //

#ifndef __BUTTONIMPL_HPP__
#define __BUTTONIMPL_HPP__

// ================================================ //

#include "WidgetImpl.hpp"

// ================================================ //

class ButtonImpl : public WidgetImpl
{
public:
	explicit ButtonImpl(void);
	virtual ~ButtonImpl(void);

	virtual void update(double dt);

private:

};

// ================================================ //

#endif

// ================================================ //