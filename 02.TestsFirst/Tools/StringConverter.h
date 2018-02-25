#pragma once

#include "tstring.h"

#include <objbase.h>

namespace AmstelTech 
{
	
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// CStringConverter
///////////////////////////////////////////////////////////////////////////////

class CStringConverter
{
   public :
      
      static _tstring AtoT(
         const std::string &input);

      static std::string TtoA(
         const _tstring &input);

      static _tstring WtoT(
         const std::wstring &input);

      static std::wstring TtoW(
         const _tstring &input);

      static std::wstring AtoW(
         const std::string &input);

      static std::string WtoA(
         const std::wstring &input);

      static std::string BSTRtoA(
	      const BSTR bstr);

      static _tstring BSTRtoT(
	      const BSTR bstr);

      static std::wstring BSTRtoW(
	      const BSTR bstr);
};

} // End of namespace Win32
} // End of namespace AmstelTech 