// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: stdafx.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Includes all common headers needed, should be included
// at the top of any header that needs them.
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
#include <stack>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <complex>
#include <algorithm>
#include <locale>

// SDL
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

// RakNet
#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include <RakNetTypes.h>
#include <BitStream.h>

// Project
#include "Singleton.hpp"
#include "Log.hpp"

// Platform-specific headers
#ifdef __WIN32__
#define _WINSOCKAPI_ // Prevents automatic winsock.h inclusion.
#include <Windows.h>
#elif __linux__
	;
#elif __APPLE__
	;
#endif

// ================================================ //