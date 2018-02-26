#pragma once

#include "ILogMessages.h"

namespace AmstelTech 
{

///////////////////////////////////////////////////////////////////////////////
// CMessageLog
///////////////////////////////////////////////////////////////////////////////

class CMessageLog : public ILogMessages
{
   public :

      CMessageLog();

      explicit CMessageLog(
         ILogMessages &log);

      ILogMessages *SetLog(
         ILogMessages &log);

      void ClearLog();

      // Implement ILogMessages

      virtual void SetThreadIdentifier(
         const std::string &identifier);

      virtual void SetThreadIdentifier(
         const std::wstring &identifier);

      virtual void SetLogName(
         const std::string &name);

      virtual void SetLogName(
         const std::wstring &name);

      virtual void LogMessage(
         const std::string &message);

      virtual void LogMessage(
         const std::wstring &message);

      virtual void LogMessage(
         const char * const pString);

      virtual void LogMessage(
         const wchar_t * const pString);

      virtual void LogMessage(
         const char * const pString,
         const DataLength stringLength);

      virtual void LogMessage(
         const wchar_t * const pString,
         const DataLength stringLength);

   private :

      ILogMessages *m_pLog;

      /// No copies do not implement
      CMessageLog(const CMessageLog &rhs);
      /// No copies do not implement
      CMessageLog &operator=(const CMessageLog &rhs);
};

} // End of namespace AmstelTech