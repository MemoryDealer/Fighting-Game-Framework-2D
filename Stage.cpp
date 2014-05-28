// ================================================ //

#include "Stage.hpp"
#include "StageImpl.hpp"

// ================================================ //

Stage::Stage(const std::string& stageFile)
	:	m_pImpl(new StageImpl(stageFile))
{
	Object::setPImpl(m_pImpl);
}

// ================================================ //

Stage::~Stage(void)
{

}

// ================================================ //

const int Stage::getSourceX(const int layer) const
{
	return m_pImpl->getSourceX(layer);
}

// ================================================ //

void Stage::update(double dt)
{
	return m_pImpl->update(dt);
}

// ================================================ //