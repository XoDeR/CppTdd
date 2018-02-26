#pragma once

#include "../Common/MessageLog.h"

#include "StringConverter.h"

namespace AmstelTech 
{
	
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// CDebugTrace
///////////////////////////////////////////////////////////////////////////////
class CDebugTrace : public AmstelTech::CMessageLog
{
   public :

      static CDebugTrace &Instance();

      /// A class that takes an instance of ILogMessages and installs it as 
      /// the message log used by the CDebugTrace class and then removes it
      /// and reinstalls the previous log in its destructor. It can, therefore,
      /// be used to support RAII "scope based" log installation and 
      /// removal.
      class LogInstaller
      {
         public :

            explicit LogInstaller(
               AmstelTech::ILogMessages &log);
      
            ~LogInstaller();

         private :

            AmstelTech::ILogMessages *m_pOldLog;

            /// No copies do not implement
            LogInstaller(const LogInstaller &rhs);
            /// No copies do not implement
            LogInstaller &operator=(const LogInstaller &rhs);
      };

   private :

      CDebugTrace();
};

inline void SetLogFileName(
   const std::string &s)
{
   CDebugTrace::Instance().SetLogName(s);
}

inline void SetLogFileName(
   const std::wstring &s)
{
   CDebugTrace::Instance().SetLogName(s);
}

inline void OutputEx(
   const std::string &s)
{
   CDebugTrace::Instance().LogMessage(s);
}

inline void OutputEx(
   const std::wstring &s)
{
   CDebugTrace::Instance().LogMessage(s);
}

inline void OutputEx(
   const char * const pString)
{
   CDebugTrace::Instance().LogMessage(pString);
}

inline void OutputEx(
   const wchar_t * const pString)
{
   CDebugTrace::Instance().LogMessage(pString);
}

inline void OutputEx(
   const char * const pString,
   const ILogMessages::DataLength stringLength)
{
   CDebugTrace::Instance().LogMessage(pString, stringLength);
}

inline void OutputEx(
   const wchar_t * const pString,
   const ILogMessages::DataLength stringLength)
{
   CDebugTrace::Instance().LogMessage(pString, stringLength);
}

#ifdef _DEBUG

inline void Output(
   const std::string &s)
{
   OutputEx(s);
}

inline void Output(
   const std::wstring &s)
{
   OutputEx(s);
}

inline void Output(
   const char * const pString)
{
   OutputEx(pString);
}

inline void Output(
   const wchar_t * const pString)
{
   OutputEx(pString);
}

inline void Output(
   const char * const pString,
   const ILogMessages::DataLength stringLength)
{
   OutputEx(pString, stringLength);
}

inline void Output(
   const wchar_t * const pString,
   const ILogMessages::DataLength stringLength)
{
   OutputEx(pString, stringLength);
}

#else

inline void Output(
   const std::string & /*s*/)
{
}

inline void Output(
   const std::wstring & /*s*/)
{
}

inline void Output(
   const char * const /*pString*/)
{
}

inline void Output(
   const wchar_t * const /*pString*/)
{
}

inline void Output(
   const char * const /*pString*/,
   const ILogMessages::DataLength /*stringLength*/)
{
}

inline void Output(
   const wchar_t * const /*pString*/,
   const ILogMessages::DataLength /*stringLength*/)
{
}

#endif

} // End of namespace Win32
} // End of namespace AmstelTech