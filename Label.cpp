// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: Label.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements Label class.
// ================================================ //

#include "Label.hpp"
#include "FontManager.hpp"
#include "Engine.hpp"

// ================================================ //

Label::Label(const bool centered) :
m_pTexture(nullptr),
m_color(),
m_centered(centered),
m_width(0),
m_height(0),
m_font(FontManager::MAIN),
m_offset(0)
{
	m_color = { 200, 200, 200, 255 };
}

// ================================================ //

Label::~Label(void)
{
	SDL_DestroyTexture(m_pTexture);
}

// ================================================ //

void Label::create(const std::string& label, const int wrap)
{
	const int MAX_LENGTH = 512;
	if (label.length() > MAX_LENGTH){
		Log::getSingletonPtr()->logMessage("Label creation rejected, text over maximum length!");
		return;
	}

	Font* pFont = FontManager::getSingletonPtr()->getFont(m_font);

	if (label == " "){
		return;
	}
	else if (label.empty()){
		//label.assign(" ");
	}
	else if (label[0] == ' '){
		//label = label.substr(1, m_label.length() - 1);
	}

	// A surface must be created before creating a texture.
	SDL_Surface* surf = (wrap == 0) ? TTF_RenderText_Blended(pFont->get(), label.c_str(), m_color)
		: TTF_RenderText_Blended_Wrapped(pFont->get(), label.c_str(), m_color, wrap);
	if (surf == nullptr){
		throw std::exception("Failure loading SDL_Surface in Label::create()");
	}

	m_pTexture = SDL_CreateTextureFromSurface(Engine::getSingletonPtr()->getRenderer(), surf);

	m_width = surf->w;
	m_height = surf->h;

	// The surface is no longer needed, the memory was copied to the texture.
	SDL_FreeSurface(surf);
}

// ================================================ //