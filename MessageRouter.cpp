// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: MessageRouter.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements MessageRouter singleton class.
// ================================================ //

#include "MessageRouter.hpp"
#include "Object.hpp"
#include "Log.hpp"
#include "Engine.hpp"

// ================================================ //

template<> MessageRouter* Singleton<MessageRouter>::msSingleton = nullptr;

// ================================================ //

Message::Message(void) :
type(MessageType::TYPE_NOTHING),
senderID(0),
receiverID(0),
delay(0),
pData(nullptr)
{

}

// ================================================ //

Message::~Message(void)
{

}

// ================================================ //
// ================================================ //

MessageRouter::MessageRouter(void) :	
m_objects(),	
m_messages()
{

}

// ================================================ //

MessageRouter::~MessageRouter(void)
{

}

// ================================================ //

void MessageRouter::addObject(Object* pObject)
{
	m_objects.push_back(pObject);
}

// ================================================ //

void MessageRouter::removeObject(const int id)
{
	Log::getSingletonPtr()->logMessage("Removing object ID " + Engine::toString(id) + " from MessageRouter...");

	ObjectList::iterator itr;
	for(itr = m_objects.begin();
		itr != m_objects.end();
		++itr){

		// Remove empty pointers from list.
		if ((*itr) == nullptr){
			m_objects.erase(itr++);
		}
		// Remove the desired object.
		else if ((*itr)->getID() == id){
			m_objects.erase(itr++);
			return;
		}
	}
}

// ================================================ //

void MessageRouter::routeMessage(const int type, const int senderID, const int receiverID, const int delay, void* pData)
{
	Message msg;
	msg.type = type;
	msg.senderID = senderID;
	msg.receiverID = receiverID;
	msg.delay = delay;
	msg.pData = pData;

	this->routeMessage(msg);
}

// ================================================ //

void MessageRouter::routeMessage(Message msg)
{
	msg.delay = Engine::getSingletonPtr()->getTicks() + msg.delay;

	m_messages.push_back(msg);
}

// ================================================ //

void MessageRouter::update(void)
{
	MessageList::iterator msgItr;
	bool shouldIterate;

	for(msgItr = m_messages.begin(); msgItr != m_messages.end();){
		shouldIterate = true;

		// See if this message's receive ID is found in the list of objects.
		ObjectList::iterator objItr;
		for(objItr = m_objects.begin(); objItr != m_objects.end(); ++objItr){

			if ((*objItr)->getID() == msgItr->receiverID){

				// See if a delay should be applied.
				if (msgItr->delay < Engine::getSingletonPtr()->getTicks()){

					this->dispatchMessageToObject(*msgItr, *objItr);

					// Now delete this message from the message list.
					msgItr = m_messages.erase(msgItr);
					shouldIterate = false;
				}
			}
		}

		// We didn't find the object or there was still a delay, so move on to the next.
		if (shouldIterate){
			++msgItr;
			// TODO: handle object not found.
		}
	}
}

// ================================================ //

void MessageRouter::dispatchMessageToObject(Message msg, Object* pObject)
{
	Log::getSingletonPtr()->logMessage("Routing message type " + Engine::toString(msg.type) + 
						" from sender " + Engine::toString(msg.senderID) + " to receiver " + Engine::toString(msg.receiverID));

	pObject->sendMessage(msg);
}

// ================================================ //
