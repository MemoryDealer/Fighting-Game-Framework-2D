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
// File: Camera.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines Camera class.
// ================================================ //

#include "stdafx.hpp"

// ================================================ //
// Logically represents a Camera in the 2D world.
class Camera : public Singleton<Camera>
{
public:
	// Initializes member variables to zero and loads Camera speed.
	explicit Camera(void);

	// Empty destructor.
	~Camera(void);

	// Returns current x-value of camera position.
	const int getX(void) const;

	// Returns current y-value of camera position.
	const int getY(void) const;

	// Returns destination x-value for panning.
	const int getPanX(void) const;

	// Returns destination y-value for panning.
	const int getPanY(void) const;

	// Returns last x-value of Camera before being panned.
	const int getLastX(void) const;

	// Returne true if Camera is not at either edge of stage.
	const bool isBetweenBounds(void) const;

	// Sets the right edge at which camera.x + camera.w can be at.
	void setRightBound(const int bound);

	// Sets the Camera's panX position, the Camera will pan to it each frame.
	void panX(const int x);

	// Sets the Camera's panY position, the Camera will pan to it each frame.
	void panY(const int y);	

	// Pans the camera if it has not reach the pan destination.
	void update(double dt);

private:
	int m_x, m_y;
	int m_panX, m_panY;
	int m_speed;
	int m_rightBound;
	int m_lastX;
};

// ================================================ //

inline const int Camera::getX(void) const{
	return m_x;
}

inline const int Camera::getY(void) const{
	return m_y;
}

inline const int Camera::getPanX(void) const{
	return m_panX;
}

inline const int Camera::getPanY(void) const{
	return m_panY;
}

inline const int Camera::getLastX(void) const{
	return m_lastX;
}

inline const bool Camera::isBetweenBounds(void) const{
	return (m_panX > 0 && m_panX < m_rightBound);
}

inline void Camera::setRightBound(const int bound){
	m_rightBound = bound;
}

// ================================================ //

