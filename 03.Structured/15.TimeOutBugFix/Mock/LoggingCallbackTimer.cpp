#include "../../Platform/Platform.h"

#include "LoggingCallbackTimer.h"

#include "../../Tools/Utils.h"

using AmstelTech::Win32::ToString;

namespace AmstelTech 
{
	
namespace Win32 
{
	
namespace Mock 
{

///////////////////////////////////////////////////////////////////////////////
// CLoggingCallbackTimer
///////////////////////////////////////////////////////////////////////////////

CLoggingCallbackTimer::CLoggingCallbackTimer()
{
}

void CLoggingCallbackTimer::OnTimer(
   UserData userData)
{
   LogMessage(_T("OnTimer: ") + ToString(userData));
}

} // End of namespace Mock
} // End of namespace Win32
} // End of namespace AmstelTech