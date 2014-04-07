// ================================================ //

#include "MessageRouter.hpp"
#include "Log.hpp"
#include "Engine.hpp"

// ================================================ //

template<> MessageRouter* Singleton<MessageRouter>::msSingleton = 0;

// ================================================ //

MessageRouter::MessageRouter(void)
	:	m_objects(),
		m_messages()
{

}

// ================================================ //

MessageRouter::~MessageRouter(void)
{
	m_objects.clear();
	m_messages.clear();
}

// ================================================ //

void MessageRouter::removeObject(const int id)
{
	ObjectList::iterator itr;
	for(itr = m_objects.begin();
		itr != m_objects.end();
		++itr){

		// Remove pointer from list
		if((*itr) == nullptr){
			itr = m_objects.erase(itr);
		}
		else if((*itr)->getID() == id){
			itr = m_objects.erase(itr);
			return;
		}
	}
}

// ================================================ //

void MessageRouter::routeMessage(const Message::Type type, const int senderID, const int receiverID, const int delay, void* pData)
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

	// Loop through each message in the list
	for(msgItr = m_messages.begin(); msgItr != m_messages.end(); ++msgItr){
		ObjectList::iterator objItr;

		// Test the message ID against each object in the router's list
		for(objItr = m_objects.begin();
			objItr != m_objects.end();
			++objItr){
			Assert(static_cast<int>((*objItr) == nullptr), "nullptr in MessageRouter ObjectList");

			// Does this object match the message receiver ID?
			if((*objItr)->getID() == msgItr->receiverID){

				// Proceed if there is no further delay
				if(msgItr->delay < Engine::getSingletonPtr()->getTicks()){
					Log::getSingletonPtr()->logMessage("Routing message type " + Engine::toString(msgItr->type) + 
						" from sender " + Engine::toString(m_messages.front().senderID) + " to receiver " + Engine::toString(m_messages.front().receiverID));
					(*objItr)->sendMessage(*msgItr);
				
					// Remove this message from the list
					msgItr = m_messages.erase(msgItr);
				}
			}
		}
	}
}

// ================================================ //
