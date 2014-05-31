// ================================================ //

#ifndef __WIDGET_HPP__
#define __WIDGET_HPP__

// ================================================ //

#include "stdafx.hpp"
#include "Object.hpp"

// ================================================ //

class WidgetImpl;

// ================================================ //
/* Abstract class for any interactive GUI widget */
class Widget : public Object
{
public:
	explicit Widget(void);
	virtual ~Widget(void);

	// Getter functions
	const bool isEnabled(void) const;

	// Setter functions
	void setEnabled(const bool enabled);

	virtual void update(double dt) = 0;

private:
	std::shared_ptr<WidgetImpl> m_pImpl;
};

// ================================================ //

#endif

// ================================================ //