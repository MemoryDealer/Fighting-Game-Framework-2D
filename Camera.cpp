// ================================================ //

#include "Camera.hpp"

// ================================================ //

template<> Camera* Singleton<Camera>::msSingleton = nullptr;

// ================================================ //

Camera::Camera(void)
	:	m_moveX(0),
		m_moveY(0),
		m_locked(false)
{
	
}

// ================================================ //

Camera::~Camera(void)
{

}

// ================================================ //

void Camera::clear(void)
{
	m_moveX = m_moveY = 0;
}

// ================================================ //