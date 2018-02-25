#pragma once

namespace AmstelTech 
{
	
namespace Win32 
{
	
namespace Test 
{

///////////////////////////////////////////////////////////////////////////////
// CCallbackTimerQueueTest
///////////////////////////////////////////////////////////////////////////////

class CCallbackTimerQueueTest
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
      static void TestMaxTimeout();
      static void TestTickCountWrap();
      static void TestResetTimer();
      static void TestOneShotTimer();
      static void TestActiveTimersAtDestructionTime();
};

} // End of namespace Test
} // End of namespace Win32
} // End of namespace AmstelTech