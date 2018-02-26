#pragma once

#include "../../TestTools/TestLog.h"

#include "../../Tools/CallbackTimerQueue.h"

namespace AmstelTech 
{
	
namespace Win32 
{
	
namespace Mock 
{

///////////////////////////////////////////////////////////////////////////////
// CLoggingCallbackTimer
///////////////////////////////////////////////////////////////////////////////

class CLoggingCallbackTimer : 
   public CCallbackTimerQueue::Timer,
   public AmstelTech::Test::CTestLog
{
   public : 

      CLoggingCallbackTimer();

      // Implement CCallbackTimerQueue::Timer

      virtual void OnTimer(
         UserData userData);

   private :

      // No copies do not implement
      CLoggingCallbackTimer(const CLoggingCallbackTimer &rhs);
      CLoggingCallbackTimer &operator=(const CLoggingCallbackTimer &rhs);
};

} // End of namespace Mock
} // End of namespace Win32
} // End of namespace AmstelTech