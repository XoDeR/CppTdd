#pragma once

#include "../Platform/Types.h"

#include <wtypes.h>

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

      static Handle InvalidHandleValue;

      virtual Handle CreateTimer() = 0;

      virtual bool SetTimer(
         const Handle &handle, 
         Timer &timer,
         const Milliseconds timeout,
         const UserData userData) = 0;

      virtual bool CancelTimer(
         const Handle &handle) = 0;

      virtual bool DestroyTimer(
         Handle &handle) = 0;
		 
		virtual bool DestroyTimer(
         const Handle &handle) = 0;

      virtual void SetTimer(
         Timer &timer,
         const Milliseconds timeout,
         const UserData userData) = 0;

		virtual Milliseconds GetMaximumTimeout() const = 0;
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