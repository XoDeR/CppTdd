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
         const Milliseconds tickCount);
	  
      void SetTickCount(
         const Milliseconds tickCount);

      // Implement IProvideTickCount

      virtual Milliseconds GetTickCount() const;

   private :

      volatile Milliseconds m_tickCount;
	  
      // No copies do not implement
      CMockTickCountProvider(const CMockTickCountProvider &rhs);
      CMockTickCountProvider &operator=(const CMockTickCountProvider &rhs);
};

} // End of namespace Mock
} // End of namespace Win32
} // End of namespace AmstelTech 