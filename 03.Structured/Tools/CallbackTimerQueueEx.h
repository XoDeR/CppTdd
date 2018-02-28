#pragma once

#include "IQueueTimers.h"

#include <map>

namespace AmstelTech 
{
	
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// Classes defined in other files...
///////////////////////////////////////////////////////////////////////////////

class IProvideTickCount64;

///////////////////////////////////////////////////////////////////////////////
// CCallbackTimerQueueEx
///////////////////////////////////////////////////////////////////////////////

class CCallbackTimerQueueEx : public IQueueTimers
{
   public :

      /// Create a timer queue.

      CCallbackTimerQueueEx();

      /// Create a timer queue that uses the provdided instance of 
      /// IProvideTickCount64 to obtain its tick counts rather than getting
      /// them directly from the system.
      
      explicit CCallbackTimerQueueEx(
         const IProvideTickCount64 &tickProvider);

      ~CCallbackTimerQueueEx();

      /// Get the number of milliseconds until the next timer is due to fire.
      /// Or INFINITE if no timer is set.
      
      Milliseconds GetNextTimeout();

      /// Process any timers that have timed out.
      
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

      typedef std::multimap<ULONGLONG, TimerData *> TimerQueue;

      typedef std::map<Handle, TimerQueue::iterator> HandleMap;

      HandleMap::iterator ValidateHandle(
         const Handle &handle);

      bool CancelTimer(
         const Handle &handle,
         const HandleMap::iterator &it);

      void InsertTimer(
         const Handle &handle,
         TimerData * const pData,
         const Milliseconds timeout);

      void MarkHandleUnset(
         Handle handle);

      TimerQueue m_queue;

      HandleMap m_handleMap;

      const IProvideTickCount64 &m_tickProvider;

      const Milliseconds m_maxTimeout;

		/// No copies do not implement
      CCallbackTimerQueueEx(const CCallbackTimerQueueEx &rhs);
		/// No copies do not implement
      CCallbackTimerQueueEx &operator=(const CCallbackTimerQueueEx &rhs);
};

} // End of namespace Win32
} // End of namespace AmstelTech