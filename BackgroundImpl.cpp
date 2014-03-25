// ================================================ //

#include "BackgroundImpl.hpp"
#include "Engine.hpp"

// ================================================ //

BackgroundImpl::BackgroundImpl(const char* textureFilename)
	:	ObjectImpl(textureFilename)
{
	if(m_pTexture){
		// set background to fill entire screen as default
		m_pos.w = Engine::getSingletonPtr()->getWindowWidth();
		m_pos.h = Engine::getSingletonPtr()->getWindowHeight();
	}
}

// ================================================ //

BackgroundImpl::~BackgroundImpl(void)
{

}

// ================================================ //

void BackgroundImpl::update(double dt)
{

}

// ================================================ //