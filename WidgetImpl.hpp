// ================================================ //

#ifndef __WIDGETIMPL_HPP__
#define __WIDGETIMPL_HPP__

// ================================================ //

#include "ObjectImpl.hpp"
#include "Widget.hpp"

// ================================================ //

class WidgetImpl : public ObjectImpl
{
public:
	explicit WidgetImpl(const int id);
	virtual ~WidgetImpl(void);

	// Getter functions
	virtual const int getWidgetID(void) const;
	virtual const bool isEnabled(void) const;
	virtual const int getLinkID(const int direction) const;

	// Setter functions
	virtual void setEnabled(const bool enabled);
	virtual void setLinkID(const int direction, const int id);

	virtual void update(double dt);

private:
	int m_widgetID;
	bool m_enabled;
	int m_links[4]; // association between widgets for navigation
};

// ================================================ //

// Getters
inline const bool WidgetImpl::isEnabled(void) const{
	return m_enabled;
}

inline const int WidgetImpl::getWidgetID(void) const{
	return m_widgetID;
}

inline const int WidgetImpl::getLinkID(const int direction) const{
	return m_links[direction];
}

// Setters
inline void WidgetImpl::setEnabled(const bool enabled){
	m_enabled = enabled;
}

inline void WidgetImpl::setLinkID(const int direction, const int id){
	m_links[direction] = id;
}

// ================================================ //

#endif

// ================================================ //