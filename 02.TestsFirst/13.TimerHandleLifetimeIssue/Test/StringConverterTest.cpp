#include "StringConverterTest.h"

#include "../../Tools/StringConverter.h"

#include "../../Tools/Utils.h"

#include "../../TestTools/TestException.h"

using AmstelTech::Test::CTestException;

using std::string;
using std::wstring;

namespace AmstelTech 
{
	
namespace Win32 
{
	
namespace Test 
{

///////////////////////////////////////////////////////////////////////////////
// CStringConverterTest
///////////////////////////////////////////////////////////////////////////////

void CStringConverterTest::TestAll()
{
   TestAtoW();
}

void CStringConverterTest::TestAtoW()
{
   const _tstring functionName = _T("CStringConverterTest::TestAtoW");
   
   Output(functionName + _T(" - start"));

   {
      const string input = "This is a string";
   
      const wstring output = CStringConverter::AtoW(input);

      const wstring expected = L"This is a string";

      THROW_ON_FAILURE(functionName, output == expected);
   }

   {
      const size_t stringSize = 2000000;

      const string input(stringSize, 'A');

      const wstring output = CStringConverter::AtoW(input);

      const wstring expected(stringSize, 'A');

      THROW_ON_FAILURE(functionName, output == expected);
   }

   {
      const string input;

      const wstring output = CStringConverter::AtoW(input);

      const wstring expected;

      THROW_ON_FAILURE(functionName, output == expected);
   }



   Output(functionName + _T(" - stop"));
}

} // End of namespace Test
} // End of namespace Win32
} // End of namespace AmstelTech