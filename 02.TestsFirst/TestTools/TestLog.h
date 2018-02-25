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
      void ClearLog();
      void LogMessage(const AmstelTech::Win32::_tstring &message) const;
      AmstelTech::Win32::_tstring GetMessages() const;
      AmstelTech::Win32::_tstring RemoveMessages();
	  void CheckNoResults(
         bool displayOnFailure = true);
      void CheckResult(const AmstelTech::Win32::_tstring &expectedResult, bool displayOnFailure = true);
      void CheckResultA(const std::string &expectedResult, bool displayOnFailure = true);
   private :
      mutable AmstelTech::Win32::CCriticalSection m_criticalSection;
      typedef std::vector<AmstelTech::Win32::_tstring> Log;
      mutable Log m_log;
};

} //-- namespace Test
} //-- namespace AmstelTech 