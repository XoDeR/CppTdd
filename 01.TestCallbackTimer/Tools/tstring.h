#pragma once

#include <string>
#include <tchar.h>

namespace AmstelTech 
{
namespace Win32 
{

#ifdef _UNICODE
typedef std::wstring _tstring;
#else
typedef std::string _tstring;
#endif

} // End of namespace Win32
} // End of namespace AmstelTech 