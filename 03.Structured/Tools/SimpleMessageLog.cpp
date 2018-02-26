#include "../Platform/Platform.h"

#include "SimpleMessageLog.h"
#include "StringConverter.h"
#include "Utils.h"

#include <iostream>

using std::string;
using std::wstring;
using std::cout;
using std::endl;

namespace AmstelTech 
{
	
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// CSimpleMessageLog
///////////////////////////////////////////////////////////////////////////////

CSimpleMessageLog::CSimpleMessageLog()
   :  m_fileName("AmstelTech.log"),
      m_logToCOUT(true),
      m_logToOutputDebugString(true),
      m_logToFile(true)
{
}

CSimpleMessageLog::CSimpleMessageLog(
   const _tstring &fileName,
   const LogTargets targets)
   :  m_fileName(CStringConverter::TtoA(fileName)),
      m_logToCOUT((targets & LogToCOUT) == LogToCOUT),
      m_logToOutputDebugString((targets & LogToOutputDebugString) == LogToOutputDebugString),
      m_logToFile((targets & LogToFile) == LogToFile)

{
}

void CSimpleMessageLog::SetLogName(
   const string &fileName)
{
   CCriticalSection::Owner lock(m_criticalSection);

   if (fileName != "")
   {
      m_fileName = fileName;
   }

   if (m_output.is_open())
   {
      m_output.close();
   }
}

void CSimpleMessageLog::SetLogName(
   const wstring &fileName)
{
   SetLogName(CStringConverter::WtoA(fileName));
}

void CSimpleMessageLog::SetThreadIdentifier(
   const string &identifier)
{
   SetThreadID(identifier + ": ");
}

void CSimpleMessageLog::SetThreadIdentifier(
   const wstring &identifier)
{
   SetThreadID(CStringConverter::WtoA(identifier) + ": ");
}

void CSimpleMessageLog::LogMessage(
   const string &message)
{
   if (m_logToCOUT || m_logToOutputDebugString || m_logToFile)
   {
      CCriticalSection::Owner lock(m_criticalSection);

      const string &threadId = GetThreadID();

      if (m_logToCOUT)
      {
         // cout displays \n as a line break, we don't log it as such...

         std::cout << threadId << message << endl;
      }

      if (m_logToOutputDebugString)
      {
         const string msg = threadId + message + "\n";

         OutputDebugStringA(msg.c_str());
      }

      if (m_logToFile)
      {
         if (!m_output.is_open())
         {
            m_output.open(m_fileName.c_str(), std::ios_base::out | std::ios_base::app | std::ios_base::binary);

            m_output << "****************New Log*****************\r\n";
         }

         m_output << threadId << message << "\r\n";
      }
   }
}

void CSimpleMessageLog::LogMessage(
   const wstring &message)
{
   LogMessage(CStringConverter::WtoA(message));
}

void CSimpleMessageLog::LogMessage(
   const char * const pString)
{
   const string message(pString);

   LogMessage(message);
}

void CSimpleMessageLog::LogMessage(
   const wchar_t * const pString)
{
   LogMessage(CStringConverter::WtoA(pString));
}

void CSimpleMessageLog::LogMessage(
   const char * const pString,
   const DataLength stringLength)
{
   const string message(pString, stringLength);

   LogMessage(message);
}

void CSimpleMessageLog::LogMessage(
   const wchar_t * const pString,
   const DataLength stringLength)
{
   LogMessage(CStringConverter::WtoA(pString, stringLength));
}

const string &CSimpleMessageLog::GetThreadID()
{
   const string *pThreadID = reinterpret_cast<string *>(m_tls.GetValue());

   if (!pThreadID)
   {
      const string threadId = ToStringA(GetCurrentThreadId()) + ": ";
      
      pThreadID = SetThreadID(threadId);
   }

   return *pThreadID;
}

const string *CSimpleMessageLog::SetThreadID(
   const string &threadIdentifier)
{
   CCriticalSection::Owner lock(m_criticalSection);

   m_threadIDs.push_back(threadIdentifier);

   string *pThreadID = &m_threadIDs.back();
   
   m_tls.SetValue(pThreadID);

   return pThreadID;
}

} // End of namespace Win32
} // End of namespace AmstelTech