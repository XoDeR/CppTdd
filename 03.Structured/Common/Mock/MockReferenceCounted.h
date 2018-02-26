#pragma once

#include "../../TestTools/TestLog.h"

namespace AmstelTech 
{
	
namespace Mock 
{

///////////////////////////////////////////////////////////////////////////////
// CMockReferenceCounted
///////////////////////////////////////////////////////////////////////////////

/// A mock object that implements AddRef() and Release() and so can be used
/// where reference counted objects might be required.
class CMockReferenceCounted : public AmstelTech::Test::CTestLog
{
   public :

      CMockReferenceCounted();

      void AddRef();

      void Release();

   private :

      long m_ref;
};
  
} // End of namespace Mock
} // End of namespace AmstelTech