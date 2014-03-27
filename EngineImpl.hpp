// ================================================ //

#ifndef __ENGINEIMPL_HPP__
#define __ENGINEIMPL_HPP__

// ================================================ //

#include "Object.hpp"

// ================================================ //

class EngineImpl
{
public:
	explicit EngineImpl(void);
	~EngineImpl(void);

	void clearRenderer(void);
	void renderPresent(void);

	// Factory functions
	SDL_Texture* loadTexture(const char* filename);

	// Destroy functions
	void destroyTexture(SDL_Texture* pTexture);

	// Setter functions
	void setWindowFocused(const bool focused);

	// Getter functions
	const SDL_Renderer* getRenderer(void) const;
	const int getWindowWidth(void) const;
	const int getWindowHeight(void) const;
	const bool isWindowFocused(void) const;

private:
	// SDL components
	SDL_Window*			m_pWindow;
	SDL_Renderer*		m_pRenderer;

	unsigned int m_width, m_height;
	bool				m_windowFocused;
};

// ================================================ //

// Setters
inline void EngineImpl::setWindowFocused(const bool focused)
{ m_windowFocused = focused; }

// Getters
inline const SDL_Renderer* EngineImpl::getRenderer(void) const
{ return m_pRenderer; }

inline const bool EngineImpl::isWindowFocused(void) const
{ return m_windowFocused; }

inline const int EngineImpl::getWindowWidth(void) const
{ return m_width; }

inline const int EngineImpl::getWindowHeight(void) const
{ return m_height; }

// ================================================ //

#endif

// ================================================ //