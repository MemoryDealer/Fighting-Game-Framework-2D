// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: WidgetImpl.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines the WidgetImpl Pimpl idiom class, used by Widget. 
// ================================================ //

#ifndef __WIDGETIMPL_HPP__
#define __WIDGETIMPL_HPP__

// ================================================ //

#include "ObjectImpl.hpp"
#include "Widget.hpp"

// ================================================ //

// Pimpl class definition for Widget. 
class WidgetImpl : public ObjectImpl
{
public:
	// Initializes the Widget ID to id, assigns the type to STATIC by default,
	// and sets it to enabled by default. Sets all links to Widget::NONE. 
	explicit WidgetImpl(const int id);

	// Empty destructor. 
	virtual ~WidgetImpl(void);

	// See Widget.hpp. 
	void parseLinks(const std::string& links);

	// Getters

	// See Widget.hpp. 
	const int getWidgetID(void) const;

	// See Widget.hpp. 
	const int getType(void) const;

	// See Widget.hpp. 
	const bool isEnabled(void) const;

	// See Widget.hpp. 
	const int getLinkID(const int direction) const;

	// Setters

	// See Widget.hpp. 
	void setType(const int type);

	// See Widget.hpp. 
	void setEnabled(const bool enabled);

	// See Widget.hpp. 
	void setLinkID(const int direction, const int id);

	// See Widget.hpp. 
	virtual void setAppearance(const int appearance);

	// See Widget.hpp. 
	virtual void update(double dt);

private:
	int m_widgetID;
	int m_type;
	bool m_enabled;

	// Assocations between this widget and other widgets for SELECTOR navigation. 
	int m_links[4];
};

// ================================================ //

inline void WidgetImpl::parseLinks(const std::string& links) {
	// Get each link ID, delimited by commas
	char* p = strtok(const_cast<char*>(links.c_str()), ",");
	int direction = Widget::Link::UP;
	while (p && direction < 4){
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