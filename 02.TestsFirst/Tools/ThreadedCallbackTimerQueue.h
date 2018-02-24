#pragma once

#include "CallbackTimerQueue.h"
#include "Thread.h"
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
   private CThread, 
   private CCallbackTimerQueue
{
   public :

      CThreadedCallbackTimerQueue();

      explicit CThreadedCallbackTimerQueue(
         const DWORD maxTimeout);

      explicit CThreadedCallbackTimerQueue(
         const IProvideTickCount &tickProvider);

      CThreadedCallbackTimerQueue(
         const DWORD maxTimeout,
         const IProvideTickCount &tickProvider);

      ~CThreadedCallbackTimerQueue();

      Handle SetTimer(
         Timer &timer,
         const DWORD timeoutMillis,
         const UserData userData);

      bool CancelTimer(
         Handle handle);

   private :

      DWORD GetNextTimeout();

      void InitiateShutdown();

      void SignalStateChange();

      // Implement CThread

      virtual int Run();

      mutable CCriticalSection m_criticalSection;

      CAutoResetEvent m_stateChangeEvent;

      volatile bool m_shutdown;

      // No copies do not implement
      CThreadedCallbackTimerQueue(const CThreadedCallbackTimerQueue &rhs);
      CThreadedCallbackTimerQueue &operator=(const CThreadedCallbackTimerQueue &rhs);
};

} // End of namespace Win32
} // End of namespace AmstelTech