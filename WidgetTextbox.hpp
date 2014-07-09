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

class Timer;

// ================================================ //

class WidgetTextbox : public Widget
{
public:
	// Calls Widget's constructor, sets type to TEXTBOX, allocates Label.
	explicit WidgetTextbox(const int id);

	// Empty destructor.
	virtual ~WidgetTextbox(void);

	// Modifies the label of the Widget.
	void handleEditing(const char* text, const bool backspace);

	// Updates with delta time.
	virtual void update(double dt);

	// Renders the cursor and calls Object::render();
	virtual void render(void);

private:
	int m_cursorPos;
	std::shared_ptr<Timer> m_pCursorTimer;
	bool m_renderCursor;
};

// ================================================ //

#endif

// ================================================ //