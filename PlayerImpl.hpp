// ================================================ //

#ifndef __PLAYERIMPL_HPP__
#define __PLAYERIMPL_HPP__

// ================================================ //

#include "ObjectImpl.hpp"

// ================================================ //

class PlayerImpl : public ObjectImpl
{
public:
	explicit PlayerImpl(unsigned int fighter);
	virtual ~PlayerImpl(void);

	void loadFighterData(void);
	void processInput(const int input);

	virtual void update(double dt);

private:
	unsigned int	m_fighter;
	int				m_xVel, m_yVel;
	int				m_maxXVel, m_maxYVel;
	int				m_currentXVel, m_currentYVel;
};

// ================================================ //

#endif

// ================================================ //