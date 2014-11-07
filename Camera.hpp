// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
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

// ================================================ //

