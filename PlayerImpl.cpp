// ================================================ //

#include "PlayerImpl.hpp"

// ================================================ //

PlayerImpl::PlayerImpl(const char* textureFilename)
	:	ObjectImpl(textureFilename)
{
	
}

// ================================================ //

PlayerImpl::~PlayerImpl(void)
{

}

// ================================================ //

void PlayerImpl::update(double dt)
{
	m_pos.x += static_cast<int>(125.0 * dt);
	printf("Updating from player...\n");
	printf("dt: %.2f\n", dt); // testing...
}

// ================================================ //