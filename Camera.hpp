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

class Camera : public Singleton<Camera>
{
public:
	explicit Camera(void);
	~Camera(void);

	const int getX(void) const;
	const int getY(void) const;

	void setX(const int x);

	void update(double dt);

private:
	int m_x, m_y;
	int m_panX, m_panY;
	int m_speed;
};

// ================================================ //

inline const int Camera::getX(void) const{
	return m_x;
}

inline const int Camera::getY(void) const{
	return m_y;
}

// ================================================ //

