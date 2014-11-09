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
#include "Stage.hpp"
#include "StageManager.hpp"

// ================================================ //

template<> Camera* Singleton<Camera>::msSingleton = nullptr;

// ================================================ //

Camera::Camera(void) :
m_x(0),
m_y(0),
m_panX(0),
m_panY(0),
m_speed(0),
m_rightBound(343),
m_lastX(0)
{
	Config e(Engine::getSingletonPtr()->getSettingsFile());
	m_speed = e.parseIntValue("camera", "speed");
}

// ================================================ //

Camera::~Camera(void)
{

}

// ================================================ //

void Camera::panX(const int x)
{
	m_lastX = m_x;

	m_panX = x;
	if (m_panX < 0){
		m_panX = 0;
	}
	else if (m_panX > m_rightBound){
		m_panX = m_rightBound;
	}
}

// ================================================ //

void Camera::panY(const int y)
{
	m_panY = y;
	
}

// ================================================ //

void Camera::update(double dt)
{
	const int snapRange = 5;

	// Pan to x-position.
	if (m_x < m_panX){
		m_x += static_cast<int>(m_speed * dt);
		if (m_x > (m_panX - snapRange)){
			m_x = m_panX;
		}
	}
	else if (m_x > m_panX){
		m_x -= static_cast<int>(m_speed * dt);
		if (m_x < (m_panX + snapRange)){
			m_x = m_panX;
		}
	}

	// Pan to y-position.
	if (m_y < m_panY){
		m_y += static_cast<int>(m_speed * dt);
		if (m_y > (m_panY - snapRange)){
			m_y = m_panY;
		}
	}
	else if (m_y > m_panY){
		m_y -= static_cast<int>(m_speed * dt);
		if (m_y < (m_panY + snapRange)){
			m_y = m_panY;
		}
	}
}

// ================================================ //

