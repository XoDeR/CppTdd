#pragma warning(disable: 4355)   // 'this' used in base member initialiser list

#include "LoggingCallbackTimerHandle.h"

#include "../../Tools/Utils.h"

#include "../../TestTools/TestException.h"

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
// CLoggingCallbackTimerHandle
///////////////////////////////////////////////////////////////////////////////

CLoggingCallbackTimerHandle::CLoggingCallbackTimerHandle()
   :  CCallbackTimer::Handle(static_cast<CCallbackTimer::Handle::Callback&>(*this))
{

}

void CLoggingCallbackTimerHandle::OnTimer(
   CCallbackTimer::Handle &hnd,
   DWORD userData)
{
   LogMessage(_T("OnTimer: ") + ToString(userData));

   m_event.Set();
}

bool CLoggingCallbackTimerHandle::WaitForTimer(
   DWORD timeoutMillis)
{
   return m_event.Wait(timeoutMillis);
}

void CLoggingCallbackTimerHandle::CheckTimerNotExpired()
{
   if (WaitForTimer(0))
   {
      throw CException(_T("CLoggingCallbackTimerHandle::CheckTimerNotExpired()"), _T("Timer has expired and it shouldn't have done"));
   }

   CheckResult(_T("|"));
}

void CLoggingCallbackTimerHandle::CheckTimerExpired(
   const DWORD userData,
   const DWORD timeoutMillis)
{
   const _tstring userDataAsString = ToString(userData);

   if (!WaitForTimer(timeoutMillis))
   {
      throw CException(_T("CLoggingCallbackTimerHandle::CheckTimerExpired()"), _T("Timer has not expired and it should have: ") + userDataAsString);
   }

   CheckResult(_T("|OnTimer: ") + userDataAsString + _T("|"));
}

} // End of namespace Mock
} // End of namespace Win32
} // End of namespace AmstelTech