// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
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