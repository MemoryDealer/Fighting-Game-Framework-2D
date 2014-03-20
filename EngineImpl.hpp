// ================================================ //

#ifndef __ENGINEIMPL_HPP__
#define __ENGINEIMPL_HPP__

// ================================================ //

#include "stdafx.hpp"
#include "Object.hpp"

// ================================================ //

class EngineImpl
{
public:
	explicit EngineImpl(void);
	~EngineImpl(void);

	void clearRenderer(void);
	void renderObject(const Object* pObject);
	void renderPresent(void);

	// Factory functions
	SDL_Texture* loadTexture(const char* filename);

	// Destroy functions
	void destroyTexture(SDL_Texture* pTexture);

private:
	// SDL components
	SDL_Window*			m_pWindow;
	SDL_Renderer*		m_pRenderer;
};

// ================================================ //

#endif

// ================================================ //