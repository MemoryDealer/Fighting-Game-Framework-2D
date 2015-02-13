// ========================================================================= //
// Fighting game framework (2D) with online multiplayer.
// Copyright(C) 2014 Jordan Sparks <unixunited@live.com>
//
// This program is free software; you can redistribute it and / or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 3
// of the License, or(at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
// ========================================================================= //
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
	const int snapRange = 1;

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

