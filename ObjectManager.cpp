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
// File: ObjectManager.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements ObjectManager class.
// ================================================ //

#include "ObjectManager.hpp"
#include "Engine.hpp"
#include "MessageRouter.hpp"
#include "Object.hpp"

// ================================================ //

ObjectManager::ObjectManager(void)
{

}

// ================================================ //

ObjectManager::~ObjectManager(void)
{
	for(ObjectList::iterator itr = m_objects.begin();
		itr != m_objects.end();
		++itr){
		delete *itr;
	}
}

// ================================================ //

Object* ObjectManager::addObject(Object* pObject)
{
	m_objects.push_back(pObject);
	
	return pObject;
}

// ================================================ //

Object* ObjectManager::getObject(const int index)
{
	if (static_cast<size_t>(index) < m_objects.size()){
		return m_objects[index];
	}

	return nullptr;
}

// ================================================ //

void ObjectManager::update(double dt, bool render)
{
	for(ObjectList::iterator itr = m_objects.begin();
		itr != m_objects.end();
		++itr){

		if ((*itr)->isDead()){
			delete *itr;
			m_objects.erase(itr++);
		}
		else{
			(*itr)->update(dt);

			if (render)
				(*itr)->render();
		}
	}
}

// ================================================ //