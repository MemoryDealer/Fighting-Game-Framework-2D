// ================================================ //

#include "Player.hpp"
#include "PlayerImpl.hpp"

// ================================================ //

Player::Player(const char* fighterFile, const int inputType)
	:	m_pImpl(new PlayerImpl(fighterFile, inputType))
{
	Object::setPImpl(m_pImpl);
}

// ================================================ //

Player::~Player(void)
{

}

// ================================================ //
// Getter functions
// ================================================ //

const int Player::getSide(void) const
{
	return m_pImpl->getSide();
}

// ================================================ //

Hitbox& Player::getHitbox(const int index)
{
	return m_pImpl->getHitbox(index);
}

// ================================================ //
// Setter functions
// ================================================ //

void Player::setSide(const int side)
{
	return m_pImpl->setSide(side);
}

// ================================================ //

void Player::setInput(const int input, const bool down)
{
	return m_pImpl->setInput(input, down);
}

// ================================================ //

void Player::setColliding(const bool colliding)
{
	return m_pImpl->setColliding(colliding);
}

// ================================================ //

void Player::update(double dt)
{
	return m_pImpl->update(dt);
}

// ================================================ //