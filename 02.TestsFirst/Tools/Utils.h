#pragma once

#pragma warning(disable: 4201)   // nameless struct/union

#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN
#endif

#include "tstring.h"
#include "StringConverter.h"

#include <strstream>

#pragma warning(default: 4201)

namespace AmstelTech 
{
namespace Win32 
{

#ifndef DEBUG_ONLY
#ifdef _DEBUG
#define DEBUG_ONLY(x)   x
#else
#define DEBUG_ONLY(x)
#endif
#endif

// Converts a type to a _tstring.
// Convert a type to a string by streaming it. Requires that there's an ostream
// inserter available for type T.
template <class T>
_tstring ToString(T num)
{
	_tstring strNum = _T("");

   {
      std::strstream buf;

	   buf << num << std::ends;

#ifdef _UNICODE
      std::string temp = buf.str();

      strNum = CStringConverter::AtoW(temp);
#else 
	   strNum = buf.str();
#endif
	   buf.freeze(false);
   }

   return strNum;

   // parameter num could be declared as a pointer to const
}

template <class T>
std::string ToStringA(T num)
{
   std::strstream buf;

	buf << num << std::ends;

   std::string strNum = buf.str();

   buf.freeze(false);

   return strNum;

   // parameter num could be declared as a pointer to const
}

template <class T>
std::wstring ToStringW(T num)
{
   std::strstream buf;

	buf << num << std::ends;

   std::string temp = buf.str();

   std::wstring strNum = CStringConverter::AtoW(temp);

   buf.freeze(false);

   return strNum;

   // parameter num could be declared as a pointer to const
}

template <class T>
_tstring ToHexString(T num)
{
   return HexToString((const BYTE *)&num, sizeof(T));
}

template <class T>
bool ToBool(const T &value)
{
   return (0 != value);
}

_tstring HexToString(
   const BYTE *pBuffer, 
   size_t iBytes);

std::string HexToStringA(
   const BYTE *pBuffer, 
   size_t iBytes,
   bool upperCase = true);

void StringToHex(
   const _tstring &str, 
   BYTE *pBuffer, 
   size_t nBytes);

_tstring GetLastErrorMessage(
   DWORD last_error);

std::string GetLastErrorMessageA(
   DWORD last_error);

_tstring GetCurrentDirectory();

_tstring GetDateStamp();

_tstring GetTimeStamp();

std::string GetTimeStampA();

void SetLogFileName(
   const _tstring &name);

void Output(
   const std::string &message);

void Output(
   const std::wstring &message);

void OutputEx(
   const std::string &message);

void OutputEx(
   const std::wstring &message);

_tstring ToHex(BYTE c);

std::string ToHexA(BYTE c);

std::string ToUpper(
   const std::string &data);

_tstring MakePrintable(
   const BYTE * const pData, 
   size_t dataLength, 
   size_t lineLength = 0);

_tstring DumpData(
   const BYTE * const pData, 
   size_t dataLength, 
   size_t lineLength = 0);

std::string DumpDataA(
   const BYTE * const pData, 
   size_t dataLength, 
   size_t lineLength = 0);

_tstring DumpData(
   const _tstring &linePrefix,
   const BYTE * const pData, 
   size_t dataLength, 
   size_t lineLength = 0);

std::string DumpDataA(
   const std::string &linePrefix,
   const BYTE * const pData, 
   size_t dataLength, 
   size_t lineLength = 0);

_tstring GetComputerName();

_tstring GetModuleFileName(
   HINSTANCE hModule = 0);

_tstring GetUserName();

_tstring GetFileVersion();

_tstring StripLeading(
   const _tstring &source, 
   const char toStrip);

_tstring StripTrailing(
   const _tstring &source, 
   const char toStrip);
   
std::string LoadFileAsStringA(
   const _tstring &filename);

void SaveStringAsFile(
   const _tstring &filename,
   const std::string &data);

} // End of namespace Win32
} // End of namespace AmstelTech 


