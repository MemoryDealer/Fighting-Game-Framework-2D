// ================================================ //

#include "StageManager.hpp"

// ================================================ //

template<> StageManager* Singleton<StageManager>::msSingleton = 0;

// ================================================ //

StageManager::StageManager(void)
	: m_pStage(nullptr)
{

}

// ================================================ //

StageManager::~StageManager(void)
{

}

// ================================================ //

bool StageManager::load(const char* stageFile)
{
	m_pStage.reset(new Stage(stageFile));

	return (m_pStage.get() != nullptr);
}

// ================================================ //

void StageManager::update(double dt)
{
	return m_pStage->update(dt);
}

// ================================================ //
