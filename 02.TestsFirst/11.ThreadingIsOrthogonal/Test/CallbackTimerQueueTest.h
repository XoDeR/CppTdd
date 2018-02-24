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
      static void TestTimer();
      static void TestMultipleTimers();
      static void TestCancelTimer();
      static void TestTickCountWrap();
	  static void TestMaxTimeout();
};

} // End of namespace Test
} // End of namespace Win32
} // End of namespace AmstelTech