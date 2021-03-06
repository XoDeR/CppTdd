#pragma once

#include "IQueueTimers.h"
#include "CriticalSection.h"

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

      void SetMaintenanceTimer();

      ULONGLONG GetTickCount64();

      TimerQueue m_queue;

      HandleMap m_handleMap;

      const IProvideTickCount &m_tickProvider;

      const Milliseconds m_maxTimeout;

      LARGE_INTEGER m_lastCount;

      CCriticalSection m_criticalSection;

      Handle m_maintenanceTimer;

      class MaintenanceTimerHandler : public IQueueTimers::Timer
      {
         // Implement IQueueTimers::Timer 

         virtual void OnTimer(
            IQueueTimers::Timer::UserData userData);
      };

      MaintenanceTimerHandler m_maintenanceTimerHandler;

      // No copies do not implement
      CCallbackTimerQueue(const CCallbackTimerQueue &rhs);
      CCallbackTimerQueue &operator=(const CCallbackTimerQueue &rhs);
};

} // End of namespace Win32
} // End of namespace AmstelTech 