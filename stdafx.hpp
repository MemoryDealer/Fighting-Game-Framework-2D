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
#include <cmath>

// SDL
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

// RakNet
#include <RakPeerInterface.h>
#include <MessageIdentifiers.h>
#include <RakNetTypes.h>
#include <BitStream.h>
#include <GetTime.h>

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