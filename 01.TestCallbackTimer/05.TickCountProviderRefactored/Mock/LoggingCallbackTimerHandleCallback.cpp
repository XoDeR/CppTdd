#include "LoggingCallbackTimerHandleCallback.h"

#include "Tools/Utils.h"

#include "TestTools/TestException.h"

using AmstelTech::Test::CTestException;

using AmstelTech::Win32::Output;
using AmstelTech::Win32::_tstring;

namespace AmstelTech 
{
	
namespace Win32 
{
	
namespace Mock 
{

///////////////////////////////////////////////////////////////////////////////
// CLoggingCallbackTimerHandleCallback
///////////////////////////////////////////////////////////////////////////////

CLoggingCallbackTimerHandleCallback::CLoggingCallbackTimerHandleCallback()
{

}

void CLoggingCallbackTimerHandleCallback::OnTimer(
   CCallbackTimer::Handle &hnd,
   DWORD userData)
{
   LogMessage(_T("OnTimer: ") + ToString(userData));

   m_event.Set();
}

bool CLoggingCallbackTimerHandleCallback::WaitForTimer(
   DWORD timeoutMillis)
{
   return m_event.Wait(timeoutMillis);
}

} // End of namespace Mock
} // End of namespace Win32
} // End of namespace AmstelTech 

