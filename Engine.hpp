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
// File: Engine.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines Engine singleton class.
// ================================================ //

#ifndef __ENGINE_HPP__
#define __ENGINE_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

class EngineImpl;

// ================================================ //

// Provides some abstraction to the underlying rendering, image loading,
// window management, text/fonts, and networking mechanisms.
class Engine : public Singleton<Engine>
{
public:
	// Allocates EngineImpl.
	explicit Engine(void);

	// Empty destructor.
	~Engine(void);

	// Clears the screen, should be called before rendering anything.
	void clearRenderer(void);

	// Renders everything, should be called after rendering the scene.
	void renderPresent(void);

	// Loads an image and returns the SDL_Texture pointer.
	SDL_Texture* loadTexture(const std::string& filename);

	// Frees an allocated SDL_Texture pointer.
	void destroyTexture(SDL_Texture* pTexture);

	// Getters

	// Returns a pointer to the SDL_Renderer being used. Necessary for
	// certain Objects that render themselves.
	SDL_Renderer* getRenderer(void) const;

	// Returns absolute window width in pixels.
	const int getWindowWidth(void) const;

	// Returns absolute window height in pixels.
	const int getWindowHeight(void) const;

	// Returns virtual window width in pixels.
	const int getLogicalWindowWidth(void) const;

	// Returns virtual window height in pixels.
	const int getLogicalWindowHeight(void) const;

	// Returns true if the window is in focus.
	const bool isWindowFocused(void) const;

	// Returns the maximum frame rate allowed by the engine.
	const int getMaxFrameRate(void) const;

	// Returns relative path to ExtMF.cfg file.
	const std::string getSettingsFile(void) const;

	// Returns relative path to "Data" directory.
	const std::string getDataDirectory(void) const;

	// Returns the game clock speed.
	const double getClockSpeed(void) const;

	// Wrapper for SDL_GetTicks().
	Uint32 getTicks(void) const;

	// Setters

	// Simply changes an internal boolean value. Used for checking if the 
	// window is in focus during the main loop.
	void setWindowFocused(const bool focused);

	// Prevents the frame rate from exceeding the specified max.
	void setMaxFrameRate(const unsigned int max);

	// Instantly changes the resolution of the window.
	void setResolution(const int width, const int height);

	// Sets the game clock speed.
	void setClockSpeed(const double speed);

	// --- //

	// Converts anything to a std::string.
	template<typename T>
	static std::string toString(const T& value)
	{
		std::ostringstream oss;
		oss << value;
		return oss.str();
	}

	// Used by Assert() macro. Do not call directly.
	static bool CustomAssertFunction(bool, char*, int, char*);

#ifdef _DEBUG
#define Assert(exp, desc)\
	if (Engine::CustomAssertFunction((int)exp, desc, __LINE__, __FILE__))\
	{ _asm { int 3 } } // Triggers debugger to break.
#else
#define Assert(exp, desc);
#endif

	// Holds the version of the game/engine. Specified in Engine.cpp.
	static const int VERSION_MAJOR;
	static const int VERSION_MINOR1;
	static const int VERSION_MINOR2;

private:
	std::shared_ptr<EngineImpl> m_pImpl;
};

// ================================================ //

// Getters

inline Uint32 Engine::getTicks(void) const{ 
	return SDL_GetTicks(); 
}

// ================================================ //

#endif

// ================================================ //