// ========================================================================= //
// Fighting game framework (2D) with online multiplayer.
// Copyright(C) 2014 Jordan Sparks <unixunited@live.com>
//
// This program is free software; you can redistribute it and / or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 3
// of the License, or(at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
// ========================================================================= //
// File: Singleton.hpp
// Author: Jordan Sparks <unixunited@live.com>
// ================================================ //
// Defines and implements Singleton class.
// ================================================ //

#ifndef __SINGLETON_HPP__
#define __SINGLETON_HPP__

// ================================================ //

#include "stdafx.hpp"

// ================================================ //

// Disable warnings for this singleton class.
#pragma warning (disable : 4311)
#pragma warning (disable : 4312)

// ================================================ //

// A basic singleton utility.
// Derive a class from Singleton and allocate it with new ClassName();,
// free it with delete ClassName::getSingletonPtr();.
template <typename T>
class Singleton
{
public:
	// Assign singleton's location in memory.
	explicit Singleton(void)
	{
		assert(!msSingleton);

#if defined ( _MSC_VER ) && _MSC_VER < 1200
		int offset = (int)(T*)1 - (int)(Singleton <T>*)(T*)1;
		msSingleton = (T*)((int)this + offset);
#else
		msSingleton = static_cast<T*>(this);
#endif
	}

	// Set singleton's memory location to null.
	~Singleton(void)
	{
		assert(msSingleton);
		msSingleton = nullptr;
	}

	// Getters

	// Returns the singleton object.
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