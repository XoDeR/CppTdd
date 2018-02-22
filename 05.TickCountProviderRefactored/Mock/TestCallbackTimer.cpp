#pragma warning(disable: 4355)   // 'this' used in base member initialiser list

#include "TestCallbackTimer.h"

#include "../../Tools/Exception.h"
#include "../../Tools/Utils.h"

namespace AmstelTech 
{
	
namespace Win32 
{
	
namespace Mock 
{

///////////////////////////////////////////////////////////////////////////////
// CTestCallbackTimer
///////////////////////////////////////////////////////////////////////////////

CTestCallbackTimer::CTestCallbackTimer(
   const DWORD tickCount,
   const DWORD operationTimeoutMillis)
   :  CMockTickCountProvider(tickCount),
      CCallbackTimer(static_cast<IProvideTickCount &>(*this)),
      m_operationTimeoutMillis(operationTimeoutMillis)
{
   if (!AllowCalls(1, m_operationTimeoutMillis))
   {
      throw CException(_T("CTestCallbackTimer::CTestCallbackTimer()"), _T("AllowCalls() failed"));
   }

   m_tickCountAsString = ToString(tickCount);

   const _tstring expectedResult = _T("|GetTickCount: Another Thread: ") + m_tickCountAsString + _T("|");

   CheckResult(expectedResult);
}

CTestCallbackTimer::~CTestCallbackTimer()
{
   AllowCalls(1000);      
}

void CTestCallbackTimer::SetTimerAndWait(
   CCallbackTimer::Handle &handle,
   const DWORD timeoutMillis,
   const DWORD userData)
{
   SetTimer(handle, timeoutMillis, userData);

   if (!AllowCalls(1, m_operationTimeoutMillis))
   {
      throw CException(_T("CTestCallbackTimer::SetTimerAndWait()"), _T("AllowCalls() failed"));
   }
   
   if (!WaitForBlockedCall(m_operationTimeoutMillis))
   {
      throw CException(_T("CTestCallbackTimer::SetTimerAndWait()"), _T("WaitForBlockedCall() failed"));
   }

   const _tstring expectedResult = _T("|GetTickCount: Main Thread: ") + m_tickCountAsString + _T("|GetTickCount: Another Thread: " + m_tickCountAsString + _T("|"));

   CheckResult(expectedResult);
}

void CTestCallbackTimer::SetTickCountAndWait(
   const DWORD tickCount,
   const bool waitForBlock)
{
   m_tickCountAsString = ToString(tickCount);

   SetTickCount(tickCount);

   if (!AllowCalls(1, m_operationTimeoutMillis))
   {
      throw CException(_T("CTestCallbackTimer::SetTickCountAndWait()"), _T("AllowCalls() failed"));
   }

   const _tstring expectedResult = _T("|GetTickCount: Another Thread: ") + m_tickCountAsString + _T("|");

   CheckResult(expectedResult);

   if (waitForBlock && !WaitForBlockedCall(m_operationTimeoutMillis))
   {
      throw CException(_T("CTestCallbackTimer::SetTickCountAndWait()"), _T("WaitForBlockedCall() failed"));
   }
}

} // End of namespace Mock
} // End of namespace Win32
} // End of namespace AmstelTech