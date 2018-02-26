#pragma once

#include <wtypes.h>

#include "SmartHandle.h"
#include "IRunnable.h"
#include "IWaitable.h"
#include "tstring.h"

namespace AmstelTech 
{
	
namespace Win32 
{

class IRunnable;

///////////////////////////////////////////////////////////////////////////////
// CThread
///////////////////////////////////////////////////////////////////////////////

class CThread : public IWaitable
{
   public :
   
      /// Create a thread to run the supplied instance of IRunnable.

      explicit CThread(
         IRunnable &runnable);
      
      virtual ~CThread();

      /// Start the thread running.

      void Start();

      /// Start the thread running and optionally start it in a suspended state.

      void Start(
         bool startSuspended);

      /// Start the thread in a suspended state.

      void StartSuspended();

      /// Start the thread with the specified thread priority.

      void StartWithPriority(
         const int priority);

      /// Resume a suspended thread.

      void Resume();

      /// Terminate a thread and have it return the supplied exit code.
      /// Note that this should be used with great care!

      void Terminate(
         DWORD exitCode = 0);

      /// Returns true if the thread was started.

      bool WasStarted() const;

      /// Sets a threads name so that it can be queried in a debugger.

      void SetThreadName(
         const _tstring &threadName) const;

      /// Returns true if the thread object represents the thread that is calling
      /// IsThisThread().

      bool IsThisThread() const;

      /// Sets the current threads name so that it can be queried in a debugger.

      static void SetCurrentThreadName(
         const _tstring &threadName);

      /// Sets the supplied threads name so that it can be queried in a debugger.

      static void SetThreadName(
         DWORD threadID, 
         const _tstring &threadName);

      void EnableThreadPriorityBoost();

      void DisableThreadPriorityBoost();

      bool ThreadPriorityBoostEnabled() const;

      void SetThreadPriority(
         const int priority);

      int GetThreadPriority() const;

      // Implement IWaitable

      HANDLE GetWaitHandle() const;

      void Wait() const;

      bool Wait(
         const Milliseconds timeout) const;

   private :

      static unsigned int __stdcall ThreadFunction(void *pV);

      CSmartHandle m_hThread;

      DWORD m_threadID;

      IRunnable &m_runnable;

      /// No copies do not implement
      CThread(const CThread &rhs);
      /// No copies do not implement
      CThread &operator=(const CThread &rhs);
};

} // End of namespace Win32
} // End of namespace AmstelTech 

