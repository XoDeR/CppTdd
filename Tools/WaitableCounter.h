#pragma once

#include "ManualResetEvent.h"
#include "CriticalSection.h"

namespace AmstelTech 
{
	
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// CWaitableCounter
///////////////////////////////////////////////////////////////////////////////

class CWaitableCounter
{
   public :
   
      CWaitableCounter(
         long initialCount = 0);
      
      void WaitForZero() const;

      bool WaitForZero(
         DWORD timeoutMillis) const;

      void WaitForNonZero() const;

      bool WaitForNonZero(
         DWORD timeoutMillis) const;

      void SetValue(
         const long value);

      void Increment();

      void Decrement();

      long GetValue() const;

   private :

      mutable CCriticalSection m_criticalSection;

      volatile long m_count;

      CManualResetEvent m_atZeroEvent;

      CManualResetEvent m_notAtZeroEvent;

      // No copies do not implement
      CWaitableCounter(const CWaitableCounter &rhs);
      CWaitableCounter &operator=(const CWaitableCounter &rhs);
};

} // End of namespace Win32
} // End of namespace AmstelTech 