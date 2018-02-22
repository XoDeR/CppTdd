#include "MockTickCountProvider.h"

#include "../Tools/Utils.h"

using AmstelTech::Win32::ToString;

namespace AmstelTech 
{
	
namespace Win32 
{
	
namespace Mock 
{

///////////////////////////////////////////////////////////////////////////////
// CMockTickCountProvider
///////////////////////////////////////////////////////////////////////////////

CMockTickCountProvider::CMockTickCountProvider()
   : m_tickCount(0)
   , m_mainThreadId(::GetCurrentThreadId())
{
	m_blockedCallEvent.Reset();
}

void CMockTickCountProvider::AllowCalls(
   const size_t numCalls)
{
   m_counter.SetValue(numCalls);
}

bool CMockTickCountProvider::AllowCalls(
   const size_t numCalls,
   const DWORD timeoutMillis)
{
   AllowCalls(numCalls);

   return m_counter.WaitForZero(timeoutMillis);
}

bool CMockTickCountProvider::WaitForBlockedCall(
   const DWORD timeoutMillis)
{
   return m_blockedCallEvent.Wait(timeoutMillis);
}

void CMockTickCountProvider::SetTickCount(
   const DWORD tickCount)
{
   ::InterlockedExchange(reinterpret_cast<volatile long *>(&m_tickCount), tickCount);
}

DWORD CMockTickCountProvider::GetTickCount() const
{
   if (m_mainThreadId != ::GetCurrentThreadId())
   {
      CCriticalSection::Owner lock(m_criticalSection);

      if (0 == m_counter.GetValue())
      {
         m_blockedCallEvent.Set();
      }

      m_counter.WaitForNonZero();

      m_blockedCallEvent.Reset();

      LogMessage(_T("GetTickCount: Another Thread: ") + ToString(m_tickCount));

      m_counter.Decrement();
   }
   else
   {
      LogMessage(_T("GetTickCount: Main Thread: ") + ToString(m_tickCount));
   }
   
   return m_tickCount;
}

///////////////////////////////////////////////////////////////////////////////
// CMockTickCountProvider::AutoRelease
///////////////////////////////////////////////////////////////////////////////

CMockTickCountProvider::AutoRelease::AutoRelease(
   CMockTickCountProvider &timer)
   :  m_timer(timer)
{

}

CMockTickCountProvider::AutoRelease::~AutoRelease()
{
   m_timer.AllowCalls(1000);
}

} // End of namespace Mock
} // End of namespace Win32
} // End of namespace AmstelTech 

