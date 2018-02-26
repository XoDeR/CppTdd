#pragma once

#include "../Platform/Types.h"

#include <wtypes.h>

namespace AmstelTech 
{
	
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// IWaitable
///////////////////////////////////////////////////////////////////////////////

// An interface to code that can be waited for, either via the methods on the
// interface or by passing a handle to one of the 

class IWaitable
{
   public :
   
      /// Access a HANDLE to wait on by passing it to one of the Wait Functions

      virtual HANDLE GetWaitHandle() const = 0;

      /// Wait indefinitely for the object to become signalled.

      virtual void Wait() const = 0;

      /// Wait, with a time limit, for the object to become signalled.

      virtual bool Wait(
         const Milliseconds timeout) const = 0;

      /// Wait indefinitely for the supplied handle to become signalled.

      static void Wait(
         HANDLE handle);

      /// Wait, with a time limit, for the supplied handle to become signalled.

      static bool Wait(
         HANDLE handle,
         const Milliseconds timeout);

   protected :

		/// We never delete instances of this interface; you must manage the 
		/// lifetime of the class that implements it.

      ~IWaitable() {}
};

} // End of namespace Win32
} // End of namespace AmstelTech 
