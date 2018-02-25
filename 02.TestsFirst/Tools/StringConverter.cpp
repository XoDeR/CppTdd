#include "StringConverter.h"

#include "Win32Exception.h"

namespace AmstelTech 
{

namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// Static helper functions 
///////////////////////////////////////////////////////////////////////////////

static std::wstring InternalAtoW(
   const char *pInput,
   const size_t inputLength);

static std::string InternalWtoA(
   const wchar_t *pInput,
   const size_t inputLength);

///////////////////////////////////////////////////////////////////////////////
// CStringConverter
///////////////////////////////////////////////////////////////////////////////

_tstring CStringConverter::AtoT(
   const std::string &input)
{
#ifdef _UNICODE
	return AtoW(input);
#else
	return input;
#endif
}

std::string CStringConverter::TtoA(
   const _tstring &input)
{
#ifdef _UNICODE
	return WtoA(input);
#else
	return input;
#endif
}

std::wstring CStringConverter::TtoW(
   const _tstring &input)
{
#ifdef _UNICODE
	return input;
#else
	return AtoW(input);
#endif
}

_tstring CStringConverter::WtoT(
   const std::wstring &input)
{
#ifdef _UNICODE
	return input;
#else
	return WtoA(input);
#endif
}

std::string CStringConverter::BSTRtoA(
	const BSTR bstr)
{
	if (::SysStringLen(bstr) == 0)
	{
		return "";
	}

   return InternalWtoA(bstr, ::SysStringLen(bstr));
}

_tstring CStringConverter::BSTRtoT(
	const BSTR bstr)
{
	if (::SysStringLen(bstr) == 0)
	{
		return _T("");
	}

#ifdef _UNICODE
   return bstr;
#else
	return InternalWtoA(bstr, ::SysStringLen(bstr));
#endif
}

std::wstring CStringConverter::BSTRtoW(
	const BSTR bstr)
{
	if (::SysStringLen(bstr) == 0)
	{
		return L"";
	}

   return bstr;
}

std::wstring CStringConverter::AtoW(
   const std::string &input)
{
	return InternalAtoW(input.c_str(), input.length());
}

std::string CStringConverter::WtoA(
   const std::wstring &input)
{
	return InternalWtoA(input.c_str(), input.length());
}

///////////////////////////////////////////////////////////////////////////////
// Static helper functions 
///////////////////////////////////////////////////////////////////////////////

static std::wstring InternalAtoW(
   const char *pInput,
   const size_t inputLength)
{
	std::wstring result;

   if (inputLength != 0)
   {
	   result.resize(inputLength);

	   if (0 ==::MultiByteToWideChar(CP_ACP, 0, pInput, inputLength, const_cast<wchar_t *>(result.c_str()), result.length()))
	   {
		   throw CWin32Exception(_T("CStringConverter::AtoW()"), ::GetLastError());
	   }
   }

	return result;
}

static std::string InternalWtoA(
   const wchar_t *pInput,
   const size_t inputLength)
{
	std::string result;

	if (inputLength != 0)
	{
		result.resize(inputLength);

		if (0 == ::WideCharToMultiByte(CP_ACP, 0, pInput, inputLength, const_cast<char *>(result.c_str()), result.length() + 1, 0, 0))
		{
			throw CWin32Exception(_T("CStringConverter::WtoA()"), ::GetLastError());
		}
	}

	return result;
}

} // End of namespace Win32
} // End of namespace AmstelTech 

