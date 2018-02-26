#include "../Platform/Platform.h"

#include "Win32Exception.h"
#include "Utils.h"

namespace AmstelTech 
{
	
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// CWin32Exception
///////////////////////////////////////////////////////////////////////////////

CWin32Exception::CWin32Exception(
   const _tstring &where, 
   DWORD error)
   :  CException(where, GetLastErrorMessage(error)),
      m_error(error)
{
}

CWin32Exception::CWin32Exception(
   const _tstring &where, 
   const _tstring &message)
   :  CException(where, message),
      m_error(NO_ERROR)
{
}

DWORD CWin32Exception::GetError() const 
{ 
   return m_error; 
}

} // End of namespace Win32
} // End of namespace AmstelTech