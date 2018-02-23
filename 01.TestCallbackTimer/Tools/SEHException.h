#pragma once

#pragma warning(disable: 4201)   // nameless struct/union

#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
#endif

#include "tstring.h"

#pragma warning(default: 4201)

namespace AmstelTech 
{
	
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// CSEHException
///////////////////////////////////////////////////////////////////////////////

class CSEHException 
{
   public : 

      class Translator;

      friend class Translator;

      unsigned int GetCode() const;

      _tstring GetWhere() const;

      _tstring GetMessage() const; 

   protected :
      
      const _tstring m_where;
      const _tstring m_message;

      const unsigned int m_code;

   private :

      CSEHException(
         unsigned int code, 
         EXCEPTION_POINTERS *pPointers);

};

class CSEHException::Translator
{
   public :
   
      Translator();
   
      ~Translator();

   private :

      static void trans_func(
         unsigned int code, 
         EXCEPTION_POINTERS *pPointers); 

      _se_translator_function m_prev;
};

} // End of namespace Win32
} // End of namespace AmstelTech