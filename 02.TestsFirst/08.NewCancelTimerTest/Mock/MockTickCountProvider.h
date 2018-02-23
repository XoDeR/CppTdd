#pragma once

#include "../../TestTools/TestLog.h"

#include "../../Tools/IProvideTickCount.h"

namespace AmstelTech 
{
	
namespace Win32 
{
	
namespace Mock 
{

///////////////////////////////////////////////////////////////////////////////
// CMockTickCountProvider
///////////////////////////////////////////////////////////////////////////////

class CMockTickCountProvider : public IProvideTickCount, public AmstelTech::Test::CTestLog
{
   public:
      CMockTickCountProvider();
	  
	  explicit CMockTickCountProvider(
         const DWORD tickCount);
	  
      void SetTickCount(
         const DWORD tickCount);

      // Implement IProvideTickCount

      virtual DWORD GetTickCount() const;

   private :

      volatile DWORD m_tickCount;
	  
      // No copies do not implement
      CMockTickCountProvider(const CMockTickCountProvider &rhs);
      CMockTickCountProvider &operator=(const CMockTickCountProvider &rhs);
};

} // End of namespace Mock
} // End of namespace Win32
} // End of namespace AmstelTech 