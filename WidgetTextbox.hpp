// ========================================================================= //
// Fighting game framework (2D) with online multiplayer.
// Copyright(C) 2014 Jordan Sparks <unixunited@live.com>
//
// This program is free software; you can redistribute it and / or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 3
// of the License, or(at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
// ========================================================================= //
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

