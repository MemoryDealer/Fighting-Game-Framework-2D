// ================================================ //

#ifndef __SINGLETON_HPP__
#define __SINGLETON_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

// Disable warnings for this singleton class
#pragma warning (disable : 4311)
#pragma warning (disable : 4312)

// ================================================ //

template <typename T>
class Singleton
{
public:
	Singleton(void)
	{
		assert(!msSingleton);

#if defined ( _MSC_VER ) && _MSC_VER < 1200
		int offset = (int)(T*)1 - (int)(Singleton <T>*)(T*)1;
		msSingleton = (T*)((int)this + offset);
#else
		msSingleton = static_cast<T*>(this);
#endif
	}

	~Singleton(void)
	{
		assert(msSingleton);
		msSingleton = 0;
	}

	// Getter functions
	static T& getSingleton(void)
	{ Assert(msSingleton); return (*msSingleton); }

	static T* getSingletonPtr(void)
	{ return msSingleton; }

protected:
	static T* msSingleton;

private:
	/** \brief Explicit private copy constructor. This is a forbidden operation.*/
	Singleton(const Singleton<T> &);

	/** \brief Private operator= . This is a forbidden operation. */
	Singleton& operator=(const Singleton<T> &);
};

// ================================================ //

#endif 

// ================================================ //