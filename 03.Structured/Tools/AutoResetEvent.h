#pragma once

#include "Event.h"

namespace AmstelTech 
{
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// CAutoResetEvent
///////////////////////////////////////////////////////////////////////////////

class CAutoResetEvent : public IWaitable
{
   public :
   
      /// Create an anonymous CAutoResetEvent object for in-process use.

      explicit CAutoResetEvent(
         CEvent::InitialState initialState = CEvent::NonSignaled,
         SECURITY_ATTRIBUTES *pSecurityAttributes = 0);
      
      /// Create a new named CAutoResetEvent object or connect to an existing
      /// one with the same name, for cross-process use.

      explicit CAutoResetEvent(
         const IKernelObjectName &name, 
         SECURITY_ATTRIBUTES *pSecurityAttributes = 0,
         CEvent::InitialState initialState = CEvent::NonSignaled);

      /// Create a new named CAutoResetEvent object or connect to an existing
      /// one with the same name, for cross-process use. Use the CreationFlags
      /// to force creation only or connection only if required.

      CAutoResetEvent(
         const IKernelObjectName &name, 
         const CEvent::CreationFlags creationFlags, 
         SECURITY_ATTRIBUTES *pSecurityAttributes = 0,
         CEvent::InitialState initialState = CEvent::NonSignaled); 

      /// Set the event to the signalled state.

      void Set();

      /// Pulse the event. Releases one waiting thread and resets the event.

      void Pulse();

      // Implement IWaitable

      HANDLE GetWaitHandle() const;

      void Wait() const;

      bool Wait(
         const Milliseconds timeout) const;

   private :

      CEvent m_event;
      // No copies do not implement
      CAutoResetEvent(const CAutoResetEvent &rhs);
      CAutoResetEvent &operator=(const CAutoResetEvent &rhs);
};

} // End of namespace Win32
} // End of namespace AmstelTech 