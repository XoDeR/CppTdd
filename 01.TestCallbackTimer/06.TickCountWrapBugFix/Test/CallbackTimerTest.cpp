#include "CallbackTimerTest.h"

#include "../../Tools/CallbackTimer.h"

#include "../Mock/LoggingCallbackTimerHandle.h"
#include "../Mock/MockTickCountProvider.h"
#include "../Mock/TestCallbackTimer.h"

#include "../../Tools/Utils.h"

#include "../../TestTools/TestException.h"

using AmstelTech::Test::CTestException;

using AmstelTech::Win32::Output;
using AmstelTech::Win32::_tstring;

using AmstelTech::Win32::Mock::CLoggingCallbackTimerHandle;
using AmstelTech::Win32::Mock::CMockTickCountProvider;
using AmstelTech::Win32::Mock::CTestCallbackTimer;

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
	TestCancelTimer();
	TestTickCountWrap();
}

void CCallbackTimerTest::TestConstruct()
{
   const _tstring functionName = _T("CCallbackTimerTest::TestConstruct");
   Output(functionName + _T(" - start"));
   CCallbackTimer timer;
   CMockTickCountProvider tickProvider;
   CCallbackTimer timer2(tickProvider);
   THROW_ON_FAILURE(functionName, true == tickProvider.AllowCalls(1, s_delay));
   CTestCallbackTimer timer3(1000, s_delay);
   Output(functionName + _T(" - stop"));
}

void CCallbackTimerTest::TestTimer()
{
   const _tstring functionName = _T("CCallbackTimerTest::TestTimer");
   
   Output(functionName + _T(" - start"));

   CTestCallbackTimer timer(1000, s_delay);

   CLoggingCallbackTimerHandle handle;

   timer.SetTimerAndWait(handle, 100, 1);

   // Prove that time is standing still
   THROW_ON_FAILURE(functionName, false == handle.WaitForTimer(0));

   handle.CheckResult(_T("|"));

   timer.SetTickCountAndWait(1100, false);

   THROW_ON_FAILURE(functionName, true == handle.WaitForTimer(s_delay));

   handle.CheckResult(_T("|OnTimer: 1|"));

   Output(functionName + _T(" - stop"));
}

void CCallbackTimerTest::TestMultipleTimers()
{
   const _tstring functionName = _T("CCallbackTimerTest::TestMultipleTimers");
   
   Output(functionName + _T(" - start"));

   CTestCallbackTimer timer(1000, s_delay);

   CLoggingCallbackTimerHandle handle1;
   CLoggingCallbackTimerHandle handle2;
   CLoggingCallbackTimerHandle handle3;
   CLoggingCallbackTimerHandle handle4;
   CLoggingCallbackTimerHandle handle5;
   CLoggingCallbackTimerHandle handle6;

   timer.SetTimerAndWait(handle1, 300, 1);
   timer.SetTimerAndWait(handle2, 100, 2);
   timer.SetTimerAndWait(handle3, 200, 3);
   timer.SetTimerAndWait(handle4, 150, 4);
   timer.SetTimerAndWait(handle5, 150, 5);
   timer.SetTimerAndWait(handle6, 160, 6);

   // Prove that time is standing still

   handle1.CheckTimerNotExpired();
   handle2.CheckTimerNotExpired();
   handle3.CheckTimerNotExpired();
   handle4.CheckTimerNotExpired();
   handle5.CheckTimerNotExpired();
   handle6.CheckTimerNotExpired();

   timer.SetTickCountAndWait(1100, true);

   handle1.CheckTimerNotExpired();
   handle2.CheckTimerExpired(2, s_delay);
   handle3.CheckTimerNotExpired();
   handle4.CheckTimerNotExpired();
   handle5.CheckTimerNotExpired();
   handle6.CheckTimerNotExpired();

   timer.SetTickCountAndWait(1155, true);

   handle1.CheckTimerNotExpired();
   handle2.CheckTimerNotExpired();
   handle3.CheckTimerNotExpired();
   handle4.CheckTimerExpired(4, s_delay);
   handle5.CheckTimerExpired(5, s_delay);
   handle6.CheckTimerNotExpired();

   timer.SetTickCountAndWait(1201, true);

   handle1.CheckTimerNotExpired();
   handle2.CheckTimerNotExpired();
   handle3.CheckTimerExpired(3, s_delay);
   handle4.CheckTimerNotExpired();
   handle5.CheckTimerNotExpired();
   handle6.CheckTimerExpired(6, s_delay);

   timer.SetTickCountAndWait(1300, false);

   handle1.CheckTimerExpired(1, s_delay);
   handle2.CheckTimerNotExpired();
   handle3.CheckTimerNotExpired();
   handle4.CheckTimerNotExpired();
   handle5.CheckTimerNotExpired();
   handle6.CheckTimerNotExpired();

   timer.SetTimerAndWait(handle1, 100, 1);
   timer.SetTimerAndWait(handle2, 200, 2);

   handle1.CheckTimerNotExpired();
   handle2.CheckTimerNotExpired();

   timer.SetTickCountAndWait(1350, true);

   handle1.CheckTimerNotExpired();
   handle2.CheckTimerNotExpired();

   timer.SetTickCountAndWait(1400, true);

   handle1.CheckTimerExpired(1, s_delay);
   handle2.CheckTimerNotExpired();

   timer.SetTickCountAndWait(1400, true);

   handle1.CheckTimerNotExpired();
   handle2.CheckTimerNotExpired();

   timer.SetTickCountAndWait(1600, false);

   handle1.CheckTimerNotExpired();
   handle2.CheckTimerExpired(2, s_delay);

   Output(functionName + _T(" - stop"));
}

void CCallbackTimerTest::TestCancelTimer()
{
   const _tstring functionName = _T("CCallbackTimerTest::TestCancelTimer");
   
   Output(functionName + _T(" - start"));

   CTestCallbackTimer timer(1000, s_delay);

   CLoggingCallbackTimerHandle handle1;
   CLoggingCallbackTimerHandle handle2;
   CLoggingCallbackTimerHandle handle3;
   CLoggingCallbackTimerHandle handle4;

   timer.SetTimerAndWait(handle1, 100, 1);
   timer.SetTimerAndWait(handle2, 200, 2);
   timer.SetTimerAndWait(handle3, 150, 3);
   timer.SetTimerAndWait(handle4, 150, 4);

   // Prove that time is standing still

   handle1.CheckTimerNotExpired();
   handle2.CheckTimerNotExpired();
   handle3.CheckTimerNotExpired();
   handle4.CheckTimerNotExpired();

   timer.SetTickCountAndWait(1100, true);

   handle1.CheckTimerExpired(1, s_delay);
   handle2.CheckTimerNotExpired();
   handle3.CheckTimerNotExpired();
   handle4.CheckTimerNotExpired();

   THROW_ON_FAILURE(functionName, true == timer.CancelTimer(handle4));
   THROW_ON_FAILURE(functionName, false == timer.CancelTimer(handle1));

   timer.SetTickCountAndWait(1160, true);

   handle1.CheckTimerNotExpired();
   handle2.CheckTimerNotExpired();
   handle3.CheckTimerExpired(3, s_delay);
   handle4.CheckTimerNotExpired();

   timer.SetTickCountAndWait(1201, false);

   handle1.CheckTimerNotExpired();
   handle2.CheckTimerExpired(2, s_delay);
   handle3.CheckTimerNotExpired();
   handle4.CheckTimerNotExpired();

   Output(functionName + _T(" - stop"));
}

void CCallbackTimerTest::TestTickCountWrap()
{
   const _tstring functionName = _T("CCallbackTimerTest::TestTickCountWrap");
   
   Output(functionName + _T(" - start"));

   const DWORD rollOver = 0;
   const DWORD beforeRollOver = rollOver - 1000;
   const DWORD justBeforeRollOver = rollOver - 1;
   const DWORD justAfterRollOver = rollOver + 1;

   CTestCallbackTimer timer(beforeRollOver, s_delay);

   CLoggingCallbackTimerHandle handle1;
   CLoggingCallbackTimerHandle handle2;
   CLoggingCallbackTimerHandle handle3;

   timer.SetTimerAndWait(handle1, 900, 1);
   timer.SetTimerAndWait(handle2, 1000, 2);
   timer.SetTimerAndWait(handle3, 1100, 3);

   // Prove that time is standing still

   handle1.CheckTimerNotExpired();
   handle2.CheckTimerNotExpired();
   handle3.CheckTimerNotExpired();

   timer.SetTickCountAndWait(justBeforeRollOver, true);

   handle1.CheckTimerExpired(1, s_delay);
   handle2.CheckTimerNotExpired();
   handle3.CheckTimerNotExpired();

   timer.SetTickCountAndWait(rollOver, true);

   handle1.CheckTimerNotExpired();
   handle2.CheckTimerExpired(2, s_delay);
   handle3.CheckTimerNotExpired();

   timer.SetTickCountAndWait(justAfterRollOver, true);

   handle1.CheckTimerNotExpired();
   handle2.CheckTimerNotExpired();
   handle3.CheckTimerNotExpired();

   timer.SetTickCountAndWait(2000, false);

   handle1.CheckTimerNotExpired();
   handle2.CheckTimerNotExpired();
   handle3.CheckTimerExpired(3, s_delay);

   // now, lets see what happens if we step over the rollover point. 

   const DWORD wayBeforeRollOver = rollOver - 100000;

   timer.SetTickCount(wayBeforeRollOver);

   // Since there are 99999 ticks to go until roll over the timer loop wont 
   // spin and block, it will wait on the event...

   timer.SetTimerAndWait(handle1, 100001, 1, false);
   timer.SetTimerAndWait(handle2, 101000, 2, false);
   timer.SetTimerAndWait(handle3, 102000, 2, false);

   handle1.CheckTimerNotExpired();
   handle2.CheckTimerNotExpired();
   handle3.CheckTimerNotExpired();

   const DWORD wayAfterRollOver = rollOver + 100000;

   // the timer loop is still waiting on the event, we've moved time faster than normal,
   // so we need to force the loop to check the time again early, we do this by cancelling
   // a new timer.

   timer.SetTickCount(wayAfterRollOver);

   timer.CancelTimer(handle3);

   handle1.CheckTimerExpired(1, s_delay);
   handle2.CheckTimerExpired(2, s_delay);
   handle2.CheckTimerNotExpired();

   Output(functionName + _T(" - stop"));
}

} // End of namespace Test
} // End of namespace Win32
} // End of namespace AmstelTech 