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

	Log::getSingletonPtr()->logMessage("SDL initialized with SDL_INIT_EVERYTHING");

	// Initialize SDL_image 
	if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) < 0)
		throw std::exception("IMG_Init() failed.");

	Log::getSingletonPtr()->logMessage("SDL_image initialized with IMG_INIT_JPG | IMG_INIT_PNG");

	// Initialize SDL_ttf
	if(TTF_Init() != 0)
		throw std::exception("TTF_Init() failed.");

	Log::getSingletonPtr()->logMessage("SDL_ttf initialized");

	// Initialize SDL_net
	// ...

	// Create the window
	m_pWindow = SDL_CreateWindow("Extreme Metal Fighter", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
	if(m_pWindow == nullptr)
		throw std::exception("SDL_CreateWindow() failed.");

	Log::getSingletonPtr()->logMessage("SDL_Window created successfully");

	// Create the renderer
	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(m_pRenderer == nullptr)
		throw std::exception("SDL_CreateRenderer() failed.");

	Log::getSingletonPtr()->logMessage("SDL_Renderer created successfully");
}

// ================================================ //

EngineImpl::~EngineImpl(void)
{
	// Free SDL components in reverse order
	Log::getSingletonPtr()->logMessage("Destroying SDL_Window and SDL_Renderer...");
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);

	Log::getSingletonPtr()->logMessage("Quitting SDL...");
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

// ================================================ //

void EngineImpl::clearRenderer(void)
{
	SDL_RenderClear(m_pRenderer);
}

// ================================================ //

void EngineImpl::renderPresent(void)
{
	SDL_RenderPresent(m_pRenderer);
}

// ================================================ //