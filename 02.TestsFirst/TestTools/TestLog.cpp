#include "TestLog.h"
#include "TestException.h"

#include <iostream>

#include "../Tools/Utils.h"
#include "../Tools/StringConverter.h"

using AmstelTech::Win32::Output;
using AmstelTech::Win32::_tstring;
using AmstelTech::Win32::CCriticalSection;
using AmstelTech::Win32::CStringConverter;

using std::string;

namespace AmstelTech 
{
	
namespace Test 
{

///////////////////////////////////////////////////////////////////////////////
// CTestLog
///////////////////////////////////////////////////////////////////////////////

void CTestLog::ClearLog()
{
   CCriticalSection::Owner lock(m_criticalSection);
   m_log.clear();
}

void CTestLog::LogMessage(const _tstring &message) const
{
   CCriticalSection::Owner lock(m_criticalSection);
   m_log.push_back(message);
}

_tstring CTestLog::GetMessages() const
{
   CCriticalSection::Owner lock(m_criticalSection);

   _tstring result = _T("|");

   for (Log::const_iterator it = m_log.begin(); it != m_log.end(); ++it)
   {
      result += *it;
      result += _T("|");
   }

   return result;
}

_tstring CTestLog::RemoveMessages() 
{
   CCriticalSection::Owner lock(m_criticalSection);

   _tstring result = GetMessages();
   
   m_log.clear();

   return result;
}

void CTestLog::CheckResult(
   const _tstring &expectedResult, 
   bool displayOnFailure)
{
   const _tstring result = RemoveMessages();

   if (result != expectedResult)
   {
      if (displayOnFailure)
      {
         Output(_T("result:   ") + result);
         Output(_T("expected: ") + expectedResult);
      }

      throw CTestException(_T("CTestLog::CheckResult()"), _T("Log does not contain expected result"));
   }
}

void CTestLog::CheckResultA(
   const string &expectedResult, 
   bool displayOnFailure)
{
   CheckResult(CStringConverter::AtoT(expectedResult), displayOnFailure);
}

} //-- namespace Test
} //-- namespace AmstelTech 