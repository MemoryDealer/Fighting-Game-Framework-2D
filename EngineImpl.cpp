// ================================================ //

#include "EngineImpl.hpp"

// ================================================ //

EngineImpl::EngineImpl(void)
	:	m_pWindow(nullptr),
		m_pRenderer(nullptr)	
{
	// Initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
		throw std::exception("SDL_Init() failed.");

	// Initialize SDL_image 
	if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) < 0)
		throw std::exception("IMG_Init() failed.");

	// Initialize SDL_ttf
	if(TTF_Init() != 0)
		throw std::exception("TTF_Init() failed.");

	// Initialize SDL_net
	// ...

	// Create the window
	m_pWindow = SDL_CreateWindow("Extreme Metal Fighter", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
	if(m_pWindow == nullptr)
		throw std::exception("SDL_CreateWindow() failed.");

	// Create the renderer
	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(m_pRenderer == nullptr)
		throw std::exception("SDL_CreateRenderer() failed.");
}

// ================================================ //

EngineImpl::~EngineImpl(void)
{
	// Free SDL components in reverse order
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

// ================================================ //