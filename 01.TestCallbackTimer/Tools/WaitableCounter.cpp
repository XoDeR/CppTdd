#include "WaitableCounter.h"

namespace AmstelTech 
{
	
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// CWaitableCounter
///////////////////////////////////////////////////////////////////////////////

CWaitableCounter::CWaitableCounter(
   const long initialCount)
{
   SetValue(initialCount);
}

void CWaitableCounter::WaitForZero() const
{
   m_atZeroEvent.Wait();
}

bool CWaitableCounter::WaitForZero(
   DWORD timeoutMillis) const
{
   return m_atZeroEvent.Wait(timeoutMillis);
}

void CWaitableCounter::WaitForNonZero() const
{
   m_notAtZeroEvent.Wait();
}

bool CWaitableCounter::WaitForNonZero(
   DWORD timeoutMillis) const
{
   return m_notAtZeroEvent.Wait(timeoutMillis);
}

void CWaitableCounter::SetValue(
   const long value)
{
   CCriticalSection::Owner lock(m_criticalSection);

   m_count = value;
   
   if (value == 0)
   {
      m_atZeroEvent.Set();
      m_notAtZeroEvent.Reset();
   }
   else
   {
      m_atZeroEvent.Reset();
      m_notAtZeroEvent.Set();
   }         
}

void CWaitableCounter::Increment()
{
   CCriticalSection::Owner lock(m_criticalSection);

   if (0 == m_count)
   {
      m_atZeroEvent.Reset();
      m_notAtZeroEvent.Set();
   }         

   m_count++;
}

void CWaitableCounter::Decrement()
{
   CCriticalSection::Owner lock(m_criticalSection);

   m_count--;

   if (0 == m_count)
   {
      m_atZeroEvent.Set();
      m_notAtZeroEvent.Reset();
   }         
}

long CWaitableCounter::GetValue() const
{
   CCriticalSection::Owner lock(m_criticalSection);

   return m_count;
}

} // End of namespace Win32
} // End of namespace AmstelTech