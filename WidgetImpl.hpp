// ================================================ //

#ifndef __WIDGETIMPL_HPP__
#define __WIDGETIMPL_HPP__

// ================================================ //

#include "ObjectImpl.hpp"

// ================================================ //

class WidgetImpl : public ObjectImpl
{
public:
	explicit WidgetImpl(const int id);
	virtual ~WidgetImpl(void);

	// Getter functions
	const int getWidgetID(void) const;
	const bool isEnabled(void) const;

	// Setter functions
	void setEnabled(const bool enabled);

	virtual void update(double dt);

private:
	int m_widgetID;
	bool m_enabled;
};

// ================================================ //

inline const bool WidgetImpl::isEnabled(void) const{
	return m_enabled;
}

inline const int WidgetImpl::getWidgetID(void) const{
	return m_widgetID;
}

inline void WidgetImpl::setEnabled(const bool enabled){
	m_enabled = enabled;
}

// ================================================ //

#endif

// ================================================ //