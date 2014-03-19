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

private:
	// SDL components
	SDL_Window*			m_pWindow;
	SDL_Renderer*		m_pRenderer;
};

// ================================================ //

#endif

// ================================================ //