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
      
      // Ato

      static _tstring AtoT(
         const std::string &input);

      static _tstring AtoT(
         const char *pInput);

      static _tstring AtoT(
         const char *pInput,
         const int inputLength);

      static std::wstring AtoW(
         const std::string &input);

      static std::wstring AtoW(
         const char *pInput);

      static std::wstring AtoW(
         const char *pInput,
         const int inputLength);

      static BSTR AtoBSTR(
         const std::string &input);

      static BSTR AtoBSTR(
         const char *pInput,
         const int inputLength);

      // Wto

      static _tstring WtoT(
         const std::wstring &input);

      static _tstring WtoT(
         const wchar_t *pInput);

      static _tstring WtoT(
         const wchar_t *pInput,
         const int inputLength);

      static std::string WtoA(
         const std::wstring &input);

      static std::string WtoA(
         const wchar_t *pInput);

      static std::string WtoA(
         const wchar_t *pInput,
         const int inputLength);

      static BSTR WtoBSTR(
         const std::wstring &input);

      // Tto

      static std::string TtoA(
         const _tstring &input);

      static std::wstring TtoW(
         const _tstring &input);

      static BSTR TtoBSTR(
         const _tstring &input);

      // BSTRto

      static _tstring BSTRtoT(
	      const BSTR bstr);

      static std::string BSTRtoA(
	      const BSTR bstr);

      static std::wstring BSTRtoW(
	      const BSTR bstr);

      // UTF8to

      static std::wstring UTF8toW(
         const std::string &input);
};

} // End of namespace Win32
} // End of namespace AmstelTech 