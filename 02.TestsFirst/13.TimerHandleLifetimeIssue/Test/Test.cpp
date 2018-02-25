#include <iostream>

#include "../../TestTools/TestException.h"

#include "CallbackTimerTest.h"
#include "ThreadedCallbackTimerQueueTest.h"
#include "StringConverterTest.h"

#include "../../Tools/Exception.h"
#include "../../Tools/SEHException.h"
#include "../../Tools/StringConverter.h"

using std::cout;
using std::endl;
using std::string;

using AmstelTech::Win32::CException;
using AmstelTech::Win32::CStringConverter;
using AmstelTech::Win32::CSEHException;

using AmstelTech::Test::CTestException;

using namespace AmstelTech::Win32::Test;

int main()
{
   CSEHException::Translator sehTranslator;

   bool ok = false;

   try
   {
      CCallbackTimerTest::TestAll();
	  CThreadedCallbackTimerQueueTest::TestAll();
	  CStringConverterTest::TestAll();
      
      ok = true;
   }
   catch(const CTestException &e)
   {
      cout << "Test Exception: " << CStringConverter::TtoA(e.GetWhere() + _T(" - ") + e.GetMessage()) << endl;

      ok = false;
   }
   catch(const CException &e)
   {
      cout << "Exception: " << CStringConverter::TtoA(e.GetWhere() + _T(" - ") + e.GetMessage()) << endl;

      ok = false;
   }
   catch(const CSEHException &e)
   {
      cout << "Exception: " << CStringConverter::TtoA(e.GetWhere() + _T(" - ") + e.GetMessage()) << endl;

      ok = false;
   }
   catch(const char *p)
   {
      cout << "Exception: " << p << endl;
   }
   catch(...)
   {
      cout << "Unexpected exception" << endl;

      ok = false;
   }

   cout << "Test " << (ok ? "Passed" : "Failed") << endl;

   return ok ? 0 : 1;
}