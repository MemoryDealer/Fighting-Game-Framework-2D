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
// Defines the Camera singleton class.
// ================================================ //

#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

// The Camera is a component to simulate camera movement in a stage. 
// It is accessed from both Stage objects and the PlayerManager. It simply
// holds offset values for the X and Y axes, and a locked boolean.
class Camera : public Singleton<Camera>
{
public:
	// Initializes X and Y values to zero, locked to false.
	Camera(void);

	// Empty destructor.
	~Camera(void);

	// Getters

	const int getMoveX(void) const;
	const int getMoveY(void) const;
	const bool isLocked(void) const;

	// Setters

	void setMoveX(const int x);
	void setMoveY(const int y);

	// Sets X and Y values to zero.
	void clear(void);

	// Sets m_locked to true.
	void lock(void);

	// Sets m_locked to false.
	void unlock(void);

private:
	// Offsets for the Stage to apply during rendering.
	int m_moveX, m_moveY;

	// The Camera should become locked when either both players are at the edges 
	// of the viewport, or when one player is at the edge of the stage.
	bool m_locked;
};

// ================================================ //

// Getters

inline const int Camera::getMoveX(void) const{
	return m_moveX;
}

inline const int Camera::getMoveY(void) const{
	return m_moveY;
}

inline const bool Camera::isLocked(void) const{
	return m_locked;
}

// Setters

inline void Camera::setMoveX(const int x){
	m_moveX = x;
}

inline void Camera::setMoveY(const int y){
	m_moveY = y;
}

inline void Camera::lock(void){
	m_locked = true;
}

inline void Camera::unlock(void){
	m_locked = false;
}

// ================================================ //

#endif

// ================================================ //