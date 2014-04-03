// ================================================ //

#ifndef __PLAYERIMPL_HPP__
#define __PLAYERIMPL_HPP__

// ================================================ //

#include "ObjectImpl.hpp"
#include "PlayerData.hpp"
#include "Animation.hpp"
#include "Config.hpp"
#include "Timer.hpp"

// ================================================ //

typedef std::vector<Animation*> AnimationList;

// ================================================ //

class PlayerImpl : public ObjectImpl
{
public:
	explicit PlayerImpl(unsigned int fighter);
	virtual ~PlayerImpl(void);

	void loadFighterData(void);
	void loadAnimations(Config& c);
	void processInput(const int input);
	void updateAnimation(double dt);

	// Getter functions
	const int getSide(void) const;

	// Setter functions
	void setSide(const int side);

	virtual void update(double dt);

private:
	int		m_fighter;
	int		m_xAccel, m_yAccel;
	int		m_xVel, m_yVel;
	int		m_xMax, m_yMax;
	int		m_currentAction;
	int		m_playerSide;

	AnimationList	m_animations;
	Animation*		m_pCurrentAnimation;
	Timer			m_animationTimer;
};

// ================================================ //

// Getter functions
inline const int PlayerImpl::getSide(void) const
{ return m_playerSide; }

// Setter functions

inline void PlayerImpl::setSide(const int side)
{ 
	m_playerSide = side; 
	m_flip = (side == PlayerSide::LEFT) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL; 
}

// ================================================ //

#endif

// ================================================ //