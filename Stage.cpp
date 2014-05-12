// ================================================ //

#include "Stage.hpp"
#include "StageImpl.hpp"

// ================================================ //

Stage::Stage(const char* stageFile)
	:	m_pImpl(new StageImpl(stageFile))
{
	Object::setPImpl(m_pImpl);
}

// ================================================ //

Stage::~Stage(void)
{

}

// ================================================ //

void Stage::update(double dt)
{
	return m_pImpl->update(dt);
}

// ================================================ //