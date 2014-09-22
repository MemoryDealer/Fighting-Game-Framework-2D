// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: StageManager.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines StageManager singleton class.
// ================================================ //

#ifndef __STAGEMANAGER_HPP__
#define __STAGEMANAGER_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

class Stage;

// ================================================ //

// Holds a Stage object so it can be accessed in between game states.
class StageManager : public Singleton<StageManager>
{
public:
	// Empty constructor.
	explicit StageManager(void);

	// Empty destructor.
	~StageManager(void);

	// Allocates Stage object with stageFile, returns true if successful.
	bool load(const std::string& stageFile);

	// Calls load() with last used stageFile.
	bool reload(void);

	// Getters

	// Returns pointer to currently loaded stage.
	Stage* getStage(void) const;

	// Calls Stage::update().
	void update(double dt);

private:
	std::shared_ptr<Stage> m_pStage;
	std::string m_stageFile;
};

// ================================================ //

// Getters

inline Stage* StageManager::getStage(void) const{
	return (m_pStage == nullptr) ? nullptr : m_pStage.get();
}

// ================================================ //

#endif

// ================================================ //
