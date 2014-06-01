// ================================================ //

#include "Font.hpp"
#include "Log.hpp"

// ================================================ //

Font::Font(const std::string& file, const int size) :
m_pFont(nullptr)
{
	// Use SDL_ttf to load a true-type font
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