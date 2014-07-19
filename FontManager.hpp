// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
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