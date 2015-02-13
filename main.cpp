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
// File: main.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Entry point of program.
// ================================================ //

#include "stdafx.hpp"
#include "App.hpp"

// ================================================ //

#ifdef __cplusplus
	extern "C" {
#endif

// ================================================ //

/* To update from repo:
* git fetch --all
* git reset --hard origin/master
*/

// ================================================ //

int SDL_main(int argc, char** argv)
{
	try{
		// Initialize application and run.
		App app;
	} 
	catch(std::exception& e){
#ifdef __WIN32__
		MessageBoxA(GetForegroundWindow(), e.what(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
		std::cerr << "An exception has occured: " << e.what() << std::endl;
#endif
	}

	return 0;
}

// ================================================ //

#ifdef __cplusplus
}
#endif

// ================================================ //