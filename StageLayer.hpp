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
// File: StageEffect.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines StageLayer struct, and Effect struct inside it.
// ================================================ //

#ifndef __STAGELAYER_HPP__
#define __STAGELAYER_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

// A layer that is rendered in a Stage. Can be the background,
// scrolling translucent fog, etc.
struct StageLayer{
	SDL_Texture* pTexture;
	SDL_Rect src, dst;
	int w, h;

	// An effect that can be applied to a Layer.
	struct{
		int scrollX, scrollY;
		int alpha;
	} Effect;
};

// ================================================ //

typedef std::vector<StageLayer> StageLayerList;

// ================================================ //

#endif

// ================================================ //