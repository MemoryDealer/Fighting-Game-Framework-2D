// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: Label.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines Label class.
// ================================================ //

#ifndef __LABEL_HPP__
#define __LABEL_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

// A class for dynamically rendering text. Use getTexturePtr()
// to get the texture containing the text.
class Label
{
public:
	// Sets SDL_Texture to nullptr and offset to zero.
	explicit Label(const bool centered = false);

	// Frees the SDL_Texture.
	virtual ~Label(void);

	// Creates the label texture with the text contained in parameter label.
	void create(const std::string& label);

	// Getters

	// Returns a pointer to the SDL_Texture containing the text.
	SDL_Texture* getTexturePtr(void) const;

	// Returns the SDL_Color of the label.
	const SDL_Color getColor(void) const;

	// Returns the offset for rendering the text.
	const int getOffset(void) const;

	// Returns the string content of the label.
	const std::string getText(void) const;

	// Returns true if the text is centered.
	const bool isCentered(void) const;

	// Returns the width of the generated label.
	const int getWidth(void) const;

	// Returns the height of the generated label.
	const int getHeight(void) const;

	// Setters

	// Sets the label's color.
	void setColor(const int r, const int g, const int b, const int a);

	// Sets the label's color.
	void setColor(const SDL_Color& color);

	// Sets the offset for rendering centered text.
	void setOffset(const int offset);

	// Sets whether or not the text is center-oriented.
	void setCentered(const bool centered);

private:
	SDL_Texture* m_pTexture;
	std::string m_label;
	SDL_Color m_color;
	bool m_centered;
	int m_width, m_height;

	// Space between both left/right sides of Object's dst.
	int m_offset;
};

// ================================================ //

// Getters

inline SDL_Texture* Label::getTexturePtr(void) const{
	return m_pTexture;
}

inline const SDL_Color Label::getColor(void) const{
	return m_color;
}

inline const int Label::getOffset(void) const{
	return m_offset;
}

inline const std::string Label::getText(void) const{
	return m_label;
}

inline const bool Label::isCentered(void) const{
	return m_centered;
}

inline const int Label::getWidth(void) const{
	return m_width;
}

inline const int Label::getHeight(void) const{
	return m_height;
}

// Setters

inline void Label::setColor(const int r, const int g, const int b, const int a){
	m_color.r = r; m_color.g = g; m_color.b = b; m_color.a = a;
}

inline void Label::setColor(const SDL_Color& color){
	m_color = color;
}

inline void Label::setOffset(const int offset){
	m_offset = offset;
}

inline void Label::setCentered(const bool centered){
	m_centered = centered;
}

// ================================================ //

#endif

// ================================================ //