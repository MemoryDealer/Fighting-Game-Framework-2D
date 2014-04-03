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

void Player::processInput(const int input)
{
	return m_pImpl->processInput(input);
}

// ================================================ //
// Getter functions
// ================================================ //

const int Player::getSide(void) const
{
	return m_pImpl->getSide();
}

// ================================================ //
// Setter functions
// ================================================ //

void Player::setSide(const int side)
{
	return m_pImpl->setSide(side);
}

// ================================================ //

void Player::update(double dt)
{
	return m_pImpl->update(dt);
}

// ================================================ //