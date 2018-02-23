#include "CallbackTimerQueue.h"
#include "Utils.h"
#include "Exception.h"
#include "TickCountProvider.h"

namespace AmstelTech 
{
	
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

static const CTickCountProvider s_tickProvider;

static const DWORD s_tickCountMax = 0xFFFFFFFF;

static const DWORD s_timeoutMax = s_tickCountMax / 4 * 3;

///////////////////////////////////////////////////////////////////////////////
// CCallbackTimerQueue
///////////////////////////////////////////////////////////////////////////////

CCallbackTimerQueue::CCallbackTimerQueue(
   const IProvideTickCount &tickProvider)
   :  m_tickProvider(tickProvider),
      m_pTimer(0),
      m_nextTimeout(0),
      m_userData(0),
      m_maxTimeout(s_timeoutMax)
{   
}

CCallbackTimerQueue::CCallbackTimerQueue(
   const DWORD maxTimeout,
   const IProvideTickCount &tickProvider)
   :  m_tickProvider(tickProvider),
      m_pTimer(0),
      m_nextTimeout(0),
      m_userData(0),
      m_maxTimeout(maxTimeout)
{   
}

CCallbackTimerQueue::CCallbackTimerQueue()
   :  m_tickProvider(s_tickProvider),
      m_pTimer(0),
      m_nextTimeout(0),
      m_userData(0),
      m_maxTimeout(s_timeoutMax)
{
}

CCallbackTimerQueue::CCallbackTimerQueue(
   const DWORD maxTimeout)
   :  m_tickProvider(s_tickProvider),
      m_pTimer(0),
      m_nextTimeout(0),
      m_userData(0),
      m_maxTimeout(maxTimeout)
{
}

CCallbackTimerQueue::Handle CCallbackTimerQueue::SetTimer(
   Timer &timer,
   const DWORD timeoutMillis,
   const UserData userData)
{
	if (timeoutMillis > m_maxTimeout)
   {
      throw CException(_T("CCallbackTimerQueue::SetTimer()"), _T("Timeout value is too large, max = ") + ToString(m_maxTimeout));
   }
	
   const DWORD now = m_tickProvider.GetTickCount();

   m_pTimer = &timer;

   m_nextTimeout = now + timeoutMillis;

   m_userData = userData;

   return reinterpret_cast<Handle>(m_pTimer);
}

bool CCallbackTimerQueue::CancelTimer(
   Handle handle)
{
   bool wasPending = false;

   if (m_pTimer != 0 && m_pTimer == reinterpret_cast<Timer *>(handle))
   {
      m_pTimer = 0;
      m_nextTimeout = 0;
      m_userData = 0;

      wasPending = true;
   }

   return wasPending;
}

DWORD CCallbackTimerQueue::GetNextTimeout() const
{
   DWORD timeout = INFINITE;

   if (m_pTimer)
   {
      const DWORD now = m_tickProvider.GetTickCount();

      timeout = m_nextTimeout - now;

      if (timeout > s_timeoutMax)
      {
         timeout = 0;
      }
   }  

   return timeout;
}

void CCallbackTimerQueue::HandleTimeouts()
{
   if (m_pTimer)
   {
      if (0 == GetNextTimeout())
      {
         m_pTimer->OnTimer(m_userData);

         m_pTimer = 0;
         m_nextTimeout = 0;
         m_userData = 0;
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
// CCallbackTimerQueue::Timer
///////////////////////////////////////////////////////////////////////////////

CCallbackTimerQueue::Timer::~Timer()
{
}

} // End of namespace Win32
} // End of namespace AmstelTech 