#pragma once

namespace AmstelTech 
{
	
namespace Win32 
{
	
namespace Test 
{

class CCallbackTimerTest
{
   public :
      static void TestAll();
      static void TestConstruct();
	  static void TestTimer();
	  static void TestMultipleTimers();
      static void TestCancelTimer();
      static void TestTickCountWrap();
};

} //-- namespace Test
} //-- namespace Win32
} //-- namespace AmstelTech 