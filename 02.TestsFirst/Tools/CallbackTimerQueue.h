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

class IProvideTickCount;

///////////////////////////////////////////////////////////////////////////////
// CCallbackTimerQueue
///////////////////////////////////////////////////////////////////////////////

class CCallbackTimerQueue
{
   public :

      typedef ULONG_PTR UserData;

      class Timer;

      CCallbackTimerQueue();

      explicit CCallbackTimerQueue(
         const IProvideTickCount &tickProvider);

      void SetTimer(
         Timer &timer,
         const DWORD timeoutMillis,
         const UserData userData);

      DWORD GetNextTimeout() const;

      void HandleTimeouts();

   private :

      const IProvideTickCount &m_tickProvider;

      Timer *m_pTimer;
      DWORD m_nextTimeout;
      UserData m_userData;

      // No copies do not implement
      CCallbackTimerQueue(const CCallbackTimerQueue &rhs);
      CCallbackTimerQueue &operator=(const CCallbackTimerQueue &rhs);
};

///////////////////////////////////////////////////////////////////////////////
// CCallbackTimerQueue::Timer
///////////////////////////////////////////////////////////////////////////////

class CCallbackTimerQueue::Timer
{
   public :

      virtual void OnTimer(
         UserData userData) = 0;

   protected :

      ~Timer();
};

} // End of namespace Win32
} // End of namespace AmstelTech 