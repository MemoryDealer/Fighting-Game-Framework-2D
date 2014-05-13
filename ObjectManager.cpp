// ================================================ //

#include "ObjectManager.hpp"
#include "Engine.hpp"
#include "MessageRouter.hpp"

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

Object* ObjectManager::addObject(Object* pObject)
{
	m_objects.push_back(pObject);
	
	return pObject;
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

		if((*itr)->isDead()){
			delete *itr;
			m_objects.erase(itr++);
			printf("ERASED OBJECT\n");
		}
		else{
			(*itr)->update(dt);

			if(render)
				(*itr)->render();
		}
	}
}

// ================================================ //