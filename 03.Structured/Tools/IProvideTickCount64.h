#pragma once

#include <wtypes.h>

namespace AmstelTech 
{
	
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// IProvideTickCount64
///////////////////////////////////////////////////////////////////////////////

class IProvideTickCount64
{
   public : 

      /// Returns the current tick count.

      virtual ULONGLONG GetTickCount64() const = 0;

   protected :

		/// We never delete instances of this interface; you must manage the 
		/// lifetime of the class that implements it.
      
      ~IProvideTickCount64() {}
};

} // End of namespace Win32
} // End of namespace AmstelTech