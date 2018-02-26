#pragma once

#include <wtypes.h>

#include "IWaitable.h"

namespace AmstelTech 
{
	
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// CSmartHandle
///////////////////////////////////////////////////////////////////////////////

/// A SmartPointer "smart pointer" to a HANDLE. Calls ::CloseHandle() on 
/// any HANDLE that the it owns when the CSmartHandle goes out of scope to aid 
/// in RAII "scope based" designs.

class CSmartHandle : public IWaitable
{
   public :
   
      /// Duplicate the owned handle with the same access for use within the 
      /// same process. 

      static CSmartHandle DuplicateHandle(
         HANDLE hInput);

      /// Construct a CSmartHandle that doesn't, currently, own a HANDLE.

      CSmartHandle();

      /// Construct a CSmartHandle that takes ownership of the supplied HANDLE.

      explicit CSmartHandle(
         HANDLE handle);

      CSmartHandle(
         const CSmartHandle &rhs);

      ~CSmartHandle();

      CSmartHandle &operator=(
         const HANDLE handle);

      CSmartHandle &operator=(
         const CSmartHandle &rhs);

      /// Access the HANDLE... We should remove this...

      operator HANDLE() const;

      HANDLE &GetHandle();

      HANDLE GetHandle() const;

      /// Take ownership of the supplied HANDLE.

      void Attach(
         HANDLE handle);

      /// No longer manage ownership of the HANDLE and return it.

      HANDLE Detach();

      /// Duplicate the owned handle with the same access for use within the 
      /// same process. 

      CSmartHandle DuplicateHandle() const;

      /// Close any handle that is managed by this CSmartHandle.
      
      void Close();

      /// Returns true if the CSmartHandle currently has ownership of a HANDLE.
      
      bool IsValid() const;

      // Implement IWaitable

      virtual HANDLE GetWaitHandle() const;

      virtual void Wait() const;

      virtual bool Wait(
         const Milliseconds timeoutMillis) const;

   private :

      HANDLE m_handle;
};

} // End of namespace Win32
} // End of namespace AmstelTech 
