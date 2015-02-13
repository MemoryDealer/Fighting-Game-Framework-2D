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
// File: FontManager.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines FontManager singleton class. 
// ================================================ //

#ifndef __FONTMANAGER_HPP__
#define __FONTMANAGER_HPP__

// ================================================ //

#include "stdafx.hpp"
#include "Font.hpp"

// ================================================ //

// A singleton class for storing any TTF fonts needed throughout the game. 
// Font objects are stored in an array and can be accessed by their corresponding
// indices, which are enumerated.
// Sample usage:
// FontManager::getSingletonPtr()->loadFont(FontManager::MAIN, "main.ttf", 12);
// FontManager::getSingletonPtr()->getFont(FontManager::MAIN);
class FontManager : public Singleton<FontManager>
{
public:
	// Sets all font pointers to nullptr.
	explicit FontManager(void);

	// Automatically destructs all fonts.
	~FontManager(void);

	// Defines an index for each font needed by the game. These are used in 
	// the loadFont() and getFont() functions. 
	enum {
		MAIN = 0,
		CHAT,

		NUM_FONTS // Gives the size needed for the font array.
	};

	// Calls reset() on the Font std::shared_ptr using the given parameters.
	// Parameters:
	// font - The font to load (e.g., MAIN)
	// file - Path to .ttf file
	// size - Size of font
	void loadFont(const int font, const std::string& file, const int size);

	// Parses ExtMF.cfg and reloads all available fonts. 
	void reloadAll(void);

	// Getters

	// Returns a pointer to the specified Font object.
	// Parameters:
	// font - The font to retrieve (e.g., MAIN)
	Font* getFont(const int font) const;

private:
	// Stores all Font objects
	std::shared_ptr<Font> m_fonts[NUM_FONTS];
};

// ================================================ //

// Getters

inline Font* FontManager::getFont(const int font) const{
	return m_fonts[font].get();
}

// ================================================ //

#endif

// ================================================ //