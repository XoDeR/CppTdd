#pragma once

#include <wtypes.h>

#include "tstring.h"
#include "SmartHandle.h"
#include "IWaitable.h"

namespace AmstelTech 
{

namespace Win32 
{

class IKernelObjectName;

///////////////////////////////////////////////////////////////////////////////
// CEvent
///////////////////////////////////////////////////////////////////////////////

class CEvent : public IWaitable
{
   public :
   
      /// Specify the type of event object.

      enum ResetType
      {
         ManualReset,
         AutoReset
      };

      /// Specify the initial state of an event object.
      
      enum InitialState
      {
         Signaled,
         NonSignaled
      };

      /// Specify how to create or connect to an existing event object.

      enum CreationFlags
      {
         CreateOrConnect,
         CreateNew,
         ConnectToExisting
      };

      /// Create an anonymous CEvent object for in-process use.
      
      CEvent(
         SECURITY_ATTRIBUTES *pSecurityAttributes,
         ResetType resetType,
         InitialState initialState);
   
      /// Create a new named CEvent object or connect to an existing
      /// one with the same name, for cross-process use. Use the CreationFlags
      /// to force creation only or connection only if required.

      CEvent(
         SECURITY_ATTRIBUTES *pSecurityAttributes,
         ResetType resetType,
         InitialState initialState,
         const IKernelObjectName &name,
         const CreationFlags creationFlags = CreateOrConnect);
 
      /// Connect to an existing named CEvent object for cross-process use.

      CEvent(
         SECURITY_ATTRIBUTES *pSecurityAttributes,
         const IKernelObjectName &name);
 
      /// Reset the event to the unsignalled state.

      void Reset();

      /// Set the event to the signalled state.

      void Set();

      /// Pulse the event.

      void Pulse();

      // Implement IWaitable

      HANDLE GetWaitHandle() const;

      void Wait() const;

      bool Wait(
         const Milliseconds timeout) const;

   private :

      CSmartHandle m_hEvent;

		/// No copies do not implement
      CEvent(const CEvent &rhs);
		/// No copies do not implement
      CEvent &operator=(const CEvent &rhs);
};

} // End of namespace Win32
} // End of namespace AmstelTech 

