#include "CallbackTimerQueueTest.h"

#include "../../Tools/CallbackTimerQueue.h"

#include "../Mock/MockTickCountProvider.h"
#include "../Mock/LoggingCallbackTimer.h"

#include "../../Tools/Utils.h"

#include "../../TestTools/TestException.h"

using AmstelTech::Test::CTestException;

using AmstelTech::Win32::Output;
using AmstelTech::Win32::_tstring;

using AmstelTech::Win32::Mock::CMockTickCountProvider;
using AmstelTech::Win32::Mock::CLoggingCallbackTimer;

namespace AmstelTech 
{
	
namespace Win32 
{
	
namespace Test 
{

///////////////////////////////////////////////////////////////////////////////
// CCallbackTimerQueueTest
///////////////////////////////////////////////////////////////////////////////

void CCallbackTimerQueueTest::TestAll()
{
   TestConstruct();
   TestTimer();
   TestCancelTimer();
   TestTickCountWrap();
   TestMaxTimeout();
   TestMultipleTimers();
   TestResetTimer();
}

void CCallbackTimerQueueTest::TestConstruct()
{
   const _tstring functionName = _T("CCallbackTimerQueueTest::TestConstruct");
   
   Output(functionName + _T(" - start"));

   CCallbackTimerQueue timerQueue;

   CMockTickCountProvider tickProvider;

   CCallbackTimerQueue timerQueue2(tickProvider);

   tickProvider.CheckResult(_T("|"));

   Output(functionName + _T(" - stop"));
}

void CCallbackTimerQueueTest::TestTimer()
{
   const _tstring functionName = _T("CCallbackTimerQueueTest::TestTimer");
   
   Output(functionName + _T(" - start"));

   CMockTickCountProvider tickProvider;

   CCallbackTimerQueue timerQueue(tickProvider);

   tickProvider.CheckResult(_T("|"));

   THROW_ON_FAILURE(functionName, INFINITE == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|"));

   CLoggingCallbackTimer timer;

   timerQueue.SetTimer(timer, 100, 1);

   tickProvider.CheckResult(_T("|GetTickCount: 0|"));

   // Prove that time is standing still

   THROW_ON_FAILURE(functionName, 100 == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|GetTickCount: 0|"));
   
   timerQueue.HandleTimeouts();

   tickProvider.CheckResult(_T("|GetTickCount: 0|"));

   timer.CheckResult(_T("|"));

   THROW_ON_FAILURE(functionName, 100 == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|GetTickCount: 0|"));

   tickProvider.SetTickCount(100);

   THROW_ON_FAILURE(functionName, 0 == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|GetTickCount: 100|"));

   timerQueue.HandleTimeouts();

   tickProvider.CheckResult(_T("|GetTickCount: 100|"));

   timer.CheckResult(_T("|OnTimer: 1|"));

   THROW_ON_FAILURE(functionName, INFINITE == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|"));

   Output(functionName + _T(" - stop"));
}

void CCallbackTimerQueueTest::TestCancelTimer()
{
   const _tstring functionName = _T("CCallbackTimerQueueTest::TestCancelTimer");
   
   Output(functionName + _T(" - start"));

   CMockTickCountProvider tickProvider;

   CCallbackTimerQueue timerQueue(tickProvider);

   THROW_ON_FAILURE(functionName, INFINITE == timerQueue.GetNextTimeout());

   CLoggingCallbackTimer timer;

   CCallbackTimerQueue::Handle handle = timerQueue.SetTimer(timer, 100, 1);

   tickProvider.CheckResult(_T("|GetTickCount: 0|"));

   THROW_ON_FAILURE(functionName, 100 == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|GetTickCount: 0|"));
   
   THROW_ON_FAILURE(functionName, true == timerQueue.CancelTimer(handle));

   timer.CheckResult(_T("|"));

   THROW_ON_FAILURE(functionName, INFINITE == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|"));

   THROW_ON_FAILURE(functionName, false == timerQueue.CancelTimer(handle));
   THROW_ON_FAILURE(functionName, false == timerQueue.CancelTimer(handle));

   tickProvider.SetTickCount(100);

   THROW_ON_FAILURE(functionName, INFINITE == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|"));

   timerQueue.HandleTimeouts();

   tickProvider.CheckResult(_T("|"));

   timer.CheckResult(_T("|"));

   Output(functionName + _T(" - stop"));
}

void CCallbackTimerQueueTest::TestTickCountWrap()
{
   const _tstring functionName = _T("CCallbackTimerQueueTest::TestTickCountWrap");
   
   Output(functionName + _T(" - start"));

   const DWORD rollOver = 0;
   const DWORD beforeRollOver = rollOver - 1000;

   CMockTickCountProvider tickProvider(beforeRollOver);

   CCallbackTimerQueue timerQueue(tickProvider);

   tickProvider.CheckResult(_T("|"));

   THROW_ON_FAILURE(functionName, INFINITE == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|"));

   CLoggingCallbackTimer timer;

   timerQueue.SetTimer(timer, 1100, 1);

   const _tstring resultBeforeRollOver = _T("|GetTickCount: ") + ToString(beforeRollOver) + _T("|");

   tickProvider.CheckResult(resultBeforeRollOver);

   THROW_ON_FAILURE(functionName, 1100 == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(resultBeforeRollOver);
   
   timerQueue.HandleTimeouts();

   tickProvider.CheckResult(resultBeforeRollOver);

   timer.CheckResult(_T("|"));

   THROW_ON_FAILURE(functionName, 1100 == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(resultBeforeRollOver);

   tickProvider.SetTickCount(rollOver);

   THROW_ON_FAILURE(functionName, 100 == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|GetTickCount: 0|"));

   timerQueue.HandleTimeouts();

   tickProvider.CheckResult(_T("|GetTickCount: 0|"));

   timer.CheckResult(_T("|"));

   tickProvider.SetTickCount(100);

   THROW_ON_FAILURE(functionName, 0 == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|GetTickCount: 100|"));

   timerQueue.HandleTimeouts();

   tickProvider.CheckResult(_T("|GetTickCount: 100|"));

   timer.CheckResult(_T("|OnTimer: 1|"));

   THROW_ON_FAILURE(functionName, INFINITE == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|"));

   tickProvider.SetTickCount(beforeRollOver);

   THROW_ON_FAILURE(functionName, INFINITE == timerQueue.GetNextTimeout());

   DWORD timeout2 = (0xFFFFFFFE / 4 * 3);

   timerQueue.SetTimer(timer, timeout2, 1);

   tickProvider.CheckResult(resultBeforeRollOver);

   THROW_ON_FAILURE(functionName, timeout2 == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(resultBeforeRollOver);
   
   timerQueue.HandleTimeouts();

   tickProvider.CheckResult(resultBeforeRollOver);

   timer.CheckResult(_T("|"));

   Output(functionName + _T(" - stop"));
}

void CCallbackTimerQueueTest::TestMaxTimeout()
{
   const _tstring functionName = _T("CCallbackTimerQueueTest::TestMaxTimeout");
   
   Output(functionName + _T(" - start"));

   CMockTickCountProvider tickProvider(1000);

   {
      CCallbackTimerQueue timerQueue(tickProvider);

      tickProvider.CheckResult(_T("|"));

      CLoggingCallbackTimer timer;

      const DWORD maxTimeout = (0xFFFFFFFF / 4 * 3);

      CCallbackTimerQueue::Handle handle = timerQueue.SetTimer(timer, maxTimeout, 1);

      tickProvider.CheckResult(_T("|GetTickCount: 1000|"));

      timerQueue.CancelTimer(handle);

      const DWORD minTimeout = 0;

      handle = timerQueue.SetTimer(timer, minTimeout, 1);

      tickProvider.CheckResult(_T("|GetTickCount: 1000|"));

      timerQueue.CancelTimer(handle);

      const DWORD illegalTimeout = maxTimeout + 1;

      THROW_ON_NO_EXCEPTION_3(functionName, timerQueue.SetTimer, timer, illegalTimeout, 1);
   }

   {
      CCallbackTimerQueue timerQueue(1000, tickProvider);

      tickProvider.CheckResult(_T("|"));

      CLoggingCallbackTimer timer;

      const DWORD maxTimeout = 1000;

      CCallbackTimerQueue::Handle handle = timerQueue.SetTimer(timer, maxTimeout, 1);

      tickProvider.CheckResult(_T("|GetTickCount: 1000|"));

      timerQueue.CancelTimer(handle);

      const DWORD minTimeout = 0;

      handle = timerQueue.SetTimer(timer, minTimeout, 1);

      tickProvider.CheckResult(_T("|GetTickCount: 1000|"));

      timerQueue.CancelTimer(handle);

      const DWORD illegalTimeout = maxTimeout + 1;

      THROW_ON_NO_EXCEPTION_3(functionName, timerQueue.SetTimer, timer, illegalTimeout, 1);
   }

   Output(functionName + _T(" - stop"));
}

void CCallbackTimerQueueTest::TestMultipleTimers()
{
   const _tstring functionName = _T("CCallbackTimerQueueTest::TestMultipleTimers");
   
   Output(functionName + _T(" - start"));

   CMockTickCountProvider tickProvider;

   CCallbackTimerQueue timerQueue(tickProvider);

   tickProvider.CheckResult(_T("|"));

   THROW_ON_FAILURE(functionName, INFINITE == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|"));

   CLoggingCallbackTimer timer1;
   CLoggingCallbackTimer timer2;
   CLoggingCallbackTimer timer3;
   CLoggingCallbackTimer timer4;
   CLoggingCallbackTimer timer5;
   CLoggingCallbackTimer timer6;

   timerQueue.SetTimer(timer1, 300, 1);
   timerQueue.SetTimer(timer2, 100, 2);
   timerQueue.SetTimer(timer3, 200, 3);
   timerQueue.SetTimer(timer4, 150, 4);
   timerQueue.SetTimer(timer5, 150, 5);
   timerQueue.SetTimer(timer6, 160, 6);

   tickProvider.CheckResult(_T("|GetTickCount: 0|GetTickCount: 0|GetTickCount: 0|GetTickCount: 0|GetTickCount: 0|GetTickCount: 0|"));

   THROW_ON_FAILURE(functionName, 100 == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|GetTickCount: 0|"));

   timerQueue.HandleTimeouts();

   tickProvider.CheckResult(_T("|GetTickCount: 0|"));

   timer1.CheckResult(_T("|"));
   timer2.CheckResult(_T("|"));
   timer3.CheckResult(_T("|"));
   timer4.CheckResult(_T("|"));
   timer5.CheckResult(_T("|"));
   timer6.CheckResult(_T("|"));

   tickProvider.SetTickCount(100);

   THROW_ON_FAILURE(functionName, 0 == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|GetTickCount: 100|"));

   timerQueue.HandleTimeouts();

   tickProvider.CheckResult(_T("|GetTickCount: 100|"));

   timer1.CheckResult(_T("|"));
   timer2.CheckResult(_T("|OnTimer: 2|"));
   timer3.CheckResult(_T("|"));
   timer4.CheckResult(_T("|"));
   timer5.CheckResult(_T("|"));
   timer6.CheckResult(_T("|"));

   THROW_ON_FAILURE(functionName, 50 == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|GetTickCount: 100|"));

   tickProvider.SetTickCount(155);

   THROW_ON_FAILURE(functionName, 0 == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|GetTickCount: 155|"));

   timerQueue.HandleTimeouts();

   tickProvider.CheckResult(_T("|GetTickCount: 155|"));

   timer1.CheckResult(_T("|"));
   timer2.CheckResult(_T("|"));
   timer3.CheckResult(_T("|"));
   timer4.CheckResult(_T("|OnTimer: 4|"));
   timer5.CheckResult(_T("|OnTimer: 5|"));
   timer6.CheckResult(_T("|"));

   THROW_ON_FAILURE(functionName, 5 == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|GetTickCount: 155|"));

   tickProvider.SetTickCount(201);

   THROW_ON_FAILURE(functionName, 0 == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|GetTickCount: 201|"));

   timerQueue.HandleTimeouts();

   tickProvider.CheckResult(_T("|GetTickCount: 201|"));

   timer1.CheckResult(_T("|"));
   timer2.CheckResult(_T("|"));
   timer3.CheckResult(_T("|OnTimer: 3|"));
   timer4.CheckResult(_T("|"));
   timer5.CheckResult(_T("|"));
   timer6.CheckResult(_T("|OnTimer: 6|"));

   THROW_ON_FAILURE(functionName, 99 == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|GetTickCount: 201|"));

   tickProvider.SetTickCount(300);

   THROW_ON_FAILURE(functionName, 0 == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|GetTickCount: 300|"));

   timerQueue.HandleTimeouts();

   tickProvider.CheckResult(_T("|GetTickCount: 300|"));

   timer1.CheckResult(_T("|OnTimer: 1|"));
   timer2.CheckResult(_T("|"));
   timer3.CheckResult(_T("|"));
   timer4.CheckResult(_T("|"));
   timer5.CheckResult(_T("|"));
   timer6.CheckResult(_T("|"));

   THROW_ON_FAILURE(functionName, INFINITE == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|GetTickCount: 300|"));

//   timerQueue.SetTimer(timer1, 100, 1);
//   timerQueue.SetTimer(timer2, 200, 2);

   Output(functionName + _T(" - stop"));
}

void CCallbackTimerQueueTest::TestResetTimer()
{
   const _tstring functionName = _T("CCallbackTimerQueueTest::TestResetTimer");
   
   Output(functionName + _T(" - start"));

   CMockTickCountProvider tickProvider;

   CCallbackTimerQueue timerQueue(tickProvider);

   CLoggingCallbackTimer timer;

   CCallbackTimerQueue::Handle handle = timerQueue.SetTimer(timer, 100, 1);

   tickProvider.CheckResult(_T("|GetTickCount: 0|"));

   THROW_ON_FAILURE(functionName, 100 == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|GetTickCount: 0|"));
   
   THROW_ON_FAILURE(functionName, true == timerQueue.ResetTimer(handle, timer, 90, 2));

   tickProvider.CheckResult(_T("|GetTickCount: 0|"));

   THROW_ON_FAILURE(functionName, 90 == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|GetTickCount: 0|"));

   tickProvider.SetTickCount(90);

   THROW_ON_FAILURE(functionName, 0 == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|GetTickCount: 90|"));

   timerQueue.HandleTimeouts();

   tickProvider.CheckResult(_T("|GetTickCount: 90|"));

   timer.CheckResult(_T("|OnTimer: 2|"));

   THROW_ON_FAILURE(functionName, INFINITE == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|"));

   THROW_ON_FAILURE(functionName, false == timerQueue.ResetTimer(handle, timer, 110, 3));

   tickProvider.CheckResult(_T("|GetTickCount: 90|"));

   THROW_ON_FAILURE(functionName, 110 == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|GetTickCount: 90|"));

   tickProvider.SetTickCount(200);

   THROW_ON_FAILURE(functionName, 0 == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|GetTickCount: 200|"));

   timerQueue.HandleTimeouts();

   tickProvider.CheckResult(_T("|GetTickCount: 200|"));

   timer.CheckResult(_T("|OnTimer: 3|"));

   THROW_ON_FAILURE(functionName, INFINITE == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|"));

   Output(functionName + _T(" - stop"));
}

} // End of namespace Test
} // End of namespace Win32
} // End of namespace AmstelTech