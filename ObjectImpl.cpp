// ================================================ //

#include "ObjectImpl.hpp"
#include "Engine.hpp"
#include "Log.hpp"
#include "FSM.hpp"
#include "MessageRouter.hpp"

// ================================================ //

ObjectImpl::ObjectImpl(const unsigned int type)
	:	m_pTexture(nullptr),
		m_src(),
		m_dst(),
		m_flip(SDL_FLIP_NONE),
		m_name("ObjectID "),
		m_pFSM(new FSM(0))
{
	static int nameCtr = 0;
	m_id = nameCtr++;
	m_name += std::to_string(static_cast<long long>(m_id));

	m_src.x = m_src.y = m_dst.x = m_dst.y = 0;

	Log::getSingletonPtr()->logMessage("Object \"" + m_name + "\" created!");
}

// ================================================ //

ObjectImpl::~ObjectImpl(void)
{
	if(m_pTexture != nullptr)
		Engine::getSingletonPtr()->destroyTexture(m_pTexture);

	Log::getSingletonPtr()->logMessage("Destroyed Object \"" + m_name + "\"");
}

// ================================================ //

bool ObjectImpl::setTextureFile(const char* filename)
{
	if(m_pTexture != nullptr)
		Engine::getSingletonPtr()->destroyTexture(m_pTexture);

	Log::getSingletonPtr()->logMessage("Setting texture \"" + std::string(filename) + 
		"\" for Object \"" + m_name + "\"");
	m_pTexture = Engine::getSingletonPtr()->loadTexture(filename);

	// Get texture width/height
	SDL_QueryTexture(m_pTexture, nullptr, nullptr, &m_src.w, &m_src.h);
	m_dst.w = m_src.w;
	m_dst.h = m_src.h;

	return (m_pTexture != nullptr);
}

// ================================================ //

void ObjectImpl::setTextureCoordinates(const int x, const int y, const int w, const int h)
{ 
	m_src.x = x; m_src.y = y; 
	if(w != 0)
		m_src.w = m_dst.w = w;
	if(h != 0)
		m_src.h = m_dst.h = h;
}

// ================================================ //

void ObjectImpl::sendMessage(const Message& msg)
{
	printf("Received message type %d\n", msg.type);
}

// ================================================ //

void ObjectImpl::render(void)
{
	/*SDL_Rect dst;
	float fWidth = Engine::getSingletonPtr()->getWindowWidth() / 800;
	float fHeight = Engine::getSingletonPtr()->getWindowHeight() / 600;

	dst.x = (m_dst.x * fWidth) - ((m_dst.w * 1.0) * fWidth / 2);
	dst.y = (m_dst.y * fWidth) - ((m_dst.h * 1.0) * fHeight / 2);
	dst.w = m_dst.w * fWidth;
	dst.h = m_dst.h * fHeight;*/

	//! I hope it's safe to const_cast the renderer pointer
	SDL_RenderCopyEx(const_cast<SDL_Renderer*>(Engine::getSingletonPtr()->getRenderer()), 
		m_pTexture, &m_src, &m_dst, 0, nullptr, m_flip);
}

// ================================================ //