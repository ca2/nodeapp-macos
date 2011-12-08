#pragma once


#include "get_platform.h"






/**
* \file		src/lib/pal/linux/thread_linux.hpp
* \brief	Platform independent threads and synchronization objects (linux version)
* \author	Thomas Nass
*/

#include <pthread.h>
#include <sys/resource.h>

namespace ca
{


//namespace gen { namespace pal {


	/// An enum representing thread priorities.
	enum thread_priority {
		thread_priority_idle 	= 1,
		thread_priority_lowest 	= 48,
		thread_priority_below_normal,
		thread_priority_normal,
		thread_priority_above_normal,
		thread_priority_highest,
		thread_priority_time_critical = 99
	};

	///  \brief		global function to set thread priority for current thread
	///  \param		new priority
	inline bool set_thread_priority(int priority)
	{
		return ( setpriority(PRIO_PROCESS, getpid(), priority) == 0 );
	}

	///  \brief		global function to get thread priority for current thread
	///  \return	priority of current thread
	inline int thread_priority()
	{ return getpriority(PRIO_PROCESS, getpid()); }

} // namespace ca


inline enum ::ca::thread_priority get_thread_priority_normal()
{

      return ::ca::thread_priority_normal;

}
