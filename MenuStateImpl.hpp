// ================================================ //

#ifndef __MENUSTATEIMPL_HPP__
#define __MENUSTATEIMPL_HPP__

// ================================================ //

#include "stdafx.hpp"
#include "Object.hpp"

// ================================================ //

class MenuStateImpl
{
public:
	explicit MenuStateImpl(void);
	~MenuStateImpl(void);

	void enter(void);
	void exit(void);
	bool pause(void);
	void resume(void);
	void update(double dt);

	const bool shouldQuit(void) const;

private:
	bool m_bQuit;

	Object*	m_pObject;
	Object* m_pBackground;
};

// ================================================ //

inline const bool MenuStateImpl::shouldQuit(void) const
{ return m_bQuit; }

// ================================================ //

#endif

// ================================================ //