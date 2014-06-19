// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
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