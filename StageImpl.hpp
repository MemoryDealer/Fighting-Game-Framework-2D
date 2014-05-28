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

	// Getter functions
	const int getSourceX(const int layer) const;

	virtual void update(double dt);

private:
	StageLayerList m_layers;
};

// ================================================ //

inline const int StageImpl::getSourceX(const int layer) const{
	return m_layers[layer].src.x;
}

// ================================================ //

#endif

// ================================================ //