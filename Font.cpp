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
// File: Font.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements the Font class. 
// ================================================ //

#include "Font.hpp"
#include "Log.hpp"

// ================================================ //

Font::Font(const std::string& file, const int size) :
m_pFont(nullptr)
{
	m_pFont = TTF_OpenFont(file.c_str(), size);
	if (m_pFont == nullptr){
		std::string exc = "Failed to load font from file \"" + file + "\"";
		throw std::exception(exc.c_str());
	}

	Log::getSingletonPtr()->logMessage("Font loaded successfully! (\"" + file + "\")");
}

// ================================================ //

Font::~Font(void)
{
	TTF_CloseFont(m_pFont);
}

// ================================================ //