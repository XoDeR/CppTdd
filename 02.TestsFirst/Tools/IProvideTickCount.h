#pragma once

#include <wchar.h>

namespace AmstelTech 
{
	
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// IProvideTickCount
///////////////////////////////////////////////////////////////////////////////

class IProvideTickCount
{
   public : 

      virtual DWORD GetTickCount() const = 0;

   protected :
      
      ~IProvideTickCount() {}
};

} // End of namespace Win32
} // End of namespace AmstelTech 