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

	Font* pFont = FontManager::getSingletonPtr()->getMainFont();
	SDL_Color color = { 200, 200, 200 };
	SDL_Surface* surf = TTF_RenderText_Blended(pFont->get(), m_label.c_str(), color);
	if (surf == nullptr){
		throw std::exception("Failure loading SDL_Surface in Label::create()");
	}

	m_pTexture = SDL_CreateTextureFromSurface(
		const_cast<SDL_Renderer*>(Engine::getSingletonPtr()->getRenderer()), surf);

	SDL_FreeSurface(surf);
}

// ================================================ //