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

	bool load(const char* stageFile);

	void update(double dt);

private:
	std::tr1::shared_ptr<Stage> m_pStage;
};

// ================================================ //

#endif

// ================================================ //
