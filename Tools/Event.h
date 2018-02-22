#pragma once

#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
#endif

#include "tstring.h"

namespace AmstelTech 
{

namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// CEvent
///////////////////////////////////////////////////////////////////////////////

class CEvent 
{
   public :
   
      CEvent(
         LPSECURITY_ATTRIBUTES lpSecurityAttributes,
         bool manualReset,
         bool initialState);
   
      CEvent(
         LPSECURITY_ATTRIBUTES lpSecurityAttributes,
         bool manualReset,
         bool initialState,
         const _tstring &name);
      
      virtual ~CEvent();
      HANDLE GetEvent() const;
      void Wait() const;
      bool Wait(DWORD timeoutMillis) const;
      void Reset();
      void Set();
      void Pulse();
   private :
      HANDLE m_hEvent;

      // No copies do not implement
      CEvent(const CEvent &rhs);
      CEvent &operator=(const CEvent &rhs);
};

} // End of namespace Win32
} // End of namespace AmstelTech 

