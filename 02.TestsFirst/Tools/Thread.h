#pragma once

#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
#endif

namespace AmstelTech 
{
	
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// CThread
///////////////////////////////////////////////////////////////////////////////

class CThread 
{
   public :
   
      CThread();
      
      virtual ~CThread();

      HANDLE GetHandle() const;

      void Wait() const;

      bool Wait(DWORD timeoutMillis) const;

      void Start();

      void Terminate(
         DWORD exitCode = 0);

   private :

      virtual int Run() = 0;

      static unsigned int __stdcall ThreadFunction(void *pV);

      HANDLE m_hThread;

      // No copies do not implement
      CThread(const CThread &rhs);
      CThread &operator=(const CThread &rhs);
};

} // End of namespace Win32
} // End of namespace AmstelTech 

