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