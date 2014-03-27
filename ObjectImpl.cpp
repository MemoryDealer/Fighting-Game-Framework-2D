// ================================================ //

#include "ObjectImpl.hpp"
#include "Engine.hpp"
#include "Log.hpp"

// ================================================ //

ObjectImpl::ObjectImpl(const char* textureFilename)
	:	m_pTexture(nullptr),
		m_pos(),
		m_flip(SDL_FLIP_NONE),
		m_name("Object")
{
	static int nameCtr = 0;
	m_name += std::to_string(static_cast<long long>(nameCtr++));

	if(textureFilename != ""){
		this->setTextureFile(textureFilename);
	}

	m_pos.x = m_pos.y = 0;

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
	SDL_QueryTexture(m_pTexture, nullptr, nullptr, &m_pos.w, &m_pos.h);

	return (m_pTexture != nullptr);
}

// ================================================ //

void ObjectImpl::render(void)
{
	//! I hope it's safe to const_cast the renderer pointer
	SDL_RenderCopyEx(const_cast<SDL_Renderer*>(Engine::getSingletonPtr()->getRenderer()), 
		m_pTexture, nullptr, &m_pos, 0, nullptr, m_flip);
}

// ================================================ //