// ========================================================================= //
// Fighting game framework (2D) with online multiplayer.
// Copyright(C) 2014 Jordan Sparks <unixunited@live.com>
//
// This program is free software; you can redistribute it and / or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 3
// of the License, or(at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
// ========================================================================= //
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
	void setClockSpeed(const double speed);

	SDL_Renderer* getRenderer(void) const;
	const int getWindowWidth(void) const;
	const int getWindowHeight(void) const;
	const int getLogicalWindowWidth(void) const;
	const int getLogicalWindowHeight(void) const;
	const bool isWindowFocused(void) const;
	const int getMaxFrameRate(void) const;
	const std::string getSettingsFile(void) const;
	const std::string getDataDirectory(void) const;
	const double getClockSpeed(void) const;

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

	// Speed at which game clock runs; 1.0 = 100%, 0.5 = 50%, etc.
	double m_clockSpeed;
};

// ================================================ //

// Setters

inline void EngineImpl::setWindowFocused(const bool focused){ 
	m_windowFocused = focused; 
}

inline void EngineImpl::setMaxFrameRate(const unsigned int max){ 
	m_maxFrameRate = max; 
}

inline void EngineImpl::setClockSpeed(const double speed){
	m_clockSpeed = speed;
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

inline const double EngineImpl::getClockSpeed(void) const{
	return m_clockSpeed;
}

// ================================================ //

#endif

// ================================================ //