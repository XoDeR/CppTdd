#pragma once

#include "tstring.h"

namespace AmstelTech 
{
	
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// IKernelObjectName
///////////////////////////////////////////////////////////////////////////////

class IKernelObjectName
{
   public :

      virtual _tstring GetName() const = 0;

      virtual bool IsGlobalName() const = 0;

      virtual bool IsLocalName() const = 0;

      virtual bool IsUnqualifiedName() const = 0;

   protected :

		/// We never delete instances of this interface; you must manage the 
		/// lifetime of the class that implements it.

      ~IKernelObjectName() {}
};

} // End of namespace Win32
} // End of namespace AmstelTech 
