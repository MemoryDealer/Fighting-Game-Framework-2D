// ================================================ //

#include "StageManager.hpp"

// ================================================ //

template<> StageManager* Singleton<StageManager>::msSingleton = 0;

// ================================================ //

StageManager::StageManager(void)
	:	m_pStage(nullptr),
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
	// Store stage file for reloading
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
