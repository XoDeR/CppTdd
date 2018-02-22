#pragma once

#include "tstring.h"

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
      
      static std::string TtoA(
         const _tstring &input);

      static std::wstring TtoW(
         const _tstring &input);

      static _tstring AtoT(
         const std::string &input);

      static std::wstring AtoW(
         const std::string &input);

      static _tstring WtoT(
         const std::wstring &input);
};

} // End of namespace Win32
} // End of namespace AmstelTech 