#pragma once

#include "Exception.h"

namespace AmstelTech 
{
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// CWin32Exception
///////////////////////////////////////////////////////////////////////////////

class CWin32Exception : public CException
{
   public : 

      CWin32Exception(
         const _tstring &where, 
         DWORD error);

      CWin32Exception(
         const _tstring &where, 
         const _tstring &message);

      DWORD GetError() const;

   protected :
      
      DWORD m_error;
};

} // End of namespace Win32
} // End of namespace AmstelTech 