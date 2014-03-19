// ================================================ //

#pragma once

// ================================================ //

// C++ STL
#include <cstdio>
#include <exception>
#include <memory>
#include <fstream>
#include <string>
#include <cassert>

// SDL
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

// Platform-specific headers
#ifdef __WIN32__
#include <Windows.h>
#elif __linux__
	;
#elif __APPLE__
	;
#endif

// Project
#include "Singleton.hpp"
#include "Log.hpp"

// ================================================ //