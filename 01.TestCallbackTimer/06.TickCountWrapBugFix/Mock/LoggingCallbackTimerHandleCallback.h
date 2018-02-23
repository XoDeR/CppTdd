#pragma once

#include "TestTools/TestLog.h"

#include "../../Tools/CallbackTimer.h"
#include "../../Tools/AutoResetEvent.h"

namespace AmstelTech 
{
	
namespace Win32 
{

namespace Mock 
{


class CLoggingCallbackTimerHandleCallback : public AmstelTech::Test::CTestLog, public CCallbackTimer::Handle::Callback
{
   public:

      CLoggingCallbackTimerHandleCallback();
   
      bool WaitForTimer(
         DWORD timeoutMillis);

   private:

      // Implement CCallbackTimer::Handle::Callback

      virtual void OnTimer(
         CCallbackTimer::Handle &hnd,
         DWORD userData);

      CAutoResetEvent m_event;

      // No copies do not implement
      CLoggingCallbackTimerHandleCallback(const CLoggingCallbackTimerHandleCallback &rhs);
      CLoggingCallbackTimerHandleCallback &operator=(const CLoggingCallbackTimerHandleCallback &rhs);
};

} // End of namespace Mock
} // End of namespace Win32
} // End of namespace AmstelTech 


