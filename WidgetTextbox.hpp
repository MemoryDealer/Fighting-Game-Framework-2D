// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: WidgetTextbox.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines the WidgetTextbox class, derived from Widget.
// ================================================ //

#ifndef __WIDGETTEXTBOX_HPP__
#define __WIDGETTEXTBOX_HPP__

// ================================================ //

#include "Widget.hpp"

// ================================================ //

class Timer;

// ================================================ //

// A textbox that displays text, can be edited.
class WidgetTextbox : public Widget
{
public:
	// Calls Widget's constructor, sets type to TEXTBOX, allocates Label.
	explicit WidgetTextbox(const int id);

	// Empty destructor.
	virtual ~WidgetTextbox(void);

	// Modifies the label of the Widget.
	void handleEditing(const char* text, const bool backspace = false);

	// Updates with delta time.
	virtual void update(double dt);

	// Calls Object::render() renders the cursor.
	virtual void render(void);

	// Getters

	// Returns the active text in the editing field.
	virtual const std::string getText(void) const;

	// Setters

	// Assigns offset to zero, calls Label::create() on the internal Label,
	// and assigns m_text to label. Scrolls text and increments offset until correct.
	virtual void setLabel(const std::string& label, const int offset = 0);

private:
	int m_cursorPos;
	int m_offset;
	std::string m_text;
	std::shared_ptr<Timer> m_pCursorTimer;
	bool m_renderCursor;
};

// ================================================ //

inline const std::string WidgetTextbox::getText(void) const{
	return m_text;
}

// ================================================ //

#endif

// ================================================ //

