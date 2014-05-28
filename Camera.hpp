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

	const bool isLocked(void) const;

	void clear(void);
	void lock(void);
	void unlock(void);

	int moveX, moveY;

private:
	bool m_locked;
};

// ================================================ //

inline const bool Camera::isLocked(void) const{
	return m_locked;
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