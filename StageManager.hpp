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
