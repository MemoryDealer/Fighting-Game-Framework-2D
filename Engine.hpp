// ================================================ //

#ifndef __ENGINE_HPP__
#define __ENGINE_HPP__

// ================================================ //

#include "stdafx.hpp"
#include "Object.hpp"

// ================================================ //

class EngineImpl;

// ================================================ //

class Engine : public Singleton<Engine>
{
public:
	explicit Engine(void);
	~Engine(void);

	void clearRenderer(void);
	void renderObject(const Object* pObject);
	void renderPresent(void);

	// Factory functions
	SDL_Texture* loadTexture(const char* filename);

	// Destroy functions
	void destroyTexture(SDL_Texture* pTexture);

private:
	std::tr1::shared_ptr<EngineImpl> m_pImpl;
};

// ================================================ //

#endif

// ================================================ //