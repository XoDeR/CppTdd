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
// IQueueTimers
///////////////////////////////////////////////////////////////////////////////

class IQueueTimers
{
   public :

      typedef ULONG_PTR UserData;

      class Timer;

      typedef ULONG_PTR Handle;

      enum
      {
         InvalidHandleValue = 0
      };

      class TimerData;

      virtual Handle SetTimer(
         Timer &timer,
         const DWORD timeoutMillis,
         const UserData userData) = 0;

      virtual bool ResetTimer(
         Handle &handle, 
         Timer &timer,
         const DWORD timeoutMillis,
         const UserData userData) = 0;

      virtual bool CancelTimer(
         Handle &handle) = 0;

   protected :

      ~IQueueTimers() {}
};

///////////////////////////////////////////////////////////////////////////////
// IQueueTimers::Timer
///////////////////////////////////////////////////////////////////////////////

class IQueueTimers::Timer
{
   public :

      typedef IQueueTimers::UserData UserData;

      virtual void OnTimer(
         UserData userData) = 0;

   protected :

      ~Timer() {}
};

} // End of namespace Win32
} // End of namespace AmstelTech