#include "../Platform/Platform.h"

#include "Event.h"
#include "IKernelObjectName.h"
#include "Win32Exception.h"

namespace AmstelTech 
{
	
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// Static helper methods
///////////////////////////////////////////////////////////////////////////////

static HANDLE Create(
   SECURITY_ATTRIBUTES *pEventAttributes, 
   bool bManualReset, 
   bool bInitialState, 
   LPCTSTR lpName,
   const CEvent::CreationFlags creationFlags);

static HANDLE Create(
   SECURITY_ATTRIBUTES *pEventAttributes, 
   LPCTSTR lpName);

///////////////////////////////////////////////////////////////////////////////
// CEvent
///////////////////////////////////////////////////////////////////////////////

CEvent::CEvent(
   SECURITY_ATTRIBUTES *pEventAttributes, 
   ResetType resetType, 
   InitialState initialState)
   :  m_hEvent(Create(pEventAttributes, (resetType == ManualReset), (initialState == Signaled), 0, CEvent::CreateOrConnect))
{

}

CEvent::CEvent(
   SECURITY_ATTRIBUTES *pEventAttributes, 
   ResetType resetType, 
   InitialState initialState,
   const IKernelObjectName &name,
   const CreationFlags creationFlags)
   :  m_hEvent(Create(pEventAttributes, (resetType == ManualReset), (initialState == Signaled), name.GetName().c_str(), creationFlags))
{

}

CEvent::CEvent(
   SECURITY_ATTRIBUTES *pEventAttributes, 
   const IKernelObjectName &name)
   :  m_hEvent(Create(pEventAttributes, name.GetName().c_str()))
{

}

void CEvent::Reset()
{
   if (!::ResetEvent(m_hEvent))
   {
      throw CWin32Exception(_T("CEvent::Reset()"), ::GetLastError());
   }
}

void CEvent::Set()
{
   if (!::SetEvent(m_hEvent))
   {
      throw CWin32Exception(_T("CEvent::Set()"), ::GetLastError());
   }
}

void CEvent::Pulse()
{
   if (!::PulseEvent(m_hEvent))
   {
      throw CWin32Exception(_T("CEvent::Pulse()"), ::GetLastError());
   }
}

HANDLE CEvent::GetWaitHandle() const
{
   return m_hEvent;
}

void CEvent::Wait() const
{
   IWaitable::Wait(m_hEvent);
}

bool CEvent::Wait(
   const Milliseconds timeout) const
{
   return IWaitable::Wait(m_hEvent, timeout);
}

///////////////////////////////////////////////////////////////////////////////
// Static helper methods
///////////////////////////////////////////////////////////////////////////////

static HANDLE Create(
   SECURITY_ATTRIBUTES *pEventAttributes, 
   LPCTSTR lpName)
{
   static const bool notUsedWhenConnecting = false;

   return Create(pEventAttributes, notUsedWhenConnecting, notUsedWhenConnecting, lpName, CEvent::ConnectToExisting);
}


static HANDLE Create(
   SECURITY_ATTRIBUTES *pEventAttributes, 
   bool bManualReset, 
   bool bInitialState, 
   LPCTSTR lpName,
   const CEvent::CreationFlags creationFlags)
{
   ::SetLastError(ERROR_SUCCESS);

   CSmartHandle hEvent(::CreateEvent(pEventAttributes, bManualReset, bInitialState, lpName));

   const DWORD lastError = ::GetLastError();

   if (hEvent == NULL)
   {
      throw CWin32Exception(_T("CEvent::Create()"), lastError);
   }

   if (creationFlags == CEvent::CreateNew)
   {
      if (lastError == ERROR_ALREADY_EXISTS)
      {
         throw CWin32Exception(_T("CEvent::Create()"), lastError);
      }
   }
   else if (creationFlags == CEvent::ConnectToExisting)
   {
      if (lastError != ERROR_ALREADY_EXISTS)
      {
         throw CWin32Exception(_T("CEvent::Create()"), ERROR_NOT_FOUND);
      }
   }

   return hEvent.Detach();
}

} // End of namespace Win32
} // End of namespace AmstelTech 