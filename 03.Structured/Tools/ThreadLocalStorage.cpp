#include "../Platform/Platform.h"

#include "ThreadLocalStorage.h"
#include "Win32Exception.h"
#include "Utils.h"
#include "DebugTrace.h"

namespace AmstelTech 
{
	
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// CThreadLocalStorage
///////////////////////////////////////////////////////////////////////////////

CThreadLocalStorage::CThreadLocalStorage()
   :  m_index(::TlsAlloc()),
      m_owner(true)
{
   if (m_index == TLS_OUT_OF_INDEXES)
   {
      throw CWin32Exception(_T("CThreadLocalStorage::CThreadLocalStorage()"), ::GetLastError());
   }
}

CThreadLocalStorage::CThreadLocalStorage(
   DWORD tlsIndex)
   :  m_index(tlsIndex),
      m_owner(false)
{
}

CThreadLocalStorage::~CThreadLocalStorage()
{
   try
   {
      if (m_owner)
      {
         if (0 == ::TlsFree(m_index))
         {
            DEBUG_ONLY(Output(_T("~CThreadLocalStorage() - error:") + GetLastErrorMessage(::GetLastError())));
         }
      }
   }
   catch(...)
   {
   }
}

DWORD CThreadLocalStorage::GetIndex() const
{
   return m_index;
}

void CThreadLocalStorage::SetValue(
   void *pValue) const
{
   if (0 == ::TlsSetValue(m_index, pValue))
   {
      throw CWin32Exception(_T("CThreadLocalStorage::SetValue()"), ::GetLastError());
   }
}

void *CThreadLocalStorage::GetValue() const
{
   void *pV = ::TlsGetValue(m_index);

   if (pV == 0)
   {
      DWORD lastError = ::GetLastError();

      if (lastError != NO_ERROR)
      {
         throw CWin32Exception(_T("CThreadLocalStorage::GetValue()"), ::GetLastError());
      }
   }
   
   return pV;
}

} // End of namespace Win32
} // End of namespace AmstelTech