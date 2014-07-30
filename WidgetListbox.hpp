// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: WidgetListbox.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines the WidgetListbox class, derived from Widget.
// ================================================ //

#ifndef __WIDGETLISTBOX_HPP__
#define __WIDGETLISTBOX_HPP__

// ================================================ //

#include "Widget.hpp"

// ================================================ //

// A scrolling box containing single lines of text.
class WidgetListbox : public Widget
{
public:
	// Calls Widget's constructor, sets type to LISTBOX.
	explicit WidgetListbox(const int id);

	// Empty destructor.
	virtual ~WidgetListbox(void);

	// Adds a new string to the listbox.
	virtual void addString(const std::string& str);

	// Adds to the index (offset for rendering).
	void addIndex(const int amount);

	// Removes all strings from the listbox and resets index.
	void clear(void);

	// Updates with delta time.
	virtual void update(double dt);

	// Renders the scrollbar and calls Object::render().
	virtual void render(void);

	// Getters

	// Returns the index of Font to use for all labels.
	const int getFont(void) const;

	// Setters

	// Sets the index of the Font to use for all labels.
	void setFont(const int font);

private:
	// Starting index for labels to display.
	int m_index;
	int m_font;
	std::vector<std::shared_ptr<Label>> m_labels;
};

// ================================================ //

inline void WidgetListbox::addIndex(const int amount){
	m_index += amount;
}

inline void WidgetListbox::clear(void){
	m_labels.clear();
	m_index = 0;
}

// Getters

inline const int WidgetListbox::getFont(void) const{
	return m_font;
}

// Setters

inline void WidgetListbox::setFont(const int font){
	m_font = font;
}

// ================================================ //

#endif

// ================================================ //