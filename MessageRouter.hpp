// ================================================ //

#ifndef __MESSAGEROUTER_HPP__
#define __MESSAGEROUTER_HPP__

// ================================================ //

#include "stdafx.hpp"
#include "Object.hpp"

// ================================================ //

typedef struct Message{
	enum Type{
		TYPE_ACTIVATE = 0,

		TYPE_END__
	};

	Type type;
	int senderID;
	int receiverID;
	Uint32 delay;
	void* pData;
} Message;

typedef std::vector<Object*> ObjectList;
typedef std::list<Message> MessageList;

// ================================================ //

class MessageRouter : public Singleton<MessageRouter>
{
public:
	explicit MessageRouter(void);
	~MessageRouter(void);

	void addObject(Object* pObject);
	void removeObject(const int id);
	void routeMessage(const Message::Type type, const int senderID, 
		const int receiverID, const int delay = 0, void* pData = nullptr);
	void routeMessage(Message msg);

	void update(void);

private:
	ObjectList m_objects;
	MessageList m_messages;
};

// ================================================ //

inline void MessageRouter::addObject(Object* pObject)
{ m_objects.push_back(pObject); }

// ================================================ //

#endif

// ================================================ //