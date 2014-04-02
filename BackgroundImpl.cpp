// ================================================ //

#include "BackgroundImpl.hpp"
#include "Engine.hpp"

// ================================================ //

BackgroundImpl::BackgroundImpl(unsigned int type)
	:	ObjectImpl(type)
{
	switch(type){
	default:
		
		break;

	case 0:
		break;
	}
}

// ================================================ //

BackgroundImpl::~BackgroundImpl(void)
{

}

// ================================================ //

bool BackgroundImpl::setTextureFile(const char* filename)
{
	ObjectImpl::setTextureFile(filename);

	if(m_pTexture){
		// set background to fill entire screen as default
		m_dst.w = Engine::getSingletonPtr()->getWindowWidth();
		m_dst.h = Engine::getSingletonPtr()->getWindowHeight();

		return true;
	}

	return false;
}

// ================================================ //

void BackgroundImpl::update(double dt)
{

}

// ================================================ //