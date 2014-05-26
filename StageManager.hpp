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

	void update(double dt);

private:
	std::tr1::shared_ptr<Stage> m_pStage;
	std::string m_stageFile;
};

// ================================================ //

#endif

// ================================================ //
