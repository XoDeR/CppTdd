#include "../../Platform/Platform.h"

#include "MessageLog.h"
#include "NullMessageLog.h"

using std::string;
using std::wstring;

namespace AmstelTech 
{

///////////////////////////////////////////////////////////////////////////////
// Static variables 
///////////////////////////////////////////////////////////////////////////////

static CNullMessageLog s_nullMessageLog;

///////////////////////////////////////////////////////////////////////////////
// CMessageLog
///////////////////////////////////////////////////////////////////////////////

CMessageLog::CMessageLog()
   :  m_pLog(&s_nullMessageLog)
{
}

CMessageLog::CMessageLog(
   ILogMessages &log)
   :  m_pLog(&log)
{
}

ILogMessages *CMessageLog::SetLog(
   ILogMessages &log)
{
   ILogMessages *pOldLog = m_pLog;

   m_pLog = &log;

   return pOldLog;
}

void CMessageLog::ClearLog()
{
   m_pLog = &s_nullMessageLog;
}

void CMessageLog::SetThreadIdentifier(
   const string &identifier)
{
   m_pLog->SetThreadIdentifier(identifier);
}

void CMessageLog::SetThreadIdentifier(
   const wstring &identifier)
{
   m_pLog->SetThreadIdentifier(identifier);
}

void CMessageLog::SetLogName(
   const string &name)
{
   m_pLog->SetLogName(name);
}

void CMessageLog::SetLogName(
   const wstring &name)
{
   m_pLog->SetLogName(name);
}

void CMessageLog::LogMessage(
   const string &message)
{
   m_pLog->LogMessage(message);
}

void CMessageLog::LogMessage(
   const wstring &message)
{
   m_pLog->LogMessage(message);
}

void CMessageLog::LogMessage(
   const char * const pString)
{
   m_pLog->LogMessage(pString);
}

void CMessageLog::LogMessage(
   const wchar_t * const pString)
{
   m_pLog->LogMessage(pString);
}

void CMessageLog::LogMessage(
   const char * const pString,
   const DataLength stringLength)
{
   m_pLog->LogMessage(pString, stringLength);
}

void CMessageLog::LogMessage(
   const wchar_t * const pString,
   const DataLength stringLength)
{
   m_pLog->LogMessage(pString, stringLength);
}

} // End of namespace AmstelTech