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

	virtual void update(double dt);

private:
	unsigned int	m_fighter;
};

// ================================================ //

#endif

// ================================================ //