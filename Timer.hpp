// ================================================ //

#ifndef __TIMER_HPP__
#define __TIMER_HPP__

// ================================================ //

class Timer
{
public:
	explicit Timer(void);
	~Timer(void);

	int restart(void);
	void stop(void);
	void pause(void);
	void unpause(void);

	int getTicks(void);

	bool isStarted(void) const;
	bool isPaused(void) const;

private:
	int		m_startTicks;
	int		m_pausedTicks;
	bool	m_paused;
	bool	m_started;
};

// ================================================ //

inline bool Timer::isStarted(void) const
{ return m_started; }

inline bool Timer::isPaused(void) const
{ return m_paused; }

// ================================================ //

#endif

// ================================================ //