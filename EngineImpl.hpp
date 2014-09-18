// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: EngineImpl.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines EngineImpl class.
// ================================================ //

#ifndef __ENGINEIMPL_HPP__
#define __ENGINEIMPL_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

// PImpl idiom class for Engine. See Engine.hpp for function details 
// that are not specified here.
class EngineImpl
{
public:
	// Initializes SDL (with everything), SDL_img, SDL_ttf, and SDL_net.
	// Creates the rendering window and sets up the renderer.
	explicit EngineImpl(void);

	// Frees the renderer and the window, then frees all SDL components
	// in reverse order from which they were initialized.
	~EngineImpl(void);

	void clearRenderer(void);
	void renderPresent(void);

	SDL_Texture* loadTexture(const std::string& filename);

	void destroyTexture(SDL_Texture* pTexture);

	void setWindowFocused(const bool focused);
	void setMaxFrameRate(const unsigned int max);
	void setResolution(const int width, const int height);

	SDL_Renderer* getRenderer(void) const;
	const int getWindowWidth(void) const;
	const int getWindowHeight(void) const;
	const int getLogicalWindowWidth(void) const;
	const int getLogicalWindowHeight(void) const;
	const bool isWindowFocused(void) const;
	const int getMaxFrameRate(void) const;
	const std::string getSettingsFile(void) const;
	const std::string getDataDirectory(void) const;

private:
	SDL_Window*			m_pWindow;
	SDL_Renderer*		m_pRenderer;

	unsigned int		m_width, m_height;
	// Represents the virtual resolution.
	unsigned int		m_logicalWidth, m_logicalHeight;
	bool				m_windowFocused;
	unsigned int		m_maxFrameRate;
	std::string			m_windowTitle;
	
	// Relative path to ExtMF.cfg file.
	std::string			m_settingsFile;
	// Relative path to the "Data" directory.
	std::string			m_dataDirectory;
};

// ================================================ //

// Setters

inline void EngineImpl::setWindowFocused(const bool focused){ 
	m_windowFocused = focused; 
}

inline void EngineImpl::setMaxFrameRate(const unsigned int max){ 
	m_maxFrameRate = max; 
}

// Getters

inline SDL_Renderer* EngineImpl::getRenderer(void) const{ 
	return m_pRenderer; 
}

inline const bool EngineImpl::isWindowFocused(void) const{ 
	return m_windowFocused; 
}

inline const int EngineImpl::getWindowWidth(void) const{ 
	return m_width; 
}

inline const int EngineImpl::getWindowHeight(void) const{ 
	return m_height; 
}

inline const int EngineImpl::getLogicalWindowWidth(void) const{ 
	return m_logicalWidth; 
}

inline const int EngineImpl::getLogicalWindowHeight(void) const{ 
	return m_logicalHeight; 
}

inline const int EngineImpl::getMaxFrameRate(void) const{ 
	return m_maxFrameRate; 
}

inline const std::string EngineImpl::getSettingsFile(void) const{
	return m_settingsFile;
}

inline const std::string EngineImpl::getDataDirectory(void) const{
	return m_dataDirectory;
}

// ================================================ //

#endif

// ================================================ //