#pragma once

#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
#endif

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