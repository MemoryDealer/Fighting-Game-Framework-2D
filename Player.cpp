// ================================================ //

#include "Player.hpp"
#include "PlayerImpl.hpp"

// ================================================ //

Player::Player(unsigned int fighter)
	:	m_pImpl(new PlayerImpl(fighter))
{
	Object::setPImpl(m_pImpl);
}

// ================================================ //

Player::~Player(void)
{

}

// ================================================ //

void Player::loadFighterData(void)
{
	return m_pImpl->loadFighterData();
}

// ================================================ //
// Getter functions
// ================================================ //

// ================================================ //

void Player::update(double dt)
{
	return m_pImpl->update(dt);
}

// ================================================ //