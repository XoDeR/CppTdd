#pragma once

#include <wtypes.h>

#include "ICriticalSection.h"

namespace AmstelTech 
{
	
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// CCriticalSection
///////////////////////////////////////////////////////////////////////////////

class CCriticalSection : public ICriticalSection
{
   public :
   
      /// Creates a critical section object.

      CCriticalSection();

      /// Creates a critical section object and allows you to specify the spin 
      /// count.

      explicit CCriticalSection(       
         const DWORD spinCount);      
      
      ~CCriticalSection();

      void SetSpinCount(
         const DWORD spinCount);      

      // Implement ICriticalSection

      virtual void Enter();

      virtual void Leave();

//#if(_WIN32_WINNT >= 0x0400)
//      bool TryEnter();
//#endif

   private :

      CRITICAL_SECTION m_crit;

		/// No copies do not implement
      CCriticalSection(const CCriticalSection &rhs);
		/// No copies do not implement
      CCriticalSection &operator=(const CCriticalSection &rhs);
};

} // End of namespace Win32
} // End of namespace AmstelTech 
