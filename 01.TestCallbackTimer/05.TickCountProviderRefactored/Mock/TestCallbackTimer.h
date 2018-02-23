#pragma once

#include "MockTickCountProvider.h"

#include "../../Tools/CallbackTimer.h"

namespace AmstelTech 
{
	
namespace Win32 
{
	
namespace Mock 
{

///////////////////////////////////////////////////////////////////////////////
// CTestCallbackTimer
///////////////////////////////////////////////////////////////////////////////

class CTestCallbackTimer : 
   public CMockTickCountProvider,
   public CCallbackTimer
{
   public :

      explicit CTestCallbackTimer(
         const DWORD tickCount,
         const DWORD operationTimeoutMillis);

      ~CTestCallbackTimer();

      void SetTimerAndWait(
         CCallbackTimer::Handle &handle,
         const DWORD timeoutMillis,
         const DWORD userData);

      void SetTickCountAndWait(
         const DWORD tickCount,
         const bool waitForBlock);

   private :

      const DWORD m_operationTimeoutMillis;

      _tstring m_tickCountAsString;

      // No copies do not implement
      CTestCallbackTimer(const CTestCallbackTimer &rhs);
      CTestCallbackTimer &operator=(const CTestCallbackTimer &rhs);
};

} // End of namespace Mock
} // End of namespace Win32
} // End of namespace AmstelTech