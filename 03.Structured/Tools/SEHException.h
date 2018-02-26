#pragma once

#include <wtypes.h>

#include "tstring.h"

namespace AmstelTech 
{
	
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// CSEHException
///////////////////////////////////////////////////////////////////////////////

/// A exception class used by a structured exception translator to translate
/// Win32 structured exceptions into C++ exceptions.
/// Note that it's a deliberate choice not to derive from CException. Win32
/// structured exceptions include things like "Stack Overflow" so you want to
/// be sure you know what you're doing if you catch one... We could split the
/// SE exception into two, ones we might be able to recover from and those that
/// we can't recover from and derive the ones we might be able to recover from
/// from CException, but...
class CSEHException 
{
   public : 

      class Translator;

      friend class Translator;

      unsigned int GetCode() const;
	  
	  const EXCEPTION_POINTERS &GetExceptionPointers() const;

      const CONTEXT &GetContext() const;

      _tstring GetWhere() const;

      _tstring GetMessage() const; 

   protected :
      
      const _tstring m_where;
      const _tstring m_message;

      const unsigned int m_code;
	  
	  EXCEPTION_POINTERS *m_pPointers;

   private :

      CSEHException(
         unsigned int code, 
         EXCEPTION_POINTERS *pPointers);

};

/// A class that acts as a structured exception translator.
/// Create one of these objects on each thread where you want Win32 structured 
/// exceptions translated into CSEHException.
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