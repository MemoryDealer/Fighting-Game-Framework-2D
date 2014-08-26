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

	// Sets the label value of entry n.
	virtual void setEntry(const int n, const std::string& str);

	// Adds to the index (offset for rendering).
	virtual void addIndex(const int amount);

	// Removes first entry from the listbox that matches the string.
	virtual void removeEntry(const std::string& str);
	
	// Removes all strings from the listbox and resets index.
	virtual void clear(void);

	// Updates with delta time.
	virtual void update(double dt);

	// Renders the scrollbar and calls Object::render().
	virtual void render(void);

	// Getters

	// Returns the index of Font to use for all labels.
	virtual const int getFont(void) const;

	// Setters

	// Sets the index of the Font to use for all labels.
	virtual void setFont(const int font);

	// Sets the offset of the border from the listbox texture.
	virtual void setBorderOffset(const int offset);

private:
	// Starting index for labels to display.
	int m_index;
	int m_font;
	std::vector<std::shared_ptr<Label>> m_labels;
	SDL_Texture* m_pBorder;
	int m_borderOffset;
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

inline void WidgetListbox::setBorderOffset(const int offset){
	m_borderOffset = offset;
}

// ================================================ //

#endif

// ================================================ //