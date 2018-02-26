#pragma once

#include <wtypes.h>

namespace AmstelTech 
{
	
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// CThreadLocalStorage
///////////////////////////////////////////////////////////////////////////////

class CThreadLocalStorage 
{
   public :

      /// Allocates and becomes the owner of a thread local storage slot. 
      /// Throws an exception if there are no more TLS slots available.

      CThreadLocalStorage();

      /// Connects to an existing TLS slot.

      explicit CThreadLocalStorage(
         DWORD tlsIndex);
   
      /// If this object owns the TLS slot then it releases it.

      ~CThreadLocalStorage();

      /// Returns the object's TLS index.

      DWORD GetIndex() const;

      /// Sets the value of the TLS slot.

      void SetValue(void *pValue) const;

      /// Returns the stored value of the TLS slot.

      void *GetValue() const;

   private :

      const DWORD m_index;

      const bool m_owner;

      /// No copies do not implement
      CThreadLocalStorage(const CThreadLocalStorage &rhs);
      /// No copies do not implement
      CThreadLocalStorage &operator=(const CThreadLocalStorage &rhs);
};

} // End of namespace Win32
} // End of namespace AmstelTech