// ================================================ //

#ifndef __ENGINE_HPP__
#define __ENGINE_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

class EngineImpl;

// ================================================ //

class Engine : public Singleton<Engine>
{
public:
	explicit Engine(void);
	~Engine(void);

	void clearRenderer(void);
	//renderObject()...
	void renderPresent(void);

private:
	std::tr1::shared_ptr<EngineImpl> m_pImpl;
};

// ================================================ //

#endif

// ================================================ //