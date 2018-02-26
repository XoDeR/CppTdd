#pragma once

#include "../Common/ILogMessages.h"

#include "tstring.h"
#include "CriticalSection.h"
#include "ThreadLocalStorage.h"

#include <fstream>
#include <list>

namespace AmstelTech 
{
	
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// CSimpleMessageLog
///////////////////////////////////////////////////////////////////////////////

class CSimpleMessageLog : public ILogMessages
{
   public :

      enum LogTargets
      {
         LogToCOUT               = 0x0001,
         LogToOutputDebugString  = 0x0010,
         LogToFile               = 0x0100,
         LogToAll                = 0x0111
      };

      CSimpleMessageLog();

      explicit CSimpleMessageLog(
         const _tstring &fileName,
         const LogTargets targets = LogToAll);

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

      const std::string &GetThreadID();

      const std::string *SetThreadID(
         const std::string &threadIdentifier);

      CCriticalSection m_criticalSection;

      CThreadLocalStorage m_tls;

      std::fstream m_output;

      std::string m_fileName;

      const bool m_logToCOUT;
      const bool m_logToOutputDebugString;
      const bool m_logToFile;

      typedef std::list<std::string> ThreadIDs;

      ThreadIDs m_threadIDs;

      /// No copies do not implement
      CSimpleMessageLog(const CSimpleMessageLog &rhs);
		/// No copies do not implement
      CSimpleMessageLog &operator=(const CSimpleMessageLog &rhs);
};

} // End of namespace Win32
} // End of namespace AmstelTech