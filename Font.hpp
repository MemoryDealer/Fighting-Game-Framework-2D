// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: Font.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines the Font class. 
// ================================================ //

#ifndef __FONT_HPP__
#define __FONT_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

// A wrapper for the TTF_Font from the SDL_ttf library. 
// A Label object (Label.hpp) needs a TTF_Font pointer which 
// can be loaded and retrieved using this class. 
// Sample usage: 
// Font font("font.ttf", 12); 
// TTF_RenderText_Blended(font.get(), label, color);
class Font
{
public:
	// Opens a true-type font file and loads it using SDL_ttf.
	// The private variable m_pFont holds the font data. 
	// Parameters:
	// ttFile - Path to .ttf file
	// size - Size of font
	explicit Font(const std::string& ttfFile, const int size);

	// Closes font using SDL_ttf.
	~Font(void);

	// Getters

	// Returns the TTF_Font pointer (member variable) created in the constructor.
	TTF_Font* get(void) const;

private:
	// Holds font data for SDL_ttf library. 
	TTF_Font* m_pFont;
};

// ================================================ //

// Getters

inline TTF_Font* Font::get(void) const{
	return m_pFont;
}

// ================================================ //

#endif

// ================================================ //