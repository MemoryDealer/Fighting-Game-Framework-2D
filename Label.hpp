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
	explicit Label(void);

	// Frees the SDL_Texture.
	virtual ~Label(void);

	// Creates the label texture with the text contained in parameter label.
	void create(const std::string& label);

	// Getters

	// Returns a pointer to the SDL_Texture containing the text.
	SDL_Texture* getTexturePtr(void) const;

	// Returns the offset for rendering the text.
	const int getOffset(void) const;

	// Setters

	// Sets the offset for rendering the text.
	void setOffset(const int offset);

private:
	SDL_Texture* m_pTexture;
	std::string m_label;

	// Space between both left/right sides of Object's dst.
	int m_offset; 
};

// ================================================ //

// Getters

inline SDL_Texture* Label::getTexturePtr(void) const{
	return m_pTexture;
}

inline const int Label::getOffset(void) const{
	return m_offset;
}

// Setters

inline void Label::setOffset(const int offset){
	m_offset = offset;
}

// ================================================ //

#endif

// ================================================ //