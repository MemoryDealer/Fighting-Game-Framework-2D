// ================================================ //

#ifndef __WIDGETIMPL_HPP__
#define __WIDGETIMPL_HPP__

// ================================================ //

#include "ObjectImpl.hpp"

// ================================================ //

class WidgetImpl : public ObjectImpl
{
public:
	explicit WidgetImpl(void);
	virtual ~WidgetImpl(void);

	// Getter functions
	const bool isEnabled(void) const;

	// Setter functions
	void setEnabled(const bool enabled);

	virtual void update(double dt);

private:
	bool m_enabled;
};

// ================================================ //

inline const bool WidgetImpl::isEnabled(void) const{
	return m_enabled;
}

inline void WidgetImpl::setEnabled(const bool enabled){
	m_enabled = enabled;
}

// ================================================ //

#endif

// ================================================ //