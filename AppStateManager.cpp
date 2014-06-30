// ================================================ //
// Extreme Metal Fighter
// Copyright (C) 2014 Jordan Sparks. All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential
// Written by Jordan Sparks <unixunited@live.com> June 2014
// ================================================ //
// File: AppStateManager.cpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Implements AppStateManager class.
// ================================================ //

#include "AppStateManager.hpp"
#include "Engine.hpp"
#include "MessageRouter.hpp"
#include "Timer.hpp"

// ================================================ //

AppStateManager::AppStateManager(void) :	
m_bShutdown(false)
{

}

// ================================================ //

AppStateManager::~AppStateManager(void)
{
	STATE_INFO si;

	Log::getSingletonPtr()->logMessage("Clearing active state stack...");
	for(;!m_activeStateStack.empty();){
		m_activeStateStack.back()->exit();
		m_activeStateStack.pop_back();
	}

	Log::getSingletonPtr()->logMessage("Clearing states...");
	for(;!m_states.empty();){
		si = m_states.back();
		si.pState->destroy();
		m_states.pop_back();
	}
}

// ================================================ //

void AppStateManager::manageAppState(const std::string& stateName, AppState* pState)
{
	Log::getSingletonPtr()->logMessage("Managing app state \"" + stateName + "\"...");

	try{
		STATE_INFO si;
		si.name = stateName;
		si.pState = pState;
		m_states.push_back(si);
	}
	catch(std::exception& e){
		delete pState;
		std::string buf = "Error while trying to manage a new app state: " + std::string(e.what());
		throw std::exception(buf.c_str());
	}
}

// ================================================ //

AppState* AppStateManager::findByName(const std::string& stateName)
{
	std::vector<STATE_INFO>::iterator itr;

	for(itr=m_states.begin(); itr!=m_states.end(); ++itr){
		if (itr->name == stateName){
			return itr->pState;
		}
	}

	return nullptr;
}

// ================================================ //

void AppStateManager::start(AppState* pState)
{
	this->changeAppState(pState);

	double dt = 1.0;
	Uint32 newTime = 0, currentTime = 0;
	Timer capTimer;
	const int TICKS_PER_FRAME = 1000 / Engine::getSingletonPtr()->getMaxFrameRate();

	Log::getSingletonPtr()->logMessage("Entering main loop...");

	for(;!m_bShutdown;){

		if (Engine::getSingletonPtr()->isWindowFocused()){
			capTimer.restart();

			newTime = SDL_GetTicks();
			dt = static_cast<double>(newTime - currentTime) / 1000.0;
			currentTime = newTime;

			SDL_SetRenderDrawColor(Engine::getSingletonPtr()->getRenderer(), 0, 0, 0, 255);

			// Perform global updates.
			MessageRouter::getSingletonPtr()->update();
			m_activeStateStack.back()->update(dt);

			// Regulate the maximum frame rate (in case VSync is off).
			int frameTicks = capTimer.getTicks();
			if (frameTicks < TICKS_PER_FRAME){
				SDL_Delay(TICKS_PER_FRAME - frameTicks);
			}
		}
		else{
			SDL_Event e;
			while(SDL_PollEvent(&e)){
				if (e.type == SDL_WINDOWEVENT){
					if (e.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
						Engine::getSingletonPtr()->setWindowFocused(true);
				}
			}
			
			currentTime = SDL_GetTicks();
		}
	}

	Log::getSingletonPtr()->logMessage("Shutting down...");
}

// ================================================ //

void AppStateManager::changeAppState(AppState* pState)
{
	if (!m_activeStateStack.empty()){
		m_activeStateStack.back()->exit();
		m_activeStateStack.pop_back();
	}

	Log::getSingletonPtr()->logMessage("Changing to app state \"" + pState->getName() + "\"");
	m_activeStateStack.push_back(pState);
	this->init(pState);
	m_activeStateStack.back()->enter();
}

// ================================================ //

bool AppStateManager::pushAppState(AppState* pState)
{
	if (!m_activeStateStack.empty()){
		if (!m_activeStateStack.back()->pause())
			return false;
	}

	Log::getSingletonPtr()->logMessage("Pushing app state \"" + pState->getName() + "\"");
	m_activeStateStack.push_back(pState);
	this->init(pState);
	m_activeStateStack.back()->enter();

	return true;
}

// ================================================ //

void AppStateManager::popAppState(void)
{
	if (!m_activeStateStack.empty()){
		Log::getSingletonPtr()->logMessage("Popping state \"" + m_activeStateStack.back()->getName() + "\"...");
		m_activeStateStack.back()->exit();
		m_activeStateStack.pop_back();
	}

	if (!m_activeStateStack.empty()){
		this->init(m_activeStateStack.back());
		m_activeStateStack.back()->resume();
	}
	else{
		this->shutdown();
	}
}

// ================================================ //

void AppStateManager::pauseAppState(void)
{
	if (!m_activeStateStack.empty()){
		m_activeStateStack.back()->pause();
	}

	// Resume state in the stack below.
	if (m_activeStateStack.size() > 2){
		this->init(m_activeStateStack.at(m_activeStateStack.size() - 2));
		m_activeStateStack.at(m_activeStateStack.size() - 2)->resume();
	}
}

// ================================================ //

void AppStateManager::shutdown(void)
{
	m_bShutdown = true;
}

// ================================================ //

void AppStateManager::init(AppState* pState)
{
	
}

// ================================================ //