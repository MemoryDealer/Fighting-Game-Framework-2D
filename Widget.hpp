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
	explicit Widget(const int id);
	virtual ~Widget(void);

	enum Link{
		UP = 0,
		DOWN,
		LEFT,
		RIGHT
	};

	enum{
		NONE = -1 // For no selected widget
	};

	// Parsing helpers
	void parseLinks(const std::string& links);

	// Getter functions
	const int getWidgetID(void) const; // widget ID must differ from object ID
	const bool isEnabled(void) const;
	const int getLinkID(const int direction) const;

	// Setter functions
	void setEnabled(const bool enabled);
	void setLinkID(const int direction, const int id);

	virtual void update(double dt) = 0;

protected:
	virtual void setPImpl(std::shared_ptr<WidgetImpl> pImpl);

private:
	std::shared_ptr<WidgetImpl> m_pImpl;
};

// ================================================ //

inline void Widget::setPImpl(std::shared_ptr<WidgetImpl> pImpl){
	m_pImpl = pImpl;
}

// ================================================ //

#endif

// ================================================ //