#pragma once

#include "MessageLog.h"

namespace AmstelTech 
{

///////////////////////////////////////////////////////////////////////////////
// CDebugTrace
///////////////////////////////////////////////////////////////////////////////

class CDebugTrace : public CMessageLog
{
   public :

      static CDebugTrace &Instance();

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

} // End of namespace AmstelTech