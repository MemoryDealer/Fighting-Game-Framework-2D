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