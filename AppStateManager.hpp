// ================================================ //

#ifndef __APPSTATEMANAGER_HPP__
#define __APPSTATEMANAGER_HPP__

// ================================================ //

#include "AppState.hpp"

// ================================================ //

class AppStateManager : public AppStateListener
{
public:
	typedef struct{
		std::string name;
		AppState* pState;
	} STATE_INFO;

	explicit AppStateManager(void);
	~AppStateManager(void);

	void manageAppState(const std::string& name, AppState* pState);

	AppState* findByName(const std::string& stateName);

	void start(AppState* pState);
	void changeAppState(AppState* pState);
	bool pushAppState(AppState* pState);
	void popAppState(void);
	void pauseAppState(void);
	void shutdown(void);

protected:
	void init(AppState* pState);

	std::vector<AppState*>	m_activeStateStack;
	std::vector<STATE_INFO> m_states;
	bool					m_bShutdown;
};

// ================================================ //

#endif

// ================================================ //