// ================================================ //

#include "ObjectImpl.hpp"
#include "Engine.hpp"
#include "Log.hpp"

// ================================================ //

ObjectImpl::ObjectImpl(const char* textureFilename)
	:	m_pTexture(nullptr),
		m_pos(),
		m_bb(),
		m_name("Object")
{
	if(textureFilename != "null"){
		this->setTextureFile(textureFilename);
	}

	m_pos.x = m_pos.y = 0;

	static int nameCtr = 0;
	m_name += std::to_string(static_cast<long long>(nameCtr++));

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

	// Set position rect
	SDL_QueryTexture(m_pTexture, nullptr, nullptr, &m_pos.w, &m_pos.h);

	return (m_pTexture != nullptr);
}

// ================================================ //

void ObjectImpl::update(double dt)
{

}

// ================================================ //