#include "ThreadedCallbackTimerQueue.h"
#include "Utils.h"
#include "Exception.h"
#include "TickCountProvider.h"

namespace AmstelTech 
{
	
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// CThreadedCallbackTimerQueue
///////////////////////////////////////////////////////////////////////////////

CThreadedCallbackTimerQueue::CThreadedCallbackTimerQueue(
   const IProvideTickCount &tickProvider)
   :  m_timerQueue(tickProvider),
      m_shutdown(false)
{
   Start();
}

CThreadedCallbackTimerQueue::CThreadedCallbackTimerQueue(
   const DWORD maxTimeout,
   const IProvideTickCount &tickProvider)
   :  m_timerQueue(maxTimeout, tickProvider),
      m_shutdown(false)
{   
   Start();
}

CThreadedCallbackTimerQueue::CThreadedCallbackTimerQueue()
   :  m_shutdown(false)
{
   Start();
}

CThreadedCallbackTimerQueue::CThreadedCallbackTimerQueue(
   const DWORD maxTimeout)
   :  m_timerQueue(maxTimeout),
      m_shutdown(false)
{
   Start();
}

CThreadedCallbackTimerQueue::~CThreadedCallbackTimerQueue()
{
   InitiateShutdown();

   Wait();
}

CThreadedCallbackTimerQueue::Handle CThreadedCallbackTimerQueue::SetTimer(
   Timer &timer,
   const DWORD timeoutMillis,
   const UserData userData)
{
   CCriticalSection::Owner lock(m_criticalSection);
   
   Handle handle = m_timerQueue.SetTimer(timer, timeoutMillis, userData);

   SignalStateChange();

   return handle;
}

bool CThreadedCallbackTimerQueue::ResetTimer(
   Handle &handle, 
   Timer &timer,
   const DWORD timeoutMillis,
   const UserData userData)
{
   CCriticalSection::Owner lock(m_criticalSection);

   const bool wasPending = m_timerQueue.ResetTimer(handle, timer, timeoutMillis, userData);

   SignalStateChange();

   return wasPending;
}

bool CThreadedCallbackTimerQueue::CancelTimer(
   Handle &handle)
{
   CCriticalSection::Owner lock(m_criticalSection);
   
   const bool wasPending = m_timerQueue.CancelTimer(handle);

   SignalStateChange();

   return wasPending;
}

int CThreadedCallbackTimerQueue::Run()
{
   while (!m_shutdown)
   {
      DWORD timeout = GetNextTimeout();
    
      if (timeout == 0)
      {
         CCriticalSection::Owner lock(m_criticalSection);
   
         m_timerQueue.HandleTimeouts();
      }
      else 
      {
         m_stateChangeEvent.Wait(timeout);
      }
   }
   
   return 0;
}

DWORD CThreadedCallbackTimerQueue::GetNextTimeout()
{
   CCriticalSection::Owner lock(m_criticalSection);

   return m_timerQueue.GetNextTimeout();
}

void CThreadedCallbackTimerQueue::InitiateShutdown()
{
   m_shutdown = true;

   SignalStateChange();
}

void CThreadedCallbackTimerQueue::SignalStateChange()
{
   m_stateChangeEvent.Set();
}

} // End of namespace Win32
} // End of namespace AmstelTech