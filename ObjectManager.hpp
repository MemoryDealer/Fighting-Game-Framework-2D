// ========================================================================= //
// Fighting game framework (2D) with online multiplayer.
// Copyright(C) 2014 Jordan Sparks <unixunited@live.com>
//
// This program is free software; you can redistribute it and / or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 3
// of the License, or(at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
// ========================================================================= //
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