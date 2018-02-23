#include "Thread.h"

#include <process.h>

#include "Win32Exception.h"

#include "TODO.h"

namespace AmstelTech 
{
	
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// CThread
///////////////////////////////////////////////////////////////////////////////

CThread::CThread()
   :  m_hThread(0)
{

}
      
CThread::~CThread()
{
   if (m_hThread != 0)
   {
      ::CloseHandle(m_hThread);
   }

   //warning: m_hThread neither freed nor zeroed in destructor
}

HANDLE CThread::GetHandle() const
{
   return m_hThread;
}

void CThread::Start()
{
   if (m_hThread == 0)
   {
      unsigned int threadID = 0;

      m_hThread = (HANDLE)::_beginthreadex(0, 0, ThreadFunction, (void*)this, 0, &threadID);

      if (m_hThread == 0)
      {
         throw CWin32Exception(_T("CThread::Start() - _beginthreadex"), errno);
      }
   }
   else
   {
      throw CException(_T("CThread::Start()"), _T("Thread already running - you can only call Start() once!"));
   }
}

void CThread::Wait() const
{
   if (!Wait(INFINITE))
   {
      throw CException(_T("CThread::Wait()"), _T("Unexpected timeout on infinite wait"));
   }
}

bool CThread::Wait(DWORD timeoutMillis) const
{
   #pragma TODO("base class? Waitable?")

   bool ok;

   DWORD result = ::WaitForSingleObject(m_hThread, timeoutMillis);

   if (result == WAIT_TIMEOUT)
   {
      ok = false;
   }
   else if (result == WAIT_OBJECT_0)
   {
      ok = true;
   }
   else
   {
      throw CWin32Exception(_T("CThread::Wait() - WaitForSingleObject"), ::GetLastError());
   }
    
   return ok;
}

unsigned int __stdcall CThread::ThreadFunction(void *pV)
{
   int result = 0;

   CThread* pThis = (CThread*)pV;
   
   if (pThis)
   {
      try
      {
         result = pThis->Run();
      }
      catch(...)
      {
      }
   }

   return result;
}

void CThread::Terminate(
   DWORD exitCode /* = 0 */)
{
   if (!::TerminateThread(m_hThread, exitCode))
   {
      throw CWin32Exception(_T("CThread::Terminate() - TerminateThread"), ::GetLastError());
   }

   m_hThread = 0;
}

} // End of namespace Win32
} // End of namespace AmstelTech 

