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

	// --- //

	typedef struct{
		int shift;
		Uint32 lastProcessedShift;
	} ShiftUpdate;

	// Loads the .stage file and parses each layer.
	explicit Stage(const std::string& stageFile);

	// Frees any textures allocated by the Stage.
	virtual ~Stage(void);

	// Shifts the stage view left or right by amount x.
	void shift(const int x);

	// Directly sets the shift offset of the stage view.
	void setShift(const int x);

	// Enqueues a shift update received from the server for server 
	// reconciliation processing.
	void updateShiftFromServer(const Stage::ShiftUpdate& update);

	// Rewinds stage shift to last server update and replays unprocessed shifts.
	void serverReconciliation(void);

	// Renders each layer, applying proper offsets using the Camera values.
	// Process Stage effects.
	virtual void update(double dt);

	// Getters

	// Returns the x value of the specified Layer's source SDL_Rect.
	const int getShift(const int layer = 0) const;

	// Returns farmost right edge at which the stage can be shifted.
	const int getRightEdge(void) const;

public:
	StageLayerList m_layers;
	int m_rightEdge;
	std::queue<ShiftUpdate> m_shiftUpdates;
};

// ================================================ //

// Getters

inline const int Stage::getShift(const int layer) const{
	return m_layers[layer].src.x;
}

inline const int Stage::getRightEdge(void) const{
	return m_rightEdge;
}

// ================================================ //

#endif

// ================================================ //