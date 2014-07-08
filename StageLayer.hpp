// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
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