#include "../../Platform/Platform.h"
#include "TestException.h"

using AmstelTech::Win32::CException;
using AmstelTech::Win32::_tstring;

namespace AmstelTech 
{
	
namespace Test 
{

///////////////////////////////////////////////////////////////////////////////
// CTestException
///////////////////////////////////////////////////////////////////////////////

CTestException::CTestException(
   const _tstring &message)
   :  CException(_T(""), message)
{
}

CTestException::CTestException(
   const _tstring &where, 
   const _tstring &message)
   :  CException(where, message)
{
}

} //-- namespace Test
} //-- namespace AmstelTech 