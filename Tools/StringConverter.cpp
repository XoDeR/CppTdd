#include "StringConverter.h"

#include <atlbase.h> // USES_CONVERSION

namespace AmstelTech 
{

namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// CStringConverter
///////////////////////////////////////////////////////////////////////////////

_tstring CStringConverter::AtoT(
   const std::string &input)
{
   USES_CONVERSION;

   return A2T(const_cast<char *>(input.c_str()));
}

std::string CStringConverter::TtoA(
   const _tstring &input)
{
   USES_CONVERSION;

   return T2A(const_cast<TCHAR *>(input.c_str()));
}

std::wstring CStringConverter::TtoW(
   const _tstring &input)
{
   USES_CONVERSION;

   return T2W(const_cast<TCHAR *>(input.c_str()));
}

std::wstring CStringConverter::AtoW(
   const std::string &input)
{
   USES_CONVERSION;

   return A2W(const_cast<char *>(input.c_str()));
}

_tstring CStringConverter::WtoT(
   const std::wstring &input)
{
   USES_CONVERSION;

   return W2T(const_cast<wchar_t *>(input.c_str()));
}

} // End of namespace Win32
} // End of namespace AmstelTech 

