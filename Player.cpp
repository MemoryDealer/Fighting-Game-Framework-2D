// ================================================ //

#include "Player.hpp"
#include "PlayerImpl.hpp"
#include "Hitbox.hpp"

// ================================================ //

Player::Player(const std::string& fighterFile, const int inputType)
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

const int Player::getCurrentState(void) const
{
	return m_pImpl->getCurrentState();
}

// ================================================ //

const bool Player::isColliding(void) const
{
	return m_pImpl->isColliding();
}

// ================================================ //

const int Player::getVelocityX(void) const
{
	return m_pImpl->getVelocityX();
}

// ================================================ //

const int Player::getVelocityY(void) const
{
	return m_pImpl->getVelocityY();
}

// ================================================ //

Input* Player::getInput(void) const
{
	return m_pImpl->getInput();
}

// ================================================ //
// Setter functions
// ================================================ //

void Player::setSide(const int side)
{
	return m_pImpl->setSide(side);
}

// ================================================ //

void Player::setColliding(const bool colliding)
{
	return m_pImpl->setColliding(colliding);
}

// ================================================ //

void Player::toggleDrawHitboxes(void)
{
	return m_pImpl->toggleDrawHitboxes();
}

// ================================================ //
// ================================================ //

void Player::update(double dt)
{
	return m_pImpl->update(dt);
}

// ================================================ //