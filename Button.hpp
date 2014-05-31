// ================================================ //

#ifndef __BUTTON_HPP__
#define __BUTTON_HPP__

// ================================================ //

#include "Widget.hpp"

// ================================================ //

class ButtonImpl;

// ================================================ //

class Button : public Widget
{
public:
	explicit Button(void);
	virtual ~Button(void);

	virtual void update(double dt);

private:
	std::shared_ptr<ButtonImpl> m_pImpl;
};

// ================================================ //

#endif

// ================================================ //