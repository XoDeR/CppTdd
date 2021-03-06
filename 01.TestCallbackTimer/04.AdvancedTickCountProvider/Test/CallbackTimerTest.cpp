#include "CallbackTimerTest.h"

#include "../../Tools/CallbackTimer.h"

#include "../Mock/LoggingCallbackTimerHandleCallback.h"
#include "../Mock/MockTickCountProvider.h"

#include "../../Tools/Utils.h"

#include "../../TestTools/TestException.h"

using AmstelTech::Test::CTestException;
using AmstelTech::Win32::Output;
using AmstelTech::Win32::_tstring;
using AmstelTech::Win32::Mock::CLoggingCallbackTimerHandleCallback;
using AmstelTech::Win32::Mock::CMockTickCountProvider;

namespace AmstelTech 
{
	
namespace Win32 
{
	
namespace Test 
{
	
///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

static DWORD s_delay = 1000;
//static DWORD s_delay = INFINITE;

///////////////////////////////////////////////////////////////////////////////
// CCallbackTimerTest
///////////////////////////////////////////////////////////////////////////////

void CCallbackTimerTest::TestAll()
{
	TestConstruct();
	TestTimer();
	TestMultipleTimers();
	// TestCancelTimer();
	// TestTickCountWrap();
}

void CCallbackTimerTest::TestConstruct()
{
   const _tstring functionName = _T("CCallbackTimerTest::TestConstruct");
   Output(functionName + _T(" - start"));
   CCallbackTimer timer;
   CMockTickCountProvider tickProvider;
   CCallbackTimer timer2(tickProvider);
   THROW_ON_FAILURE(functionName, true == tickProvider.AllowCalls(1, s_delay));
   Output(functionName + _T(" - stop"));
}

void CCallbackTimerTest::TestTimer()
{
   const _tstring functionName = _T("CCallbackTimerTest::TestTimer");
   
   Output(functionName + _T(" - start"));

   CMockTickCountProvider tickProvider;

   tickProvider.SetTickCount(1000);

   CCallbackTimer timer(tickProvider);

   CMockTickCountProvider::AutoRelease releaser(tickProvider);

   THROW_ON_FAILURE(functionName, true == tickProvider.AllowCalls(1, s_delay));

   tickProvider.CheckResult(_T("|GetTickCount: Another Thread: 1000|"));

   CLoggingCallbackTimerHandleCallback callback;

   CCallbackTimer::Handle handle(callback);

   timer.SetTimer(handle, 100, 1);

   tickProvider.CheckResult(_T("|GetTickCount: Main Thread: 1000|"));

   THROW_ON_FAILURE(functionName, true == tickProvider.AllowCalls(1, s_delay));

   tickProvider.CheckResult(_T("|GetTickCount: Another Thread: 1000|"));

   THROW_ON_FAILURE(functionName, true == tickProvider.WaitForBlockedCall(s_delay));

   // Prove that time is standing still
   THROW_ON_FAILURE(functionName, false == callback.WaitForTimer(0));

   callback.CheckResult(_T("|"));

   tickProvider.SetTickCount(1100);

   THROW_ON_FAILURE(functionName, true == tickProvider.AllowCalls(1, s_delay));

   tickProvider.CheckResult(_T("|GetTickCount: Another Thread: 1100|"));

   THROW_ON_FAILURE(functionName, true == callback.WaitForTimer(s_delay));

   callback.CheckResult(_T("|OnTimer: 1|"));

   Output(functionName + _T(" - stop"));
}

void CCallbackTimerTest::TestMultipleTimers()
{
   const _tstring functionName = _T("CCallbackTimerTest::TestMultipleTimers");
   
   Output(functionName + _T(" - start"));

   CMockTickCountProvider tickProvider;

   tickProvider.SetTickCount(1000);

   CCallbackTimer timer(tickProvider);

   CMockTickCountProvider::AutoRelease releaser(tickProvider);

   THROW_ON_FAILURE(functionName, true == tickProvider.AllowCalls(1, s_delay));

   tickProvider.CheckResult(_T("|GetTickCount: Another Thread: 1000|"));

   CLoggingCallbackTimerHandleCallback callback1;

   CCallbackTimer::Handle handle1(callback1);

   timer.SetTimer(handle1, 100, 1);

   tickProvider.CheckResult(_T("|GetTickCount: Main Thread: 1000|"));

   THROW_ON_FAILURE(functionName, true == tickProvider.AllowCalls(1, s_delay));

   tickProvider.CheckResult(_T("|GetTickCount: Another Thread: 1000|"));

   THROW_ON_FAILURE(functionName, true == tickProvider.WaitForBlockedCall(s_delay));
///
   CLoggingCallbackTimerHandleCallback callback2;

   CCallbackTimer::Handle handle2(callback2);

   timer.SetTimer(handle2, 200, 2);

   tickProvider.CheckResult(_T("|GetTickCount: Main Thread: 1000|"));

   THROW_ON_FAILURE(functionName, true == tickProvider.AllowCalls(1, s_delay));

   tickProvider.CheckResult(_T("|GetTickCount: Another Thread: 1000|"));

   THROW_ON_FAILURE(functionName, true == tickProvider.WaitForBlockedCall(s_delay));
///
   CLoggingCallbackTimerHandleCallback callback3;

   CCallbackTimer::Handle handle3(callback3);

   timer.SetTimer(handle3, 150, 3);

   tickProvider.CheckResult(_T("|GetTickCount: Main Thread: 1000|"));

   THROW_ON_FAILURE(functionName, true == tickProvider.AllowCalls(1, s_delay));

   tickProvider.CheckResult(_T("|GetTickCount: Another Thread: 1000|"));

   THROW_ON_FAILURE(functionName, true == tickProvider.WaitForBlockedCall(s_delay));

   CLoggingCallbackTimerHandleCallback callback4;

   CCallbackTimer::Handle handle4(callback4);

   timer.SetTimer(handle4, 150, 4);

   tickProvider.CheckResult(_T("|GetTickCount: Main Thread: 1000|"));

   THROW_ON_FAILURE(functionName, true == tickProvider.AllowCalls(1, s_delay));

   tickProvider.CheckResult(_T("|GetTickCount: Another Thread: 1000|"));

   THROW_ON_FAILURE(functionName, true == tickProvider.WaitForBlockedCall(s_delay));

   // Prove that time is standing still
   THROW_ON_FAILURE(functionName, false == callback1.WaitForTimer(0));
   THROW_ON_FAILURE(functionName, false == callback2.WaitForTimer(0));
   THROW_ON_FAILURE(functionName, false == callback3.WaitForTimer(0));
   THROW_ON_FAILURE(functionName, false == callback4.WaitForTimer(0));

   callback1.CheckResult(_T("|"));
   callback2.CheckResult(_T("|"));
   callback3.CheckResult(_T("|"));
   callback4.CheckResult(_T("|"));

   tickProvider.SetTickCount(1100);

   THROW_ON_FAILURE(functionName, true == tickProvider.AllowCalls(1, s_delay));

   tickProvider.CheckResult(_T("|GetTickCount: Another Thread: 1100|"));

   THROW_ON_FAILURE(functionName, true == tickProvider.WaitForBlockedCall(s_delay));

   THROW_ON_FAILURE(functionName, true  == callback1.WaitForTimer(s_delay));
   THROW_ON_FAILURE(functionName, false == callback2.WaitForTimer(0));
   THROW_ON_FAILURE(functionName, false == callback3.WaitForTimer(0));
   THROW_ON_FAILURE(functionName, false == callback4.WaitForTimer(0));

   callback1.CheckResult(_T("|OnTimer: 1|"));
   callback2.CheckResult(_T("|"));
   callback3.CheckResult(_T("|"));
   callback4.CheckResult(_T("|"));

   tickProvider.SetTickCount(1160);

   THROW_ON_FAILURE(functionName, true == tickProvider.AllowCalls(1, s_delay));

   tickProvider.CheckResult(_T("|GetTickCount: Another Thread: 1160|"));

   THROW_ON_FAILURE(functionName, true == tickProvider.WaitForBlockedCall(s_delay));

   THROW_ON_FAILURE(functionName, false == callback1.WaitForTimer(0));
   THROW_ON_FAILURE(functionName, false == callback2.WaitForTimer(0));
   THROW_ON_FAILURE(functionName, true  == callback3.WaitForTimer(s_delay));
   THROW_ON_FAILURE(functionName, true  == callback4.WaitForTimer(s_delay));

   callback1.CheckResult(_T("|"));
   callback2.CheckResult(_T("|"));
   callback3.CheckResult(_T("|OnTimer: 3|"));
   callback4.CheckResult(_T("|OnTimer: 4|"));

   tickProvider.SetTickCount(1201);

   THROW_ON_FAILURE(functionName, true == tickProvider.AllowCalls(1, s_delay));

   tickProvider.CheckResult(_T("|GetTickCount: Another Thread: 1201|"));

   // No more timers pending so the thread goes into an infinite wait until new timers are added.

   THROW_ON_FAILURE(functionName, false == callback1.WaitForTimer(0));
   THROW_ON_FAILURE(functionName, true  == callback2.WaitForTimer(s_delay));
   THROW_ON_FAILURE(functionName, false == callback3.WaitForTimer(0));
   THROW_ON_FAILURE(functionName, false == callback4.WaitForTimer(0));

   callback1.CheckResult(_T("|"));
   callback2.CheckResult(_T("|OnTimer: 2|"));
   callback3.CheckResult(_T("|"));
   callback4.CheckResult(_T("|"));

   Output(functionName + _T(" - stop"));
}

} // End of namespace Test
} // End of namespace Win32
} // End of namespace AmstelTech 