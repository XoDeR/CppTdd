#pragma once

#include "../TestTools/TestLog.h"

#include "../IProvideTickCount.h"

#include "../CriticalSection.h"
#include "../WaitableCounter.h"

namespace AmstelTech 
{
	
namespace Win32 
{
	
namespace Mock 
{

///////////////////////////////////////////////////////////////////////////////
// CMockTickCountProvider
///////////////////////////////////////////////////////////////////////////////

class CMockTickCountProvider : public IProvideTickCount, public AmstelTech::Test::CTestLog
{
   public:
		class AutoRelease
		{
        public :

            AutoRelease(CMockTickCountProvider& timer);

            ~AutoRelease();

        private :

            CMockTickCountProvider &m_timer;

            // No copies do not implement
            AutoRelease(const AutoRelease &rhs);
            AutoRelease &operator=(const AutoRelease &rhs);
		};

      CMockTickCountProvider();
	  
	  explicit CMockTickCountProvider(
         const DWORD tickCount);
	  
	  void AllowCalls(
         const size_t numCalls);

      bool AllowCalls(
         const size_t numCalls,
         const DWORD timeoutMillis);

      bool WaitForBlockedCall(
         const DWORD timeoutMillis);

      void SetTickCount(
         const DWORD tickCount);

      // Implement IProvideTickCount

      virtual DWORD GetTickCount() const;

   private :

      volatile DWORD m_tickCount;
	  
	  const DWORD m_mainThreadId;

      mutable CCriticalSection m_criticalSection;

      mutable CWaitableCounter m_counter;

      mutable CManualResetEvent m_blockedCallEvent;

      // No copies do not implement
      CMockTickCountProvider(const CMockTickCountProvider &rhs);
      CMockTickCountProvider &operator=(const CMockTickCountProvider &rhs);
};

} // End of namespace Mock
} // End of namespace Win32
} // End of namespace AmstelTech 