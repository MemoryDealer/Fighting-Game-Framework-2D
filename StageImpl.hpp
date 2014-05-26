// ================================================ //

#ifndef __STAGE_IMPL_HPP__
#define __STAGE_IMPL_HPP__

// ================================================ //

#include "ObjectImpl.hpp"
#include "StageEffect.hpp"

// ================================================ //

class StageImpl : public ObjectImpl
{
public:
	explicit StageImpl(const std::string& stageFile);
	virtual ~StageImpl(void);

	virtual void update(double dt);

private:
	StageLayerList m_layers;
	int m_stageWidth, m_stageHeight;
};

// ================================================ //

#endif

// ================================================ //