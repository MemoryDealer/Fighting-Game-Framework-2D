// ================================================ //

#ifndef __ENGINEIMPL_HPP__
#define __ENGINEIMPL_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

class EngineImpl
{
public:
	explicit EngineImpl(void);
	~EngineImpl(void);

	void clearRenderer(void);
	void renderTexture(SDL_Texture* pTexture);
	void renderPresent(void);

	// Factory functions
	SDL_Texture* loadTexture(const char* filename);

private:
	// SDL components
	SDL_Window*			m_pWindow;
	SDL_Renderer*		m_pRenderer;
};

// ================================================ //

#endif

// ================================================ //