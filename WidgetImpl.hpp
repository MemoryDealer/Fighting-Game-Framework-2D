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

	// Helper functions
	void parseLinks(const std::string& links);

	// Getter functions
	const int getWidgetID(void) const;
	const int getType(void) const;
	const bool isEnabled(void) const;
	const int getLinkID(const int direction) const;

	// Setter functions
	void setType(const int type);
	void setEnabled(const bool enabled);
	void setLinkID(const int direction, const int id);

	virtual void update(double dt);

private:
	int m_widgetID;
	int m_type;
	bool m_enabled;
	int m_links[4]; // association between widgets for navigation
};

// ================================================ //

// Helpers
inline void WidgetImpl::parseLinks(const std::string& links) {
	char* p = strtok(const_cast<char*>(links.c_str()), ",");
	int direction = Widget::Link::UP;
	while (p){
		int linkID = std::stoi(p);
		this->setLinkID(direction++, linkID);
		p = strtok(nullptr, ",");
	}
}

// Getters
inline const int WidgetImpl::getWidgetID(void) const{
	return m_widgetID;
}

inline const int WidgetImpl::getType(void) const{
	return m_type;
}

inline const bool WidgetImpl::isEnabled(void) const{
	return m_enabled;
}

inline const int WidgetImpl::getLinkID(const int direction) const{
	return m_links[direction];
}

// Setters
inline void WidgetImpl::setType(const int type){
	m_type = type;
}

inline void WidgetImpl::setEnabled(const bool enabled){
	m_enabled = enabled;
}

inline void WidgetImpl::setLinkID(const int direction, const int id){
	m_links[direction] = id;
}

// ================================================ //

#endif

// ================================================ //