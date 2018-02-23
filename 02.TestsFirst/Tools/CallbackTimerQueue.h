#pragma once

#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
#endif

#include <list>
#include <map>

namespace AmstelTech 
{
	
namespace Win32 
{

class IProvideTickCount;

///////////////////////////////////////////////////////////////////////////////
// CCallbackTimerQueue
///////////////////////////////////////////////////////////////////////////////

class CCallbackTimerQueue
{
   public :

      typedef ULONG_PTR UserData;

      class Timer;
	  
	  typedef ULONG_PTR Handle;
	  
	  struct TimerData;

      CCallbackTimerQueue();
	  
	  explicit CCallbackTimerQueue(
         const DWORD maxTimeout);

      explicit CCallbackTimerQueue(
         const IProvideTickCount &tickProvider);
		 
		CCallbackTimerQueue(
			const DWORD maxTimeout,
			const IProvideTickCount &tickProvider);
		 
		~CCallbackTimerQueue();

      Handle SetTimer(
         Timer &timer,
         const DWORD timeoutMillis,
         const UserData userData);
		 
		bool CancelTimer(
         Handle handle);

      DWORD GetNextTimeout() const;

      void HandleTimeouts();

   private :

      typedef std::list<TimerData *> TimerQueue;

      typedef std::map<Handle, TimerQueue::iterator> HandleMap;

      TimerQueue m_queue;

      HandleMap m_handleMap;

      TimerQueue::iterator m_wrapPoint;

      const IProvideTickCount &m_tickProvider;

      const DWORD m_maxTimeout;

      // No copies do not implement
      CCallbackTimerQueue(const CCallbackTimerQueue &rhs);
      CCallbackTimerQueue &operator=(const CCallbackTimerQueue &rhs);
};

///////////////////////////////////////////////////////////////////////////////
// CCallbackTimerQueue::Timer
///////////////////////////////////////////////////////////////////////////////

class CCallbackTimerQueue::Timer
{
   public :

      virtual void OnTimer(
         UserData userData) = 0;

   protected :

      ~Timer();
};

} // End of namespace Win32
} // End of namespace AmstelTech 