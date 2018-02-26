#pragma once

#include <wtypes.h>

#include "tstring.h"

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