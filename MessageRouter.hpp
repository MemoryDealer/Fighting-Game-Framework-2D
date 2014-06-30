// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: MessageRouter.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines MessageRouter singleton class.
// ================================================ //

#ifndef __MESSAGEROUTER_HPP__
#define __MESSAGEROUTER_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

class Object;

// ================================================ //

namespace MessageType{
	enum{
		TYPE_NOTHING = 0,
		TYPE_ACTIVATE
	};
}

// Can be sent to and received by an Object.
typedef struct Message{
	// Initializes type to TYPE_NOTHING and sets delay to zero.
	explicit Message(void);

	// Empty destructor.
	~Message(void);

	int type;
	int senderID;
	int receiverID;
	// Time to wait until the message is sent (ms).
	Uint32 delay;
	void* pData;
} Message;

typedef std::vector<Object*> ObjectList;
typedef std::list<Message> MessageList;

// ================================================ //

// Holds a list of all active Objects in the game (Object's constructor 
// automatically adds itself to the MessageRouter).
class MessageRouter : public Singleton<MessageRouter>
{
public:
	// Empty constructor.
	explicit MessageRouter(void);

	// Empty destructor.
	~MessageRouter(void);

	// Adds pObject to router's internal list.
	void addObject(Object* pObject);

	// Removes Object with the specified ID from the router's internal list.
	void removeObject(const int id);

	// Allocates a Message and sends it to routeMessage(Message msg).
	void routeMessage(const int type, const int senderID, 
		const int receiverID, const int delay = 0, void* pData = nullptr);

	// Sets up the delay using the ticks from the Engine and adds the message
	// to the dispatch list.
	void routeMessage(Message msg);

	// Iterates through list of messages to dispatch and tests if each is ready
	// to dispatch, if so the message is sent to the Object.
	void update(void);

	// Logs the action and calls Object::sendMessage().
	void dispatchMessageToObject(const Message msg, Object* pObject);

private:
	ObjectList m_objects;
	MessageList m_messages;
};

// ================================================ //

#endif

// ================================================ //