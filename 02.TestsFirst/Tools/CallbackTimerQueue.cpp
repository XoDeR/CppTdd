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

///////////////////////////////////////////////////////////////////////////////
// CCallbackTimerQueue
///////////////////////////////////////////////////////////////////////////////

CCallbackTimerQueue::CCallbackTimerQueue(
   const IProvideTickCount &tickProvider)
   :  m_tickProvider(tickProvider),
      m_pTimer(0),
      m_nextTimeout(0),
      m_userData(0)
{   
}

CCallbackTimerQueue::CCallbackTimerQueue()
   :  m_tickProvider(s_tickProvider),
      m_pTimer(0),
      m_nextTimeout(0),
      m_userData(0)
{
}

void CCallbackTimerQueue::SetTimer(
   Timer &timer,
   const DWORD timeoutMillis,
   const UserData userData)
{
   const DWORD now = m_tickProvider.GetTickCount();

   m_pTimer = &timer;

   m_nextTimeout = now + timeoutMillis;

   m_userData = userData;
}

DWORD CCallbackTimerQueue::GetNextTimeout() const
{
   DWORD timeout = INFINITE;

   if (m_pTimer)
   {
      const DWORD now = m_tickProvider.GetTickCount();

      if (now > m_nextTimeout)
      {
         timeout = 0;
      }
      else
      {
         timeout = m_nextTimeout - now;
      }
   }

   return timeout;
}

void CCallbackTimerQueue::HandleTimeouts()
{
   if (m_pTimer)
   {
      const DWORD now = m_tickProvider.GetTickCount();

      if (now >= m_nextTimeout)
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