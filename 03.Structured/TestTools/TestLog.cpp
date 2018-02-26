#include "TestLog.h"
#include "TestException.h"

#include <iostream>

#include "../Tools/Utils.h"
#include "../Tools/DebugTrace.h"
#include "../Tools/StringConverter.h"

using AmstelTech::Win32::OutputEx;
using AmstelTech::Win32::_tstring;
using AmstelTech::Win32::CCriticalSection;
using AmstelTech::Win32::CStringConverter;
using AmstelTech::Win32::FindAndReplace;
using AmstelTech::Win32::ToString;
using AmstelTech::Win32::LoadFileAsString;
using AmstelTech::Win32::SaveStringAsFile;

using std::string;

namespace AmstelTech 
{
	
namespace Test 
{

///////////////////////////////////////////////////////////////////////////////
// CTestLog
///////////////////////////////////////////////////////////////////////////////

CTestLog::CTestLog(
   const _tstring &separator)
	:	m_fileNumber(1),
      m_separator(separator),
      m_pLog(0)
{

}

CTestLog::CTestLog()
	:	m_fileNumber(1),
      m_separator(_T("|")),
      m_pLog(0)
{

}

CTestLog::CTestLog(
	CTestLog *pLinkedLog)
	:	m_fileNumber(1),
      m_separator(_T("|")),
		m_pLog(pLinkedLog)
{

}

CTestLog::CTestLog(
	CTestLog *pLinkedLog,
   const _tstring &separator)
	:	m_fileNumber(1),
      m_separator(separator),
		m_pLog(pLinkedLog)
{

}

void CTestLog::ClearLog()
{
	if (m_pLog)
	{
		m_pLog->ClearLog();
	}
	else
	{
      CCriticalSection::Owner lock(m_criticalSection);

      m_log.clear();
   }
}

void CTestLog::LogMessage(
   const _tstring &message) const
{
	if (m_pLog)
	{
		m_pLog->LogMessage(message);
	}
	else
	{
		CCriticalSection::Owner lock(m_criticalSection);

      m_log.push_back(message);
	}
}

_tstring CTestLog::GetMessages() const
{
	if (m_pLog)
	{
		return m_pLog->GetMessages();
	}

   CCriticalSection::Owner lock(m_criticalSection);

   _tstring result;

   for (Log::const_iterator it = m_log.begin(); it != m_log.end(); ++it)
   {
      result += *it;
      result += m_separator;
   }

   return result;
}

_tstring CTestLog::RemoveMessages() 
{
	if (m_pLog)
	{
		return m_pLog->RemoveMessages();
	}

   CCriticalSection::Owner lock(m_criticalSection);

   _tstring result = GetMessages();
   
   m_log.clear();

   return result;
}

void CTestLog::CheckNoResults(
   DisplayOnFailureMode displayOnFailure)
{
   CheckResult(m_separator, displayOnFailure);
}

void CTestLog::CheckResult(
   const _tstring &expectedResult, 
   DisplayOnFailureMode displayOnFailure)
{
   CheckResult(expectedResult, m_separator + RemoveMessages(), displayOnFailure);
}

void CTestLog::CheckResult(
   const _tstring &expectedResult, 
   const _tstring &actualResult, 
   DisplayOnFailureMode displayOnFailure)
{
   if (actualResult != expectedResult)
   {
      if (displayOnFailure == DisplayOnFailure)
      {
         OutputEx(_T("result:   ") + actualResult);
         OutputEx(_T("expected: ") + expectedResult);
      }

      throw CTestException(_T("CTestLog::CheckResult()"), _T("Log does not contain expected result"));
   }
}

void CTestLog::CheckResultA(
   const string &expectedResult, 
   DisplayOnFailureMode displayOnFailure)
{
   CheckResult(CStringConverter::AtoT(expectedResult), displayOnFailure);
}

_tstring CTestLog::GetFileName(
	const _tstring &fileName)
{
   return fileName + _T(".") + ToString(m_fileNumber++);
}

void CTestLog::CheckResultFromFile(
	const _tstring &fileName,
	const bool fileContainsLineEndBars)
{
	if (m_pLog)
	{
      m_pLog->CheckResultFromFile(fileName, fileContainsLineEndBars);
   }
   else
   {
   	const _tstring lineEnd = (fileContainsLineEndBars ? m_separator + _T("\r\n") : _T("\r\n"));

   	CCriticalSection::Owner lock(m_criticalSection);

	   _tstring actualResults = GetMessages();

   	actualResults = FindAndReplace(actualResults, m_separator, lineEnd);

	   const _tstring fileNameBase = GetFileName(fileName);

	   try
	   {
		   _tstring expectedResults = LoadFileAsString(fileNameBase + _T(".log"));

   		expectedResults = FindAndReplace(expectedResults, lineEnd, m_separator);

   		CheckResult(m_separator + expectedResults, false);
	   }
	   catch(...)
	   {
		   SaveStringAsFile(fileNameBase + _T(".Actual.log"), actualResults);
		   
		   throw;
	   }
   }
}

} //-- namespace Test
} //-- namespace AmstelTech 