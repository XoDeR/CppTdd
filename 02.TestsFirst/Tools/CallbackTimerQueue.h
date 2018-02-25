#pragma once

#include "IQueueTimers.h"

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

class CCallbackTimerQueue : public IQueueTimers
{
   public :

      CCallbackTimerQueue();
	  
	  explicit CCallbackTimerQueue(
         const DWORD maxTimeout);

      explicit CCallbackTimerQueue(
         const IProvideTickCount &tickProvider);
		 
		CCallbackTimerQueue(
			const DWORD maxTimeout,
			const IProvideTickCount &tickProvider);
		 
		~CCallbackTimerQueue();

      void HandleTimeouts();

      // Implement IQueueTimers

      virtual Handle CreateTimer();

      virtual bool SetTimer(
         const Handle &handle, 
         Timer &timer,
         const DWORD timeoutMillis,
         const UserData userData);

      virtual bool CancelTimer(
         const Handle &handle);

      virtual bool DestroyTimer(
         Handle &handle);

      virtual void SetTimer(
         Timer &timer,
         const DWORD timeoutMillis,
         const UserData userData);

   private :
   
		class TimerData;

      TimerData *CreateTimer(
         Timer &timer,
         const DWORD timeoutMillis,
         const UserData userData,
         bool &wrapped) const;

      DWORD GetAbsoluteTimeout(
         const DWORD timeoutMillis,
         bool &wrapped) const;

      Handle InsertTimer(
         TimerData *pData,
         const bool wrapped);

      TimerData *RemoveTimer(
         Handle handle);

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

} // End of namespace Win32
} // End of namespace AmstelTech 