// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: FontManager.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements the FontManager singleton class. 
// ================================================ //

#include "FontManager.hpp"
#include "Config.hpp"
#include "Engine.hpp"

// ================================================ //

template<> FontManager* Singleton<FontManager>::msSingleton = nullptr;

// ================================================ //

FontManager::FontManager(void) :
m_fonts()
{

}

// ================================================ //

FontManager::~FontManager(void)
{

}

// ================================================ //

void FontManager::loadFont(const int font, const std::string& file, const int size)
{
	m_fonts[font].reset(new Font(file, size));
}

// ================================================ //

void FontManager::reloadAll(void)
{
	Config e(Engine::getSingletonPtr()->getSettingsFile());

	// Open the theme file specified in ExtMF.cfg. 
	Config theme(Engine::getSingletonPtr()->getDataDirectory() + 
		"/" + e.parseValue("GUI", "theme")); 

	if (theme.isLoaded()){
		// Load each font. 
		m_fonts[FontManager::MAIN].reset(new Font(
			Engine::getSingletonPtr()->getDataDirectory() + "/" + theme.parseValue("font.main", "file"), 
			theme.parseIntValue("font.main", "size")));
		m_fonts[FontManager::CHAT].reset(new Font(
			Engine::getSingletonPtr()->getDataDirectory() + "/" + theme.parseValue("font.chat", "file"),
			theme.parseIntValue("font.chat", "size")));
	}
}

// ================================================ //