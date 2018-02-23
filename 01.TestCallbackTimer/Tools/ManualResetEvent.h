#pragma once

#include "Event.h"

namespace AmstelTech 
{

namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// CManualResetEvent
///////////////////////////////////////////////////////////////////////////////

class CManualResetEvent : public CEvent
{
   public :
   
      explicit CManualResetEvent(
         bool initialState = false);
      
      explicit CManualResetEvent(
         const _tstring &name, 
         bool initialState = false);

   private :

      // No copies do not implement
      CManualResetEvent(const CManualResetEvent &rhs);
      CManualResetEvent &operator=(const CManualResetEvent &rhs);
};

} // End of namespace Win32
} // End of namespace AmstelTech 