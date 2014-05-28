// ================================================ //

#ifndef __STAGE_HPP__
#define __STAGE_HPP__

// ================================================ //

#include "Object.hpp"

// ================================================ //

class StageImpl;

// ================================================ //

class Stage : public Object
{
public:
	explicit Stage(const std::string& stageFile);
	virtual ~Stage(void);

	virtual void update(double dt);

private:
	std::shared_ptr<StageImpl>	m_pImpl;
};

// ================================================ //

#endif

// ================================================ //