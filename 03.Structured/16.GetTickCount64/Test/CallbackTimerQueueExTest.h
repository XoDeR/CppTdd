#pragma once

namespace AmstelTech 
{
	
namespace Win32 
{
	
namespace Test 
{

///////////////////////////////////////////////////////////////////////////////
// CCallbackTimerQueueExTest
///////////////////////////////////////////////////////////////////////////////

class CCallbackTimerQueueExTest
{
   public :

      static void TestAll();
      static void TestConstruct();
      static void TestCreateTimer();
      static void TestDestroyTimer();
      static void TestTimer();
      static void TestMultipleTimers();
      static void TestCancelTimer();
      static void TestCancelExpiredTimer();
      static void TestGetMaxTimeout();
      static void TestMaxTimeout();
      static void TestSetTimerPastTickCount64CountWrap();
      static void TestResetTimer();
      static void TestOneShotTimer();
      static void TestActiveTimersAtDestructionTime();
};

} // End of namespace Test
} // End of namespace Win32
} // End of namespace AmstelTech