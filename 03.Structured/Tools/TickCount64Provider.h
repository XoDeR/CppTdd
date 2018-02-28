#pragma once

#include "IProvideTickCount64.h"

///////////////////////////////////////////////////////////////////////////////
// Requires Windows Vista or later due to use of GetTickCount64()
///////////////////////////////////////////////////////////////////////////////

#if (_WIN32_WINNT >= 0x0600) 

namespace AmstelTech 
{
	
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// CTickCount64Provider
///////////////////////////////////////////////////////////////////////////////

class CTickCount64Provider: public IProvideTickCount64
{
   public : 

      virtual ULONGLONG GetTickCount64() const
      {
         return ::GetTickCount64();
      }
};

} // End of namespace Win32
} // End of namespace AmstelTech

///////////////////////////////////////////////////////////////////////////////
// Requires Windows Vista or later due to use of GetTickCount64()
///////////////////////////////////////////////////////////////////////////////

#endif // (_WIN32_WINNT >= 0x0600)