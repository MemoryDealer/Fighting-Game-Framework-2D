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
#include "Config.hpp"
#include "Engine.hpp"

// ================================================ //

template<> Camera* Singleton<Camera>::msSingleton = nullptr;

// ================================================ //

Camera::Camera(void) :
m_x(0),
m_y(0),
m_panX(0),
m_panY(0),
m_speed(0)
{
	Config e(Engine::getSingletonPtr()->getSettingsFile());
	m_speed = e.parseIntValue("camera", "speed");
}

// ================================================ //

Camera::~Camera(void)
{

}

// ================================================ //

void Camera::setX(const int x){
	m_panX = x;
	if (m_panX < 0){
		m_panX = 0;
	}
	else if (m_panX > 343){
		m_panX = 343;
	}
}

// ================================================ //

void Camera::update(double dt)
{
	printf("X: %d\tPanX: %d\n", m_x, m_panX);

	const int snapRange = 5;

	if (m_x < m_panX){
		m_x += static_cast<int>(m_speed * dt);
		if (m_x >(m_panX - snapRange)){
			m_x = m_panX;
		}
	}
	else if (m_x > m_panX){
		m_x -= static_cast<int>(m_speed * dt);
		if (m_x < (m_panX + snapRange)){
			m_x = m_panX;
		}
	}
}

// ================================================ //

