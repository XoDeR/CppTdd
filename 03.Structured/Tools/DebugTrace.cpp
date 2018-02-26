#include "../Platform/Platform.h"

#include "DebugTrace.h"
#include "SimpleMessageLog.h"

using AmstelTech::CMessageLog;
using AmstelTech::ILogMessages;

namespace AmstelTech 
{
	
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// Static variables 
///////////////////////////////////////////////////////////////////////////////

static CSimpleMessageLog s_simpleMessageLog;

///////////////////////////////////////////////////////////////////////////////
// CDebugTrace
///////////////////////////////////////////////////////////////////////////////

CDebugTrace::CDebugTrace()
   :  CMessageLog(s_simpleMessageLog)
{
}

CDebugTrace &CDebugTrace::Instance()
{
   static CDebugTrace theInstance;

   return theInstance;
}

///////////////////////////////////////////////////////////////////////////////
// CDebugTrace::LogInstaller
///////////////////////////////////////////////////////////////////////////////

CDebugTrace::LogInstaller::LogInstaller(
   AmstelTech::ILogMessages &log)
   :  m_pOldLog(CDebugTrace::Instance().SetLog(log))
{

}
      
CDebugTrace::LogInstaller::~LogInstaller()
{
   CDebugTrace::Instance().SetLog(*m_pOldLog);
}

} // End of namespace Win32
} // End of namespace AmstelTech