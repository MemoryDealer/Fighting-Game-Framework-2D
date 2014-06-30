// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: StageManager.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements StageManager singleton class.
// ================================================ //

#include "StageManager.hpp"
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
