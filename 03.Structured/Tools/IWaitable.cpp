#include "../Platform/Platform.h"

#include "IWaitable.h"
#include "Win32Exception.h"

namespace AmstelTech 
{
	
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// IWaitable
///////////////////////////////////////////////////////////////////////////////

void IWaitable::Wait(
   HANDLE handle)
{
   if (!Wait(handle, INFINITE))
   {
      throw CException(_T("IWaitable::Wait()"), _T("Unexpected timeout on infinite wait"));
   }
}

bool IWaitable::Wait(
   HANDLE handle,
   const Milliseconds timeout)
{
   if (handle == INVALID_HANDLE_VALUE)
   {
      throw CException(_T("IWaitable::Wait()"), _T("Handle is invalid"));
   }

   bool ok;

   DWORD result = ::WaitForSingleObject(handle, timeout);

   if (result == WAIT_TIMEOUT)
   {
      ok = false;
   }
   else if (result == WAIT_OBJECT_0)
   {
      ok = true;
   }
   else
   {
      throw CWin32Exception(_T("IWaitable::Wait() - WaitForSingleObject"), ::GetLastError());
   }
    
   return ok;
}   

} // End of namespace Win32
} // End of namespace AmstelTech 
