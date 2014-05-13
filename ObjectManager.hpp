// ================================================ //

#ifndef __OBJECTMANAGER_HPP__
#define __OBJECTMANAGER_HPP__

// ================================================ //

#include "stdafx.hpp"
#include "Object.hpp"

// ================================================ //

typedef std::vector<Object*> ObjectList;

// ================================================ //

class ObjectManager
{
public:
	explicit ObjectManager(void);
	~ObjectManager(void);

	Object* addObject(Object* pObject);

	Object* getObject(const int index);

	void update(double dt, bool render = true);

private:
	ObjectList	m_objects;
};

// ================================================ //

#endif

// ================================================ //