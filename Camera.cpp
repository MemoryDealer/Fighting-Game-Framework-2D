// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: Camera.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements Camera singleton class.
// ================================================ //

#include "Camera.hpp"

// ================================================ //

template<> Camera* Singleton<Camera>::msSingleton = nullptr;

// ================================================ //

Camera::Camera(void) :	
m_moveX(0),
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