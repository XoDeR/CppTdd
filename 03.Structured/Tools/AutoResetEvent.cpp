#include "../Platform/Platform.h"
#include "AutoResetEvent.h"

namespace AmstelTech 
{
	
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// CAutoResetEvent
///////////////////////////////////////////////////////////////////////////////

CAutoResetEvent::CAutoResetEvent(
   CEvent::InitialState initialState,
   SECURITY_ATTRIBUTES *pSecurityAttributes)
   :  m_event(pSecurityAttributes, CEvent::AutoReset, initialState)
{

}

CAutoResetEvent::CAutoResetEvent(
   const IKernelObjectName &name, 
   SECURITY_ATTRIBUTES *pSecurityAttributes,
   CEvent::InitialState initialState)
   :  m_event(pSecurityAttributes, CEvent::AutoReset, initialState, name)
{
   
}

CAutoResetEvent::CAutoResetEvent(
   const IKernelObjectName &name, 
   const CEvent::CreationFlags creationFlags, 
   SECURITY_ATTRIBUTES *pSecurityAttributes,
   CEvent::InitialState initialState)
   :  m_event(pSecurityAttributes, CEvent::AutoReset, initialState, name, creationFlags)
{
   
}

void CAutoResetEvent::Set()
{
   m_event.Set();
}

void CAutoResetEvent::Pulse()
{
   m_event.Pulse();
}

HANDLE CAutoResetEvent::GetWaitHandle() const
{
   return m_event.GetWaitHandle();
}

void CAutoResetEvent::Wait() const
{
   m_event.Wait();
}

bool CAutoResetEvent::Wait(
   const Milliseconds timeout) const
{
   return m_event.Wait(timeout);
}
 
} // End of namespace Win32
} // End of namespace AmstelTech 