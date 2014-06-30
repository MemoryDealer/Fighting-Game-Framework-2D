// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: ObjectManager.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines ObjectManager class.
// ================================================ //

#ifndef __OBJECTMANAGER_HPP__
#define __OBJECTMANAGER_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

class Object;

// ================================================ //

typedef std::vector<Object*> ObjectList;

// ================================================ //

// Holds a list of Objects and updates all of them.
class ObjectManager
{
public:
	// Empty constructor.
	explicit ObjectManager(void);

	// Frees all Objects in the internal list.
	~ObjectManager(void);

	// Adds Object to internal list and returns the pointer.
	Object* addObject(Object* pObject);

	// Returns a pointer to the Object at the specified index.
	Object* getObject(const int index);

	// Iterates through all Objects in the internal list and updates them,
	// deletes them if they are dead, and renders them if render is true.
	void update(double dt, bool render = true);

private:
	ObjectList	m_objects;
};

// ================================================ //

#endif

// ================================================ //