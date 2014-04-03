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
	void renderPresent(void);

	// Factory functions
	SDL_Texture* loadTexture(const char* filename);

	// Destroy functions
	void destroyTexture(SDL_Texture* pTexture);

	// Setter functions
	void setWindowFocused(const bool focused);
	void setMaxFrameRate(const unsigned int max);

	// Getter functions
	const SDL_Renderer* getRenderer(void) const;
	const int getWindowWidth(void) const;
	const int getWindowHeight(void) const;
	const int getLogicalWindowWidth(void) const;
	const int getLogicalWindowHeight(void) const;
	const bool isWindowFocused(void) const;
	const int getMaxFrameRate(void) const;

	// Some other functions
	template<typename T>
	static std::string toString(const T& value)
	{
		std::ostringstream oss;
		oss << value;
		return oss.str();
	}
#ifdef _DEBUG
	static bool CustomAssertFunction(bool, char*, int, char*);

#define Assert(exp, desc)\
	if(Engine::CustomAssertFunction((int)exp, desc, __LINE__, __FILE__))\
	{ _asm { int 3 } } // trigger debugger to break
#else
#define Assert(exp, desc);
#endif

private:
	std::tr1::shared_ptr<EngineImpl> m_pImpl;
};

// ================================================ //

#endif

// ================================================ //