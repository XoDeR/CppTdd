#include "CallbackTimerTest.h"

#include "..\CallbackTimer.h"

#include "Tools\Utils.h"

using AmstelTech::Win32::Output;
using AmstelTech::Win32::_tstring;

namespace AmstelTech {
namespace Win32 {
namespace Test {

void CCallbackTimerTest::TestAll()
{
   TestConstruct();
}

void CCallbackTimerTest::TestConstruct()
{
   const _tstring functionName = _T("CCallbackTimerTest::TestConstruct");
   
   Output(functionName + _T(" - start"));

   CCallbackTimer timer;

   Output(functionName + _T(" - stop"));
}

} // End of namespace Test
} // End of namespace Win32
} // End of namespace AmstelTech 