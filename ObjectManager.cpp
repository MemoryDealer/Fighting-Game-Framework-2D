// ================================================ //

#include "ObjectManager.hpp"
#include "Engine.hpp"

// ================================================ //

ObjectManager::ObjectManager(void)
{

}

// ================================================ //

ObjectManager::~ObjectManager(void)
{
	// Clear all objects
	for(ObjectList::iterator itr = m_objects.begin();
		itr != m_objects.end();
		++itr){
		delete *itr;
	}

	m_objects.clear();
}

// ================================================ //

bool ObjectManager::addObject(Object* pObject)
{
	m_objects.push_back(pObject);

	return true;
}

// ================================================ //

Object* ObjectManager::getObject(const int index)
{
	if(static_cast<size_t>(index) < m_objects.size()){
		return m_objects[index];
	}

	return nullptr;
}

// ================================================ //

void ObjectManager::update(double dt, bool render)
{
	// Update all objects in list
	for(ObjectList::iterator itr = m_objects.begin();
		itr != m_objects.end();
		++itr){
		(*itr)->update(dt);

		if(render)
			(*itr)->render();
	}
}

// ================================================ //