// ================================================ //

#include "ObjectImpl.hpp"
#include "Engine.hpp"
#include "Log.hpp"

// ================================================ //

ObjectImpl::ObjectImpl(const char* textureFilename)
	:	m_pTexture(nullptr),
		m_src(),
		m_dst(),
		m_flip(SDL_FLIP_NONE),
		m_name("Object"),
		m_pFSM(new FSM(0))
{
	static int nameCtr = 0;
	m_name += std::to_string(static_cast<long long>(nameCtr++));

	m_dst.x = m_dst.y = 0;

	if(textureFilename != ""){
		this->setTextureFile(textureFilename);
		m_src.x = m_src.y = 0;
		SDL_QueryTexture(m_pTexture, nullptr, nullptr, &m_src.w, &m_src.h);
	}

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

void ObjectImpl::setTextureCoordinates(int x, int y, int w, int h)
{ 
	m_src.x = x; m_src.y = y; 
	if(w != 0)
		m_src.w = m_dst.w = w;
	if(h != 0)
		m_src.h = m_dst.h = h;
}

// ================================================ //

void ObjectImpl::render(void)
{
	//! I hope it's safe to const_cast the renderer pointer
	SDL_RenderCopyEx(const_cast<SDL_Renderer*>(Engine::getSingletonPtr()->getRenderer()), 
		m_pTexture, &m_src, &m_dst, 0, nullptr, m_flip);
}

// ================================================ //