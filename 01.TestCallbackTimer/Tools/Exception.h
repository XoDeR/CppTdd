#pragma once

#pragma warning(disable: 4201)   // nameless struct/union

#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
#endif

#include "tstring.h"

#pragma warning(default: 4201)

namespace AmstelTech 
{
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// CException
///////////////////////////////////////////////////////////////////////////////

class CException
{
   public : 

      CException(
         const _tstring &where, 
         const _tstring &message);

      virtual ~CException() {}

      virtual _tstring GetWhere() const;

      virtual _tstring GetMessage() const; 

      void MessageBox(
         HWND hWnd = NULL) const; 

   protected :
      
      const _tstring m_where;
      const _tstring m_message;
};

} // End of namespace Win32
} // End of namespace AmstelTech 