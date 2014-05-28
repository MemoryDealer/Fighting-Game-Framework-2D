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

	// Getter functions
	const int getMoveX(void) const;
	const int getMoveY(void) const;
	const bool isLocked(void) const;

	// Setter functions
	void setMoveX(const int x);
	void setMoveY(const int y);
	void clear(void);
	void lock(void);
	void unlock(void);

private:
	int m_moveX, m_moveY;
	bool m_locked;
};

// ================================================ //

inline const int Camera::getMoveX(void) const{
	return m_moveX;
}

inline const int Camera::getMoveY(void) const{
	return m_moveY;
}

inline const bool Camera::isLocked(void) const{
	return m_locked;
}

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