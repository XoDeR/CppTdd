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

/// A class that manages a group of timers that implement IQueueTimers::Timer 
/// and which have their IQueueTimers::Timer::OnTimer() method called when the 
/// timer expires. You must manually manage the handling and processing of 
/// timeouts by calling HandleTimeouts() every GetNextTimeout() milliseconds.
class CCallbackTimerQueue : public IQueueTimers
{
   public :

      CCallbackTimerQueue();
	  
	  explicit CCallbackTimerQueue(
         const Milliseconds maxTimeout);

      explicit CCallbackTimerQueue(
         const IProvideTickCount &tickProvider);
		 
		CCallbackTimerQueue(
			const Milliseconds maxTimeout,
			const IProvideTickCount &tickProvider);
		 
		~CCallbackTimerQueue();
		
		Milliseconds GetNextTimeout();

      void HandleTimeouts();

      // Implement IQueueTimers

      virtual IQueueTimers::Handle CreateTimer();

      virtual bool SetTimer(
         const IQueueTimers::Handle &handle, 
         IQueueTimers::Timer &timer,
         const Milliseconds timeout,
         const IQueueTimers::UserData userData);

      virtual bool CancelTimer(
         const IQueueTimers::Handle &handle);

      virtual bool DestroyTimer(
         IQueueTimers::Handle &handle);

      virtual bool DestroyTimer(
         const IQueueTimers::Handle &handle);

      virtual void SetTimer(
         IQueueTimers::Timer &timer,
         const Milliseconds timeout,
         const IQueueTimers::UserData userData);

      virtual Milliseconds GetMaximumTimeout() const;

   private :
   
		class TimerData;
		
		typedef std::multimap<Milliseconds, TimerData *> TimerQueue;

      typedef std::pair<TimerQueue *, TimerQueue::iterator> HandleMapValue;

      typedef std::map<Handle, HandleMapValue> HandleMap;

      HandleMap::iterator ValidateHandle(
         const Handle &handle);

      bool CancelTimer(
         const Handle &handle,
         const HandleMap::iterator &it);

      Milliseconds GetAbsoluteTimeout(
         const Milliseconds timeout,
         const Milliseconds now) const;

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

      const Milliseconds m_maxTimeout;
	  
	  Milliseconds m_lastWrappedTimerSetTicks;

      // No copies do not implement
      CCallbackTimerQueue(const CCallbackTimerQueue &rhs);
      CCallbackTimerQueue &operator=(const CCallbackTimerQueue &rhs);
};

} // End of namespace Win32
} // End of namespace AmstelTech 