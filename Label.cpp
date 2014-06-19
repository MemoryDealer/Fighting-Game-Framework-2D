// ================================================ //

#include "Label.hpp"
#include "FontManager.hpp"
#include "Engine.hpp"

// ================================================ //

Label::Label(void) :
m_pTexture(nullptr),
m_label(),
m_offset(0)
{

}

// ================================================ //

Label::~Label(void)
{
	SDL_DestroyTexture(m_pTexture);
}

// ================================================ //

void Label::create(const std::string& label)
{
	if (label.empty()){
		Log::getSingletonPtr()->logMessage("Label creation rejected due to blank label text");
		return;
	}

	m_label = label;

	Font* pFont = FontManager::getSingletonPtr()->getFont(FontManager::MAIN); // TODO: add font parameter to this function. 
	SDL_Color color = { 200, 200, 200 };

	// A surface must be created before creating a texture. 
	SDL_Surface* surf = TTF_RenderText_Blended(pFont->get(), m_label.c_str(), color);
	if (surf == nullptr){
		throw std::exception("Failure loading SDL_Surface in Label::create()");
	}

	m_pTexture = SDL_CreateTextureFromSurface(Engine::getSingletonPtr()->getRenderer(), surf);

	// The surface is no longer needed, the memory was copied to the texture. 
	SDL_FreeSurface(surf);
}

// ================================================ //