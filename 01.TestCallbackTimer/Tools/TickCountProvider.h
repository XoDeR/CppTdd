#pragma once

#include "IProvideTickCount.h"

namespace AmstelTech 
{
	
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// CTickCountProvider
///////////////////////////////////////////////////////////////////////////////

class CTickCountProvider: public IProvideTickCount
{
   public : 

      virtual DWORD GetTickCount() const
      {
         return ::GetTickCount();
      }
};

} // End of namespace Win32
} // End of namespace AmstelTech 