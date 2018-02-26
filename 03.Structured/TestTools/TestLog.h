#pragma once

// MSVC only
#pragma warning(disable : 4786)

#include "../Tools/tstring.h"
#include "../Tools/CriticalSection.h"

#include <vector>
#include <string>

namespace AmstelTech 
{
namespace Test 
{

///////////////////////////////////////////////////////////////////////////////
// CTestLog
///////////////////////////////////////////////////////////////////////////////

class CTestLog 
{
   public :

      explicit CTestLog(
         const AmstelTech::Win32::_tstring &separator);

      CTestLog();

		explicit CTestLog(
			CTestLog *pLinkedLog);

      CTestLog(
			CTestLog *pLinkedLog,
         const AmstelTech::Win32::_tstring &separator);

      void ClearLog();

      void LogMessage(
         const AmstelTech::Win32::_tstring &message) const;

      AmstelTech::Win32::_tstring GetMessages() const;

      AmstelTech::Win32::_tstring RemoveMessages();

      enum DisplayOnFailureMode
      {
         DisplayOnFailure,
         DoNotDisplayOnFailure
      };

      void CheckNoResults(
         DisplayOnFailureMode displayOnFailure = DisplayOnFailure);

      void CheckResult(
         const AmstelTech::Win32::_tstring &expectedResult, 
         DisplayOnFailureMode displayOnFailure = DisplayOnFailure);

      void CheckResultA(
         const std::string &expectedResult, 
         DisplayOnFailureMode displayOnFailure = DisplayOnFailure);

		void CheckResultFromFile(
			const AmstelTech::Win32::_tstring &fileName,
			const bool fileContainsLineEndBars = false);

   protected :

      void CheckResult(
         const AmstelTech::Win32::_tstring &expectedResult, 
         const AmstelTech::Win32::_tstring &actualResult, 
         DisplayOnFailureMode displayOnFailure = DisplayOnFailure);

      AmstelTech::Win32::_tstring GetFileName(
			const AmstelTech::Win32::_tstring &fileName);

   private :

		unsigned int m_fileNumber;

      const AmstelTech::Win32::_tstring m_separator;

      mutable AmstelTech::Win32::CCriticalSection m_criticalSection;

      typedef std::vector<AmstelTech::Win32::_tstring> Log;

      mutable Log m_log;

		CTestLog *m_pLog;

		// no copies - do not implement
		CTestLog(const CTestLog &rhs);
		CTestLog &operator=(const CTestLog &rhs);
};

} //-- namespace Test
} //-- namespace AmstelTech 