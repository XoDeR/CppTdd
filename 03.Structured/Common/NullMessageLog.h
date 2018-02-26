#pragma once

#include "ILogMessages.h"

namespace AmstelTech 
{

///////////////////////////////////////////////////////////////////////////////
// CNullMessageLog
///////////////////////////////////////////////////////////////////////////////

class CNullMessageLog : public ILogMessages
{
   public :

      virtual void SetThreadIdentifier(
         const std::string & /*identifier*/) {}

      virtual void SetThreadIdentifier(
         const std::wstring & /*identifier*/) {}

      virtual void SetLogName(
         const std::string & /*name*/) {}

      virtual void SetLogName(
         const std::wstring & /*name*/) {}

      virtual void LogMessage(
         const std::string & /*message*/) {}

      virtual void LogMessage(
         const std::wstring & /*message*/) {}

      virtual void LogMessage(
         const char * const /*pString*/) {}

      virtual void LogMessage(
         const wchar_t * const /*pString*/) {}

      virtual void LogMessage(
         const char * const /*pString*/,
         const DataLength /*stringLength*/) {}

      virtual void LogMessage(
         const wchar_t * const /*pString*/,
         const DataLength /*stringLength*/) {}
};

} // End of namespace AmstelTech