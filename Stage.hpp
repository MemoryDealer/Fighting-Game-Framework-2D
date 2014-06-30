// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: Stage.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines Stage class.
// ================================================ //

#ifndef __STAGE_HPP__
#define __STAGE_HPP__

// ================================================ //

#include "Object.hpp"
#include "StageLayer.hpp"

// ================================================ //

// The level in which the fighters play on; it is simply a background.
class Stage : public Object
{
public:
	// Loads the .stage file and parses each layer.
	explicit Stage(const std::string& stageFile);

	// Frees any textures allocated by the Stage.
	virtual ~Stage(void);

	// Getters

	// Returns the x value of the specified Layer's source SDL_Rect.
	const int getSourceX(const int layer) const;

	// Renders each layer, applying proper offsets using the Camera values.
	// Process Stage effects.
	virtual void update(double dt);

private:
	StageLayerList m_layers;
};

// ================================================ //

// Getters

inline const int Stage::getSourceX(const int layer) const{
	return m_layers[layer].src.x;
}

// ================================================ //

#endif

// ================================================ //