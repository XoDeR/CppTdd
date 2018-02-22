#pragma once

#include "Event.h"

namespace AmstelTech 
{
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// CAutoResetEvent
///////////////////////////////////////////////////////////////////////////////

class CAutoResetEvent : public CEvent
{
   public :
      explicit CAutoResetEvent(bool initialState = false);
      explicit CAutoResetEvent(const _tstring &name, bool initialState = false);
   private :
      // No copies do not implement
      CAutoResetEvent(const CAutoResetEvent &rhs);
      CAutoResetEvent &operator=(const CAutoResetEvent &rhs);
};

} // End of namespace Win32
} // End of namespace AmstelTech 