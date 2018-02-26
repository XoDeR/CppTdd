#pragma once

#include "IQueueTimers.h"

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
		
		typedef std::multimap<DWORD, TimerData *> TimerQueue;

      typedef std::pair<TimerQueue *, TimerQueue::iterator> HandleMapValue;

      typedef std::map<Handle, HandleMapValue> HandleMap;

      HandleMap::iterator ValidateHandle(
         const Handle &handle);

      bool CancelTimer(
         const Handle &handle,
         const HandleMap::iterator &it);

      DWORD GetAbsoluteTimeout(
         const DWORD timeoutMillis,
         bool &wrapped) const;

      void InsertTimer(
         const Handle &handle,
         TimerData * const pData,
         const DWORD timeoutMillis,
         const bool wrapped);

      void MarkHandleUnset(
         Handle handle);

      TimerQueue m_queue1;
      TimerQueue m_queue2;

      TimerQueue *m_pCurrentQueue;
      TimerQueue *m_pWrappedQueue;

      HandleMap m_handleMap;

      const IProvideTickCount &m_tickProvider;

      const DWORD m_maxTimeout;

      // No copies do not implement
      CCallbackTimerQueue(const CCallbackTimerQueue &rhs);
      CCallbackTimerQueue &operator=(const CCallbackTimerQueue &rhs);
};

} // End of namespace Win32
} // End of namespace AmstelTech 