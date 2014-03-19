// ================================================ //

#ifndef __ENGINE_HPP__
#define __ENGINE_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

class EngineImpl;

// ================================================ //

class Engine : public Singleton<Engine>
{
public:
	explicit Engine(void);
	~Engine(void);

	void clearRenderer(void);
	void renderTexture(SDL_Texture* pTexture); //! this should eventually be replaced with renderObject(), just temporary hack
	//renderObject()...
	void renderPresent(void);

	// Factory functions
	SDL_Texture* loadTexture(const char* filename);

private:
	std::tr1::shared_ptr<EngineImpl> m_pImpl;
};

// ================================================ //

#endif

// ================================================ //