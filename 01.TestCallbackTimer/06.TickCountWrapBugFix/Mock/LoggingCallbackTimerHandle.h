#pragma once

#include "../../TestTools/TestLog.h"

#include "../../Tools/CallbackTimer.h"
#include "../../Tools/AutoResetEvent.h"

namespace AmstelTech 
{
	
namespace Win32 
{
	
namespace Mock 
{

///////////////////////////////////////////////////////////////////////////////
// CLoggingCallbackTimerHandle
///////////////////////////////////////////////////////////////////////////////

class CLoggingCallbackTimerHandle : 
   public AmstelTech::Test::CTestLog,
   public CCallbackTimer::Handle,
   private CCallbackTimer::Handle::Callback
{
   public :

      CLoggingCallbackTimerHandle();
   
      bool WaitForTimer(
         DWORD timeoutMillis);

      void CheckTimerNotExpired();

      void CheckTimerExpired(
         const DWORD userData,
         const DWORD timeoutMillis);

   private :

      // Implement CCallbackTimer::Handle::Callback

      virtual void OnTimer(
         CCallbackTimer::Handle &hnd,
         DWORD userData);

      CAutoResetEvent m_event;

      // No copies do not implement
      CLoggingCallbackTimerHandle(const CLoggingCallbackTimerHandle &rhs);
      CLoggingCallbackTimerHandle &operator=(const CLoggingCallbackTimerHandle &rhs);
};

} // End of namespace Mock
} // End of namespace Win32
} // End of namespace AmstelTech