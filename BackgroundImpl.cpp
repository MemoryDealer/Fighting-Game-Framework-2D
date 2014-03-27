// ================================================ //

#include "BackgroundImpl.hpp"
#include "Engine.hpp"

// ================================================ //

BackgroundImpl::BackgroundImpl(const char* textureFilename)
	:	ObjectImpl(textureFilename)
{
	if(m_pTexture){
		// set background to fill entire screen as default
		m_dst.w = Engine::getSingletonPtr()->getWindowWidth();
		m_dst.h = Engine::getSingletonPtr()->getWindowHeight();
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