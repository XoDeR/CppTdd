#include "ThreadedCallbackTimerQueueTest.h"

#include "../../ThreadedCallbackTimerQueue.h"

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
// CThreadedCallbackTimerQueueTest
///////////////////////////////////////////////////////////////////////////////

void CThreadedCallbackTimerQueueTest::TestAll()
{
   TestConstruct();
   TestTimer();
   TestMultipleTimers();
}

void CThreadedCallbackTimerQueueTest::TestConstruct()
{
   const _tstring functionName = _T("CThreadedCallbackTimerQueueTest::TestConstruct");
   
   Output(functionName + _T(" - start"));

   CThreadedCallbackTimerQueue timerQueue;

   CMockTickCountProvider tickProvider;

   CThreadedCallbackTimerQueue timerQueue2(tickProvider);

   tickProvider.CheckResult(_T("|"));

   Output(functionName + _T(" - stop"));
}

void CThreadedCallbackTimerQueueTest::TestTimer()
{
   const _tstring functionName = _T("CThreadedCallbackTimerQueueTest::TestTimer");
   
   Output(functionName + _T(" - start"));

   CThreadedCallbackTimerQueue timerQueue;

   CLoggingCallbackTimer timer;

   timerQueue.SetTimer(timer, 500, 1);

   Sleep(1000);

   timer.CheckResult(_T("|OnTimer: 1|"));

   Output(functionName + _T(" - stop"));
}

void CThreadedCallbackTimerQueueTest::TestMultipleTimers()
{
   const _tstring functionName = _T("CThreadedCallbackTimerQueueTest::TestMultipleTimers");
   
   Output(functionName + _T(" - start"));

   CThreadedCallbackTimerQueue timerQueue;

   CLoggingCallbackTimer timer;

   timerQueue.SetTimer(timer, 500, 1);
   timerQueue.SetTimer(timer, 1500, 2);
   timerQueue.SetTimer(timer, 300, 3);

   Sleep(1000);

   timer.CheckResult(_T("|OnTimer: 3|OnTimer: 1|"));

   timerQueue.SetTimer(timer, 800, 4);
   timerQueue.SetTimer(timer, 200, 5);
   timerQueue.SetTimer(timer, 2000, 6);

   Sleep(1000);

   timer.CheckResult(_T("|OnTimer: 5|OnTimer: 2|OnTimer: 4|"));

   Sleep(1500);

   timer.CheckResult(_T("|OnTimer: 6|"));

   Output(functionName + _T(" - stop"));
}

} // End of namespace Test
} // End of namespace Win32
} // End of namespace AmstelTech