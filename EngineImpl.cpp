// ================================================ //

#include "EngineImpl.hpp"

// ================================================ //

EngineImpl::EngineImpl(void)
	:	m_pWindow(nullptr),
		m_pRenderer(nullptr),
		m_width(640),
		m_height(480)
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
	if(SDLNet_Init() < 0)
		throw std::exception(("SDLNet_Init() failed."));

	Log::getSingletonPtr()->logMessage("SDL_net initialized");

	// Create the window
	m_pWindow = SDL_CreateWindow("Extreme Metal Fighter", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, m_width, m_height, 0);
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
	SDLNet_Quit();
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

void EngineImpl::renderObject(const Object* pObject)
{
	SDL_RenderCopy(m_pRenderer, pObject->getTexturePtr(), nullptr, &pObject->getPosition());
}

// ================================================ //

void EngineImpl::renderPresent(void)
{
	SDL_RenderPresent(m_pRenderer);
}

// ================================================ //

SDL_Texture* EngineImpl::loadTexture(const char* filename)
{
	SDL_Texture* tex = nullptr;

	tex = IMG_LoadTexture(m_pRenderer, filename);
	if(tex == nullptr)
		Log::getSingletonPtr()->logMessage("Failed to load texture from file: \"" + std::string(filename) + "\"");

	Log::getSingletonPtr()->logMessage("Texture \"" + std::string(filename) + "\" loaded!");

	return tex;
}

// ================================================ //

void EngineImpl::destroyTexture(SDL_Texture* pTexture)
{
	SDL_DestroyTexture(pTexture);
}

// ================================================ //