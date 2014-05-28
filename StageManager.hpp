// ================================================ //

#ifndef __STAGEMANAGER_HPP__
#define __STAGEMANAGER_HPP__

// ================================================ //

#include "stdafx.hpp"
#include "Stage.hpp"

// ================================================ //

class StageManager : public Singleton<StageManager>
{
public:
	explicit StageManager(void);
	~StageManager(void);

	bool load(const std::string& stageFile);
	bool reload(void);

	// Getter functions
	const int getSourceX(const int layer = 0) const;

	void update(double dt);

private:
	std::shared_ptr<Stage> m_pStage;
	std::string m_stageFile;
};

// ================================================ //

inline const int StageManager::getSourceX(const int layer) const{
	return m_pStage->getSourceX(layer);
}

// ================================================ //

#endif

// ================================================ //
