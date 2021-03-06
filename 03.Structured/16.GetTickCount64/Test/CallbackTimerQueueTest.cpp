#include "CallbackTimerQueueTest.h"

#include "../../Tools/CallbackTimerQueue.h"

#include "../Mock/MockTickCountProvider.h"
#include "../Mock/LoggingCallbackTimer.h"

#include "../../Tools/Utils.h"
#include "../../Tools/DebugTrace.h"

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
// Static helper functions
///////////////////////////////////////////////////////////////////////////////

static CCallbackTimerQueue::Handle CreateAndSetTimer(
   CCallbackTimerQueue &timerQueue, 
   CCallbackTimerQueue::Timer &timer, 
   const Milliseconds timeout,
   const CCallbackTimerQueue::UserData userData);

///////////////////////////////////////////////////////////////////////////////
// CCallbackTimerQueueTest
///////////////////////////////////////////////////////////////////////////////

void CCallbackTimerQueueTest::TestAll()
{
   TestConstruct();
   TestCreateTimer();
   TestDestroyTimer();
   TestTimer();
   TestCancelTimer();
   TestCancelExpiredTimer();
   TestResetTimer();
   TestTickCountWrap();
   TestTickCountWrap2();
   TestTickCountWrap3();
   TestGetMaxTimeout();
   TestSetTimerPastTickCount64CountWrap();
   TestMaxTimeout();
   TestMultipleTimers();
   TestOneShotTimer();
   TestActiveTimersAtDestructionTime();
}

void CCallbackTimerQueueTest::TestConstruct()
{
   const _tstring functionName = _T("CCallbackTimerQueueTest::TestConstruct");
   
   Output(functionName + _T(" - start"));

   CCallbackTimerQueue timerQueue;

   CMockTickCountProvider tickProvider;

   CCallbackTimerQueue timerQueue2(tickProvider);

   tickProvider.CheckResult(_T("|GetTickCount: 0|"));       // creating a queue sets an 
                                                            // internal maintenance timer
   Output(functionName + _T(" - stop"));
}

void CCallbackTimerQueueTest::TestCreateTimer()
{
   const _tstring functionName = _T("CCallbackTimerQueueTest::TestCreateTimer");
   
   Output(functionName + _T(" - start"));

   CMockTickCountProvider tickProvider;

   CCallbackTimerQueue timerQueue(tickProvider);

   tickProvider.CheckResult(_T("|GetTickCount: 0|"));       // creating a queue sets an 
                                                            // internal maintenance timer

   CCallbackTimerQueue::Handle handle = timerQueue.CreateTimer();

   tickProvider.CheckResult(_T("|"));

   THROW_ON_FAILURE(functionName, CCallbackTimerQueue::InvalidHandleValue != handle);

   Output(functionName + _T(" - stop"));
}

void CCallbackTimerQueueTest::TestDestroyTimer()
{
   const _tstring functionName = _T("CCallbackTimerQueueTest::TestDestroyTimer");
   
   Output(functionName + _T(" - start"));

   CMockTickCountProvider tickProvider;

   CCallbackTimerQueue timerQueue(tickProvider);

   tickProvider.CheckResult(_T("|GetTickCount: 0|"));       // creating a queue sets an 
                                                            // internal maintenance timer

   CCallbackTimerQueue::Handle handle = timerQueue.CreateTimer();

   tickProvider.CheckResult(_T("|"));

   THROW_ON_FAILURE(functionName, CCallbackTimerQueue::InvalidHandleValue != handle);

   CCallbackTimerQueue::Handle handleCopy = handle;

   THROW_ON_FAILURE(functionName, false == timerQueue.DestroyTimer(handle));

   THROW_ON_FAILURE(functionName, CCallbackTimerQueue::InvalidHandleValue == handle);

   tickProvider.CheckResult(_T("|"));

   THROW_ON_NO_EXCEPTION_1(functionName, timerQueue.DestroyTimer, handleCopy);

   tickProvider.CheckResult(_T("|"));

   THROW_ON_NO_EXCEPTION_1(functionName, timerQueue.DestroyTimer, CCallbackTimerQueue::InvalidHandleValue);

   tickProvider.CheckResult(_T("|"));

   Output(functionName + _T(" - stop"));
}

void CCallbackTimerQueueTest::TestTimer()
{
   const _tstring functionName = _T("CCallbackTimerQueueTest::TestTimer");
   
   Output(functionName + _T(" - start"));

   CMockTickCountProvider tickProvider;

   CCallbackTimerQueue timerQueue(tickProvider);

   tickProvider.CheckResult(_T("|GetTickCount: 0|"));       // creating a queue sets an 
                                                            // internal maintenance timer

   THROW_ON_FAILURE(functionName, INFINITE == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|"));

   CLoggingCallbackTimer timer;

   CCallbackTimerQueue::Handle handle = timerQueue.CreateTimer();

   tickProvider.CheckResult(_T("|"));

   THROW_ON_FAILURE(functionName, CCallbackTimerQueue::InvalidHandleValue != handle);

   THROW_ON_FAILURE(functionName, false == timerQueue.SetTimer(handle, timer, 100, 1));

   tickProvider.CheckResult(_T("|GetTickCount: 0|"));

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

   THROW_ON_FAILURE(functionName, false == timerQueue.DestroyTimer(handle));

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

   CCallbackTimerQueue::Handle handle = timerQueue.CreateTimer();

   tickProvider.CheckResult(_T("|GetTickCount: 0|"));       // creating a queue sets an 
                                                            // internal maintenance timer

   THROW_ON_FAILURE(functionName, CCallbackTimerQueue::InvalidHandleValue != handle);

   THROW_ON_FAILURE(functionName, false == timerQueue.SetTimer(handle, timer, 100, 1));

   tickProvider.CheckResult(_T("|GetTickCount: 0|"));

   THROW_ON_FAILURE(functionName, 100 == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|GetTickCount: 0|"));
   
   THROW_ON_FAILURE(functionName, true == timerQueue.CancelTimer(handle));

   timer.CheckResult(_T("|"));

   THROW_ON_FAILURE(functionName, INFINITE == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|"));

   THROW_ON_FAILURE(functionName, false == timerQueue.CancelTimer(handle));

   CCallbackTimerQueue::Handle invalid = 0;

   THROW_ON_NO_EXCEPTION_1(functionName, timerQueue.CancelTimer, invalid);

   tickProvider.SetTickCount(100);

   THROW_ON_FAILURE(functionName, INFINITE == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|"));

   timerQueue.HandleTimeouts();

   tickProvider.CheckResult(_T("|"));

   timer.CheckResult(_T("|"));

   THROW_ON_FAILURE(functionName, false == timerQueue.DestroyTimer(handle));

   Output(functionName + _T(" - stop"));
}

void CCallbackTimerQueueTest::TestCancelExpiredTimer()
{
   const _tstring functionName = _T("CCallbackTimerQueueTest::TestCancelExpiredTimer");
   
   Output(functionName + _T(" - start"));

   CMockTickCountProvider tickProvider;

   CCallbackTimerQueue timerQueue(tickProvider);

   THROW_ON_FAILURE(functionName, INFINITE == timerQueue.GetNextTimeout());

   CLoggingCallbackTimer timer;

   CCallbackTimerQueue::Handle handle = timerQueue.CreateTimer();

   tickProvider.CheckResult(_T("|GetTickCount: 0|"));       // creating a queue sets an 
                                                            // internal maintenance timer

   THROW_ON_FAILURE(functionName, CCallbackTimerQueue::InvalidHandleValue != handle);

   THROW_ON_FAILURE(functionName, false == timerQueue.SetTimer(handle, timer, 100, 1));

   tickProvider.CheckResult(_T("|GetTickCount: 0|"));

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

   THROW_ON_FAILURE(functionName, false == timerQueue.CancelTimer(handle));

   timer.CheckResult(_T("|"));

   THROW_ON_FAILURE(functionName, INFINITE == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|"));

   THROW_ON_FAILURE(functionName, false == timerQueue.DestroyTimer(handle));

   Output(functionName + _T(" - stop"));
}

void CCallbackTimerQueueTest::TestTickCountWrap()
{
   const _tstring functionName = _T("CCallbackTimerQueueTest::TestTickCountWrap");
   
   Output(functionName + _T(" - start"));

   const Milliseconds rollOver = 0;
   const Milliseconds beforeRollOver = rollOver - 1000;

   CMockTickCountProvider tickProvider(beforeRollOver);

   CCallbackTimerQueue timerQueue(tickProvider);

   const _tstring resultBeforeRollOver = _T("|GetTickCount: ") + ToString(beforeRollOver) + _T("|");

   tickProvider.CheckResult(resultBeforeRollOver);          // creating a queue sets an 
                                                            // internal maintenance timer

   THROW_ON_FAILURE(functionName, INFINITE == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|"));

   CLoggingCallbackTimer timer;

   CCallbackTimerQueue::Handle handle = timerQueue.CreateTimer();

   tickProvider.CheckResult(_T("|"));

   THROW_ON_FAILURE(functionName, CCallbackTimerQueue::InvalidHandleValue != handle);

   // Set a single timer for 100ms after the tick count rolls to 0.

   THROW_ON_FAILURE(functionName, false == timerQueue.SetTimer(handle, timer, 1100, 1));

   tickProvider.CheckResult(resultBeforeRollOver);

   THROW_ON_FAILURE(functionName, 1100 == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(resultBeforeRollOver);

   // Check that the timer doesn't go off.

   timerQueue.HandleTimeouts();

   tickProvider.CheckResult(resultBeforeRollOver);

   timer.CheckResult(_T("|"));

   THROW_ON_FAILURE(functionName, 1100 == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(resultBeforeRollOver);

   // Set the time to the point where the tick count rolls over.

   tickProvider.SetTickCount(rollOver);

   THROW_ON_FAILURE(functionName, 100 == timerQueue.GetNextTimeout());

   // Because the count has wrapped the maintenance timer is reset, so two calls to GetTickCount...

   tickProvider.CheckResult(_T("|GetTickCount: 0|GetTickCount: 0|"));      

   // Check that the timer doesn't go off.

   timerQueue.HandleTimeouts();

   tickProvider.CheckResult(_T("|GetTickCount: 0|"));

   timer.CheckResult(_T("|"));

   // Set the tick count to the timeout time.

   tickProvider.SetTickCount(100);

   THROW_ON_FAILURE(functionName, 0 == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|GetTickCount: 100|"));

   // Check that the timer goes off.

   timerQueue.HandleTimeouts();

   tickProvider.CheckResult(_T("|GetTickCount: 100|"));

   timer.CheckResult(_T("|OnTimer: 1|"));

   // Check that there are no more timers to go off.

   THROW_ON_FAILURE(functionName, INFINITE == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|"));

   tickProvider.SetTickCount(beforeRollOver);

   THROW_ON_FAILURE(functionName, INFINITE == timerQueue.GetNextTimeout());

   const Milliseconds timeout2 = timerQueue.GetMaximumTimeout();

   THROW_ON_FAILURE(functionName, false == timerQueue.SetTimer(handle, timer, timeout2, 1));

   tickProvider.CheckResult(resultBeforeRollOver);

   THROW_ON_FAILURE(functionName, timeout2 == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(resultBeforeRollOver);
   
   timerQueue.HandleTimeouts();

   tickProvider.CheckResult(resultBeforeRollOver);

   timer.CheckResult(_T("|"));

   THROW_ON_FAILURE(functionName, true == timerQueue.DestroyTimer(handle));

   Output(functionName + _T(" - stop"));
}

void CCallbackTimerQueueTest::TestTickCountWrap2()
{
   const _tstring functionName = _T("CCallbackTimerQueueTest::TestTickCountWrap2");
   
   Output(functionName + _T(" - start"));

   const Milliseconds rollOver = 0;
   const Milliseconds beforeRollOver = rollOver - 1000;

   CMockTickCountProvider tickProvider(beforeRollOver);

   CCallbackTimerQueue timerQueue(tickProvider);

   const _tstring resultBeforeRollOver = _T("|GetTickCount: ") + ToString(beforeRollOver) + _T("|");

   tickProvider.CheckResult(resultBeforeRollOver);          // creating a queue sets an 
                                                            // internal maintenance timer

   THROW_ON_FAILURE(functionName, INFINITE == timerQueue.GetNextTimeout());

   tickProvider.CheckNoResults();

   CCallbackTimerQueue::Handle handle1 = timerQueue.CreateTimer();

   THROW_ON_FAILURE(functionName, CCallbackTimerQueue::InvalidHandleValue != handle1);

   tickProvider.CheckNoResults();

   CLoggingCallbackTimer timer;

   // Set a timer for 1000ms after the tick count rolls to 0.

   THROW_ON_FAILURE(functionName, false == timerQueue.SetTimer(handle1, timer, 2000, 1));

   tickProvider.CheckResult(resultBeforeRollOver);

   THROW_ON_FAILURE(functionName, 2000 == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(resultBeforeRollOver);

   // Check that the timer doesn't go off.

   timerQueue.HandleTimeouts();

   tickProvider.CheckResult(resultBeforeRollOver);

   timer.CheckNoResults();

   THROW_ON_FAILURE(functionName, 2000 == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(resultBeforeRollOver);

   // Set the time to the point where the tick count rolls over.

   tickProvider.SetTickCount(rollOver);

   THROW_ON_FAILURE(functionName, 1000 == timerQueue.GetNextTimeout());

   // Because the count has wrapped the maintenance timer is reset, so two calls to GetTickCount...

   tickProvider.CheckResult(_T("|GetTickCount: 0|GetTickCount: 0|"));      

   // Check that the timer doesn't go off.

   timerQueue.HandleTimeouts();

   tickProvider.CheckResult(_T("|GetTickCount: 0|"));

   timer.CheckNoResults();

   // Set another timer for 10000 ms time

   CCallbackTimerQueue::Handle handle2 = timerQueue.CreateTimer();

   THROW_ON_FAILURE(functionName, CCallbackTimerQueue::InvalidHandleValue != handle2);

   tickProvider.CheckNoResults();

   THROW_ON_FAILURE(functionName, false == timerQueue.SetTimer(handle2, timer, 10000, 2));

   tickProvider.CheckResult(_T("|GetTickCount: 0|"));

   // Check that the timer goes off.

   timerQueue.HandleTimeouts();

   tickProvider.CheckResult(_T("|GetTickCount: 0|"));

   // Set the tick count to the timeout time.

   tickProvider.SetTickCount(1000);

   THROW_ON_FAILURE(functionName, 0 == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|GetTickCount: 1000|"));

   // Check that the timer goes off.

   timerQueue.HandleTimeouts();

   tickProvider.CheckResult(_T("|GetTickCount: 1000|GetTickCount: 1000|"));

   timer.CheckResult(_T("|OnTimer: 1|"));

   THROW_ON_FAILURE(functionName, 9000 == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|GetTickCount: 1000|"));

   // Set the tick count to the timeout time.

   tickProvider.SetTickCount(10000);

   THROW_ON_FAILURE(functionName, 0 == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|GetTickCount: 10000|"));

   // Check that the timer goes off.

   timerQueue.HandleTimeouts();

   tickProvider.CheckResult(_T("|GetTickCount: 10000|"));

   timer.CheckResult(_T("|OnTimer: 2|"));

   THROW_ON_FAILURE(functionName, INFINITE == timerQueue.GetNextTimeout());

   tickProvider.CheckNoResults();

   THROW_ON_FAILURE(functionName, false == timerQueue.DestroyTimer(handle1));

   THROW_ON_FAILURE(functionName, false == timerQueue.DestroyTimer(handle2));

   Output(functionName + _T(" - stop"));
}

void CCallbackTimerQueueTest::TestTickCountWrap3()
{
   // If we have a timer before the GetTickCount() wrap point that is set but hasn't been 
   // handled and a timer after the wrap point and the tick count wraps and we set a new 
   // timer, the three timers should all go off in the right order...

   const _tstring functionName = _T("CCallbackTimerQueueTest::TestTickCountWrap3");
   
   Output(functionName + _T(" - start"));

   const Milliseconds rollOver = 0;
   const Milliseconds beforeRollOver = rollOver - 1000;

   CMockTickCountProvider tickProvider(beforeRollOver);

   CCallbackTimerQueue timerQueue(tickProvider);

   const _tstring resultBeforeRollOver = _T("|GetTickCount: ") + ToString(beforeRollOver) + _T("|");

   tickProvider.CheckResult(resultBeforeRollOver);          // creating a queue sets an 
                                                            // internal maintenance timer

   THROW_ON_FAILURE(functionName, INFINITE == timerQueue.GetNextTimeout());

   tickProvider.CheckNoResults();

   CLoggingCallbackTimer timer;

   // Set a timer for 100ms before the tick count rolls to 0.

   CCallbackTimerQueue::Handle handle1 = timerQueue.CreateTimer();

   THROW_ON_FAILURE(functionName, CCallbackTimerQueue::InvalidHandleValue != handle1);

   tickProvider.CheckNoResults();

   const Milliseconds firstTimerTime = 900;

   THROW_ON_FAILURE(functionName, false == timerQueue.SetTimer(handle1, timer, firstTimerTime, 1));

   tickProvider.CheckResult(resultBeforeRollOver);

   THROW_ON_FAILURE(functionName, firstTimerTime == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(resultBeforeRollOver);

   // Check that the timer doesn't go off.

   timerQueue.HandleTimeouts();

   tickProvider.CheckResult(resultBeforeRollOver);

   timer.CheckNoResults();

   // Now set a timer for 1000ms after the tick count rolls to 0.

   CCallbackTimerQueue::Handle handle2 = timerQueue.CreateTimer();

   THROW_ON_FAILURE(functionName, CCallbackTimerQueue::InvalidHandleValue != handle2);

   tickProvider.CheckNoResults();

   const Milliseconds secondTimerTime = 2000;

   THROW_ON_FAILURE(functionName, false == timerQueue.SetTimer(handle2, timer, secondTimerTime, 2));

   tickProvider.CheckResult(resultBeforeRollOver);

   THROW_ON_FAILURE(functionName, firstTimerTime == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(resultBeforeRollOver);

   // Check that the timer doesn't go off.

   timerQueue.HandleTimeouts();

   tickProvider.CheckResult(resultBeforeRollOver);

   timer.CheckNoResults();

   THROW_ON_FAILURE(functionName, firstTimerTime == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(resultBeforeRollOver);

   // Set the time to the point where the tick count rolls over.

   tickProvider.SetTickCount(rollOver);

   // the first timer will go off now if we call HandleTimeouts()...

   THROW_ON_FAILURE(functionName, 0 == timerQueue.GetNextTimeout());

   // Because the count has wrapped the maintenance timer is reset, so two calls to GetTickCount...

   tickProvider.CheckResult(_T("|GetTickCount: 0|GetTickCount: 0|"));      

   timer.CheckNoResults();

   // Set another timer for 10000 ms time

   CCallbackTimerQueue::Handle handle3 = timerQueue.CreateTimer();

   THROW_ON_FAILURE(functionName, CCallbackTimerQueue::InvalidHandleValue != handle3);

   tickProvider.CheckNoResults();

   const Milliseconds thirdTimerTime = 10000;

   THROW_ON_FAILURE(functionName, false == timerQueue.SetTimer(handle3, timer, thirdTimerTime, 3));

   tickProvider.CheckResult(_T("|GetTickCount: 0|"));

   timer.CheckNoResults();

   timerQueue.HandleTimeouts();

   tickProvider.CheckResult(_T("|GetTickCount: 0|GetTickCount: 0|"));

   timer.CheckResult(_T("|OnTimer: 1|"));

   // Set the tick count to the second timeout time.

   tickProvider.SetTickCount(1000);

   THROW_ON_FAILURE(functionName, 0 == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|GetTickCount: 1000|"));

   // Check that the timer goes off.

   timerQueue.HandleTimeouts();

   tickProvider.CheckResult(_T("|GetTickCount: 1000|GetTickCount: 1000|"));

   timer.CheckResult(_T("|OnTimer: 2|"));

   THROW_ON_FAILURE(functionName, 9000 == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|GetTickCount: 1000|"));

   // Set the tick count to the timeout time.

   tickProvider.SetTickCount(10000);

   THROW_ON_FAILURE(functionName, 0 == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|GetTickCount: 10000|"));

   // Check that the timer goes off.

   timerQueue.HandleTimeouts();

   tickProvider.CheckResult(_T("|GetTickCount: 10000|"));

   timer.CheckResult(_T("|OnTimer: 3|"));

   THROW_ON_FAILURE(functionName, INFINITE == timerQueue.GetNextTimeout());

   tickProvider.CheckNoResults();

   THROW_ON_FAILURE(functionName, false == timerQueue.DestroyTimer(handle1));

   THROW_ON_FAILURE(functionName, false == timerQueue.DestroyTimer(handle2));

   THROW_ON_FAILURE(functionName, false == timerQueue.DestroyTimer(handle3));

   Output(functionName + _T(" - stop"));
}

void CCallbackTimerQueueTest::TestGetMaxTimeout()
{
   const _tstring functionName = _T("CCallbackTimerQueueTest::TestMaxTimeout");
   
   Output(functionName + _T(" - start"));

   CMockTickCountProvider tickProvider;

   {
      CCallbackTimerQueue timerQueue(tickProvider);

      tickProvider.CheckResult(_T("|GetTickCount: 0|"));       // creating a queue sets an 
                                                               // internal maintenance timer
   
      CLoggingCallbackTimer timer;

      THROW_ON_FAILURE(functionName, 4294967294 == timerQueue.GetMaximumTimeout());

      tickProvider.CheckNoResults();

      Output(functionName + _T(" - TODO - test for near 64bit rollover"));

      //// GetMaximumTimeout() doesn't reduce the value that it returns as the 64bit 
      //// rollover approaches; which means you WILL get an exception if you try and
      //// set a timer that is less than the value returned by GetMaximumTimeout() 
      //// but which crosses the rollover point. I'll fix this if I get enough 
      //// repeatable bug reports.

      //const ULONGLONG rollOver = 0;
      //const ULONGLONG beforeRollOver = rollOver - 1000;

      //tickProvider.SetTickCount(beforeRollOver);

      //THROW_ON_FAILURE(functionName, 4294967294 == timerQueue.GetMaximumTimeout());

      //tickProvider.CheckNoResults();
   }

   Output(functionName + _T(" - stop"));
}

void CCallbackTimerQueueTest::TestSetTimerPastTickCount64CountWrap()
{
   const _tstring functionName = _T("CCallbackTimerQueueTest::TestSetTimerPastTickCount64CountWrap");

   Output(functionName + _T(" - TODO - test for 64bit rollover"));

   //Output(functionName + _T(" - start"));

   //const ULONGLONG rollOver = 0;
   //const ULONGLONG beforeRollOver = rollOver - 1000;

   //CMockTickCountProvider tickProvider(beforeRollOver);

   //CCallbackTimerQueueEx timerQueue(tickProvider);

   //const _tstring resultBeforeRollOver = _T("|GetTickCount: ") + ToString(beforeRollOver) + _T("|");

   //tickProvider.CheckNoResults();

   //THROW_ON_FAILURE(functionName, INFINITE == timerQueue.GetNextTimeout());

   //tickProvider.CheckResult(_T("|"));

   //CLoggingCallbackTimer timer;

   //CCallbackTimerQueueEx::Handle handle = timerQueue.CreateTimer();

   //tickProvider.CheckResult(_T("|"));

   //THROW_ON_FAILURE(functionName, CCallbackTimerQueueEx::InvalidHandleValue != handle);

   //// Set a single timer for 100ms after the tick count rolls to 0.

   //THROW_ON_NO_EXCEPTION_4(functionName, timerQueue.SetTimer, handle, timer, 1100, 1);

   //tickProvider.CheckResult(resultBeforeRollOver);

   //THROW_ON_FAILURE(functionName, INFINITE == timerQueue.GetNextTimeout());

   //tickProvider.CheckNoResults();

   //THROW_ON_FAILURE(functionName, false == timerQueue.CancelTimer(handle));

   //// Set a single timer for 1ms before the tick count rolls to 0.

   //THROW_ON_FAILURE(functionName, false == timerQueue.SetTimer(handle, timer, 999, 1));

   //tickProvider.CheckResult(resultBeforeRollOver);

   //THROW_ON_FAILURE(functionName, 999 == timerQueue.GetNextTimeout());

   //tickProvider.CheckResult(resultBeforeRollOver);

   //// Set the time to the point where the tick count rolls over.

   //tickProvider.SetTickCount(rollOver);

   //// The timer expired 1ms ago...

   //THROW_ON_FAILURE(functionName, 0 == timerQueue.GetNextTimeout());

   //tickProvider.CheckResult(_T("|GetTickCount: 0|"));      

   //// Check that the time goes off.

   //timerQueue.HandleTimeouts();

   //tickProvider.CheckResult(_T("|GetTickCount: 0|"));

   //timer.CheckResult(_T("|OnTimer: 1|"));

   //// Prove that once we HAVE wrapped then all is well again for another zillion years...

   //// Set a single timer for 1000ms time.

   //THROW_ON_FAILURE(functionName, false == timerQueue.SetTimer(handle, timer, 1000, 1));

   //tickProvider.CheckResult(_T("|GetTickCount: 0|"));

   //THROW_ON_FAILURE(functionName, 1000 == timerQueue.GetNextTimeout());

   //tickProvider.CheckResult(_T("|GetTickCount: 0|"));

   //// Set the tick count to the timeout time.

   //tickProvider.SetTickCount(1000);

   //THROW_ON_FAILURE(functionName, 0 == timerQueue.GetNextTimeout());

   //tickProvider.CheckResult(_T("|GetTickCount: 1000|"));

   //// Check that the timer goes off.

   //timerQueue.HandleTimeouts();

   //tickProvider.CheckResult(_T("|GetTickCount: 1000|"));

   //timer.CheckResult(_T("|OnTimer: 1|"));

   //// Check that there are no more timers to go off.

   //THROW_ON_FAILURE(functionName, INFINITE == timerQueue.GetNextTimeout());

   //THROW_ON_FAILURE(functionName, false == timerQueue.DestroyTimer(handle));

   //Output(functionName + _T(" - stop"));
}

void CCallbackTimerQueueTest::TestMaxTimeout()
{
   const _tstring functionName = _T("CCallbackTimerQueueTest::TestMaxTimeout");
   
   Output(functionName + _T(" - start"));

   CMockTickCountProvider tickProvider(1000);

   {
      CCallbackTimerQueue timerQueue(tickProvider);

      tickProvider.CheckResult(_T("|GetTickCount: 1000|"));       // creating a queue sets an 
                                                                  // internal maintenance timer

      CLoggingCallbackTimer timer;

      const Milliseconds maxTimeout = timerQueue.GetMaximumTimeout();

      CCallbackTimerQueue::Handle handle = timerQueue.CreateTimer();

      tickProvider.CheckNoResults();

      THROW_ON_FAILURE(functionName, CCallbackTimerQueue::InvalidHandleValue != handle);

      THROW_ON_FAILURE(functionName, false == timerQueue.SetTimer(handle, timer, maxTimeout, 1));

      tickProvider.CheckResult(_T("|GetTickCount: 1000|"));

      const Milliseconds illegalTimeout = maxTimeout + 1;

      THROW_ON_NO_EXCEPTION_4(functionName, timerQueue.SetTimer, handle, timer, illegalTimeout, 1);

      tickProvider.CheckNoResults();

      THROW_ON_FAILURE(functionName, true == timerQueue.CancelTimer(handle));

      THROW_ON_NO_EXCEPTION_4(functionName, timerQueue.SetTimer, handle, timer, illegalTimeout, 1);

      tickProvider.CheckNoResults();

      THROW_ON_FAILURE(functionName, false == timerQueue.DestroyTimer(handle));

      timer.CheckNoResults();
      tickProvider.CheckNoResults();
   }

   Output(functionName + _T(" - stop"));
}

void CCallbackTimerQueueTest::TestMultipleTimers()
{
   const _tstring functionName = _T("CCallbackTimerQueueTest::TestMultipleTimers");
   
   Output(functionName + _T(" - start"));

   CMockTickCountProvider tickProvider;

   CCallbackTimerQueue timerQueue(tickProvider);

   tickProvider.CheckResult(_T("|GetTickCount: 0|"));          // creating a queue sets an 
                                                               // internal maintenance timer

   tickProvider.CheckResult(_T("|"));

   THROW_ON_FAILURE(functionName, INFINITE == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|"));

   CLoggingCallbackTimer timer1;
   CLoggingCallbackTimer timer2;
   CLoggingCallbackTimer timer3;
   CLoggingCallbackTimer timer4;
   CLoggingCallbackTimer timer5;
   CLoggingCallbackTimer timer6;

   CCallbackTimerQueue::Handle handle1 = CreateAndSetTimer(timerQueue, timer1, 300, 1);
   CCallbackTimerQueue::Handle handle2 = CreateAndSetTimer(timerQueue, timer2, 100, 2);
   CCallbackTimerQueue::Handle handle3 = CreateAndSetTimer(timerQueue, timer3, 200, 3);
   CCallbackTimerQueue::Handle handle4 = CreateAndSetTimer(timerQueue, timer4, 150, 4);
   CCallbackTimerQueue::Handle handle5 = CreateAndSetTimer(timerQueue, timer5, 150, 5);
   CCallbackTimerQueue::Handle handle6 = CreateAndSetTimer(timerQueue, timer6, 160, 6);

   tickProvider.CheckResult(
      _T("|GetTickCount: 0")
      _T("|GetTickCount: 0")
      _T("|GetTickCount: 0")
      _T("|GetTickCount: 0")
      _T("|GetTickCount: 0")
      _T("|GetTickCount: 0|"));

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

   tickProvider.CheckResult(_T("|GetTickCount: 100|GetTickCount: 100|"));

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

   tickProvider.CheckResult(_T("|GetTickCount: 155|GetTickCount: 155|GetTickCount: 155|"));

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

   tickProvider.CheckResult(_T("|GetTickCount: 201|GetTickCount: 201|GetTickCount: 201|"));

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

   tickProvider.CheckResult(_T("|"));

//   timerQueue.SetTimer(timer1, 100, 1);
//   timerQueue.SetTimer(timer2, 200, 2);

   THROW_ON_FAILURE(functionName, false == timerQueue.DestroyTimer(handle1));
   THROW_ON_FAILURE(functionName, false == timerQueue.DestroyTimer(handle2));
   THROW_ON_FAILURE(functionName, false == timerQueue.DestroyTimer(handle3));
   THROW_ON_FAILURE(functionName, false == timerQueue.DestroyTimer(handle4));
   THROW_ON_FAILURE(functionName, false == timerQueue.DestroyTimer(handle5));
   THROW_ON_FAILURE(functionName, false == timerQueue.DestroyTimer(handle6));

   Output(functionName + _T(" - stop"));
}

void CCallbackTimerQueueTest::TestResetTimer()
{
   const _tstring functionName = _T("CCallbackTimerQueueTest::TestResetTimer");
   
   Output(functionName + _T(" - start"));

   CMockTickCountProvider tickProvider;

   CCallbackTimerQueue timerQueue(tickProvider);

   CLoggingCallbackTimer timer;

   CCallbackTimerQueue::Handle handle = timerQueue.CreateTimer();

   tickProvider.CheckResult(_T("|GetTickCount: 0|"));       // creating a queue sets an 
                                                            // internal maintenance timer

   THROW_ON_FAILURE(functionName, CCallbackTimerQueue::InvalidHandleValue != handle);

   THROW_ON_FAILURE(functionName, false == timerQueue.SetTimer(handle, timer, 100, 1));

   tickProvider.CheckResult(_T("|GetTickCount: 0|"));

   THROW_ON_FAILURE(functionName, 100 == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|GetTickCount: 0|"));
   
   THROW_ON_FAILURE(functionName, true == timerQueue.SetTimer(handle, timer, 90, 2));

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

   tickProvider.CheckNoResults();

   THROW_ON_FAILURE(functionName, false == timerQueue.SetTimer(handle, timer, 110, 3));

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

   THROW_ON_FAILURE(functionName, false == timerQueue.DestroyTimer(handle));

   Output(functionName + _T(" - stop"));
}

void CCallbackTimerQueueTest::TestOneShotTimer()
{
   const _tstring functionName = _T("CCallbackTimerQueueTest::TestOneShotTimer");
   
   Output(functionName + _T(" - start"));

   CMockTickCountProvider tickProvider;

   CCallbackTimerQueue timerQueue(tickProvider);

   tickProvider.CheckResult(_T("|GetTickCount: 0|"));       // creating a queue sets an 
                                                            // internal maintenance timer

   THROW_ON_FAILURE(functionName, INFINITE == timerQueue.GetNextTimeout());

   tickProvider.CheckResult(_T("|"));

   CLoggingCallbackTimer timer;

   timerQueue.SetTimer(timer, 100, 1);

   tickProvider.CheckResult(_T("|GetTickCount: 0|"));

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

void CCallbackTimerQueueTest::TestActiveTimersAtDestructionTime()
{
   const _tstring functionName = _T("CCallbackTimerQueueTest::TestActiveTimersAtDestructionTime");
   
   Output(functionName + _T(" - start"));

   CMockTickCountProvider tickProvider;

   {
      CCallbackTimerQueue timerQueue(tickProvider);

      tickProvider.CheckResult(_T("|GetTickCount: 0|"));       // creating a queue sets an 
                                                               // internal maintenance timer
      CLoggingCallbackTimer timer;

      CCallbackTimerQueue::Handle handle1 = timerQueue.CreateTimer();

      THROW_ON_FAILURE(functionName, CCallbackTimerQueue::InvalidHandleValue != handle1);

      THROW_ON_FAILURE(functionName, false == timerQueue.SetTimer(handle1, timer, 100, 1));

      tickProvider.CheckResult(_T("|GetTickCount: 0|"));

      CCallbackTimerQueue::Handle handle2 = timerQueue.CreateTimer();

      THROW_ON_FAILURE(functionName, CCallbackTimerQueue::InvalidHandleValue != handle2);

      timerQueue.SetTimer(timer, 250, 1);

      timerQueue.SetTimer(timer, 2500, 1);

      timerQueue.HandleTimeouts();

      timer.CheckResult(_T("|"));
   }

   Output(functionName + _T(" - stop"));
}

///////////////////////////////////////////////////////////////////////////////
// Static helper functions
///////////////////////////////////////////////////////////////////////////////

static CCallbackTimerQueue::Handle CreateAndSetTimer(
   CCallbackTimerQueue &timerQueue, 
   CCallbackTimerQueue::Timer &timer, 
   const Milliseconds timeout,
   const CCallbackTimerQueue::UserData userData)
{
   const _tstring functionName = _T("CreateAndSetTimer");

   CCallbackTimerQueue::Handle handle = timerQueue.CreateTimer();

   THROW_ON_FAILURE(functionName, CCallbackTimerQueue::InvalidHandleValue != handle);

   THROW_ON_FAILURE(functionName, false == timerQueue.SetTimer(handle, timer, timeout, userData));

   return handle;
}

} // End of namespace Test
} // End of namespace Win32
} // End of namespace AmstelTech