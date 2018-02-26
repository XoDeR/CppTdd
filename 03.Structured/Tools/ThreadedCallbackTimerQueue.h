#pragma once

#include "../Platform/Types.h"

#include "CallbackTimerQueue.h"
#include "Thread.h"
#include "IRunnable.h"
#include "AutoResetEvent.h"
#include "CriticalSection.h"

namespace AmstelTech 
{
	
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// CThreadedCallbackTimerQueue
///////////////////////////////////////////////////////////////////////////////

class CThreadedCallbackTimerQueue : 
   public IQueueTimers,
   private IRunnable
{
   public :

      CThreadedCallbackTimerQueue();

      explicit CThreadedCallbackTimerQueue(
         const Milliseconds maxTimeout);

      explicit CThreadedCallbackTimerQueue(
         const IProvideTickCount &tickProvider);

      CThreadedCallbackTimerQueue(
         const Milliseconds maxTimeout,
         const IProvideTickCount &tickProvider);

      ~CThreadedCallbackTimerQueue();

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

      /// Called when the timer queue thread is terminated due to an exception
      /// this is a BAD situation! Override this to deal with it, log the error,
      /// etc...

      virtual void OnThreadTerminationException(
         const _tstring &message);

   private :

      Milliseconds GetNextTimeout();

      void InitiateShutdown();

      void SignalStateChange();

      // Implement IRunnable

      virtual int Run() throw();

      mutable CCriticalSection m_criticalSection;

      CAutoResetEvent m_stateChangeEvent;

      CThread m_thread;

      CCallbackTimerQueue m_timerQueue;

      volatile bool m_shutdown;

      // No copies do not implement
      CThreadedCallbackTimerQueue(const CThreadedCallbackTimerQueue &rhs);
      CThreadedCallbackTimerQueue &operator=(const CThreadedCallbackTimerQueue &rhs);
};

} // End of namespace Win32
} // End of namespace AmstelTech