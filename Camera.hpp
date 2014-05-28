// ================================================ //

#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

class Camera : public Singleton<Camera>
{
public:
	Camera(void);
	~Camera(void);

	void clear(void);

	int moveX, moveY;

private:

};

// ================================================ //

#endif

// ================================================ //