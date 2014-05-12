// ================================================ //

#ifndef __STAGEEFFECT_HPP__
#define __STAGEEFFECT_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

struct StageLayer{
	SDL_Texture* pTexture;
	SDL_Rect src, dst;

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