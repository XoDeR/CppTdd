#pragma once

#include "../../Platform/Types.h"

#include "../../TestTools/TestLog.h"

#include "../../Tools/IProvideTickCount64.h"

namespace AmstelTech 
{
	
namespace Win32 
{
	
namespace Mock 
{

///////////////////////////////////////////////////////////////////////////////
// CMockTickCount64Provider
///////////////////////////////////////////////////////////////////////////////

/// A mock object that implements IProvideTickCount64 and provides a tick count
/// that can be controlled from within the test.

class CMockTickCount64Provider : 
   public IProvideTickCount64,
   public AmstelTech::Test::CTestLog
{
   public : 

      CMockTickCount64Provider();

      /// Construct a tick count provider with the specified tick count. All
      /// calls to GetTickCount54() will return this value.

      explicit CMockTickCount64Provider(
         const ULONGLONG tickCount); 

      /// Change the tick count that the provider will return from calls to 
      /// GetTickCount64().

      void SetTickCount(
         const ULONGLONG tickCount);

      // Implement IProvideTickCount64

      virtual ULONGLONG GetTickCount64() const;

   private :

      volatile ULONGLONG m_tickCount;

      // No copies do not implement
      CMockTickCount64Provider(const CMockTickCount64Provider &rhs);
      CMockTickCount64Provider &operator=(const CMockTickCount64Provider &rhs);
};

} // End of namespace Mock
} // End of namespace Win32
} // End of namespace AmstelTech