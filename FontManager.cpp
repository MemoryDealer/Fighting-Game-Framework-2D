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