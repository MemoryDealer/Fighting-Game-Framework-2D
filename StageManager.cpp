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
// File: StageManager.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements StageManager singleton class.
// ================================================ //

#include "StageManager.hpp"
#include "Stage.hpp"
#include "PlayerManager.hpp"

// ================================================ //

template<> StageManager* Singleton<StageManager>::msSingleton = nullptr;

// ================================================ //

StageManager::StageManager(void) :
m_pStage(nullptr),
m_stageFile()
{

}

// ================================================ //

StageManager::~StageManager(void)
{

}

// ================================================ //

bool StageManager::load(const std::string& stageFile)
{
	// Store stage file for reloading.
	m_stageFile.assign(stageFile);

	m_pStage.reset(new Stage(stageFile));

	return (m_pStage.get() != nullptr);
}

// ================================================ //

bool StageManager::reload(void)
{
	return this->load(m_stageFile);
}

// ================================================ //

void StageManager::update(double dt)
{
	return m_pStage->update(dt);
}

// ================================================ //
