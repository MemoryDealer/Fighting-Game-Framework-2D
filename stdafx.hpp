// ================================================ //

#pragma once

// ================================================ //

#pragma warning (disable : 4075) // warning LNK4075: ignoring '/EDITANDCONTINUE' due to '/INCREMENTAL:NO' specification
#pragma warning (disable : 4098) // warning LNK4098: defaultlib 'msvcrt.lib' conflicts with use of other libs; use /NODEFAULTLIB:library

// ================================================ //

// C++ STL
#include <cstdio>
#include <exception>
#include <memory>
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <complex>
#include <algorithm>

// SDL
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_net.h>

// Project
#include "Singleton.hpp"
#include "Log.hpp"

// Platform-specific headers
#ifdef __WIN32__
#define _WINSOCKAPI_ // prevents automatic winsock.h inclusion 
#include <Windows.h>
#elif __linux__
	;
#elif __APPLE__
	;
#endif

// ================================================ //