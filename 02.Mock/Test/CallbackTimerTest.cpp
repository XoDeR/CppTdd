#include "CallbackTimerTest.h"

#include "../../Tools/CallbackTimer.h"
#include "../Mock/LoggingCallbackTimerHandleCallback.h"

#include "../../Tools/Utils.h"
#include "../../TestTools/TestException.h"

using AmstelTech::Test::CTestException;
using AmstelTech::Win32::Output;
using AmstelTech::Win32::_tstring;
using AmstelTech::Win32::Mock::CLoggingCallbackTimerHandleCallback;

namespace AmstelTech 
{
namespace Win32 
{
namespace Test 
{

void CCallbackTimerTest::TestAll()
{
   TestConstruct();
   TestTimer();
}

void CCallbackTimerTest::TestConstruct()
{
   const _tstring functionName = _T("CCallbackTimerTest::TestConstruct");
   Output(functionName + _T(" - start"));
   CCallbackTimer timer;
   Output(functionName + _T(" - stop"));
}

void CCallbackTimerTest::TestTimer()
{
   const _tstring functionName = _T("CCallbackTimerTest::TestTimer");
   Output(functionName + _T(" - start"));
   CCallbackTimer timer;
   CLoggingCallbackTimerHandleCallback callback;
   CCallbackTimer::Handle handle(callback);
   timer.SetTimer(handle, 100, 1);
   THROW_ON_FAILURE(functionName, true == callback.WaitForTimer(200));
   callback.CheckResult(_T("|OnTimer: 1|"));
   Output(functionName + _T(" - stop"));
}

} // End of namespace Test
} // End of namespace Win32
} // End of namespace AmstelTech 