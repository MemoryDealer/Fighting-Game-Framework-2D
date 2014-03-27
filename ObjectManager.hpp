// ================================================ //

#ifndef __OBJECTMANAGER_HPP__
#define __OBJECTMANAGER_HPP__

// ================================================ //

#include "stdafx.hpp"
#include "Object.hpp"

// ================================================ //

typedef std::list<Object*> ObjectList;

// ================================================ //

class ObjectManager
{
public:
	explicit ObjectManager(void);
	~ObjectManager(void);

	bool addObject(Object* pObject);

	void update(double dt);

private:
	ObjectList	m_objects;
};

// ================================================ //

#endif

// ================================================ //