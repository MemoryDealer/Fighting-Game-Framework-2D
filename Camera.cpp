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
// Defines Camera class.
// ================================================ //

#include "Camera.hpp"

// ================================================ //

template<> Camera* Singleton<Camera>::msSingleton = nullptr;

// ================================================ //

Camera::Camera(void) :
m_x(0),
m_y(0)
{

}

// ================================================ //

Camera::~Camera(void)
{

}

// ================================================ //

void Camera::setX(const int x){
	m_x = x;
	if (m_x < 0){
		m_x = 0;
	}
	else if (m_x > 343){
		m_x = 343;
	}
}

// ================================================ //

