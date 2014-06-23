// ================================================ //

#ifndef __STAGE_HPP__
#define __STAGE_HPP__

// ================================================ //

#include "Object.hpp"
#include "StageEffect.hpp"

// ================================================ //

class Stage : public Object
{
public:
	explicit Stage(const std::string& stageFile);
	virtual ~Stage(void);

	// Getter functions
	const int getSourceX(const int layer) const;

	virtual void update(double dt);

private:
	StageLayerList m_layers;
};

// ================================================ //

inline const int Stage::getSourceX(const int layer) const{
	return m_layers[layer].src.x;
}

// ================================================ //

#endif

// ================================================ //