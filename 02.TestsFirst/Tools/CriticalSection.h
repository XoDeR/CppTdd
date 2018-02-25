#pragma once

#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
#endif

namespace AmstelTech 
{
	
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// CCriticalSection
///////////////////////////////////////////////////////////////////////////////

class CCriticalSection 
{
   public :
   
      class Owner
      {
         public:

            explicit Owner(
               CCriticalSection &crit);

            ~Owner();
      
         private :

            CCriticalSection &m_crit;

            // No copies do not implement
            Owner(const Owner &rhs);
            Owner &operator=(const Owner &rhs);
      };

      class ConditionalOwner
      {
         public:

            ConditionalOwner(
               CCriticalSection &crit,
               bool look);

            ~ConditionalOwner();
      
         private :

            CCriticalSection &m_crit;

            const bool m_lock;

            // No copies do not implement
            ConditionalOwner(const ConditionalOwner &rhs);
            ConditionalOwner &operator=(const ConditionalOwner &rhs);
      };

      CCriticalSection();
	  
	  explicit CCriticalSection(       // only actually does anything if > NT 4 Sp3
         const size_t spinCount); 
      
      ~CCriticalSection();

#if(_WIN32_WINNT >= 0x0400)
      bool TryEnter();
#endif
      void Enter();

      void Leave();

   private :

      CRITICAL_SECTION m_crit;

      // No copies do not implement
      CCriticalSection(const CCriticalSection &rhs);
      CCriticalSection &operator=(const CCriticalSection &rhs);
};

} // End of namespace Win32
} // End of namespace AmstelTech 
