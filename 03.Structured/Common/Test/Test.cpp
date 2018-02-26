#include "../../Platform/Platform.h"

#include <iostream>

#include "../../TestTools/TestException.h"

#include "ExpandableBufferTest.h"
#include "NodeListTest.h"
#include "ReferenceCountedSmartPointerTest.h"

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

using namespace AmstelTech::Test;

int main(int /*argc*/, char * /*argv[ ]*/)
{
   int nArgc = __argc;
#ifdef UNICODE
   PWSTR *ppArgv = CommandLineToArgvW(GetCommandLine(), &nArgc);
#else
   PCSTR *ppArgv = (PCSTR*) __argv;
#endif

   if (nArgc == 2)
   {
      SetCurrentDirectory(ppArgv[1]);
   }

   CSEHException::Translator sehTranslator;

   bool ok = false;

   try
   {
      CReferenceCountedSmartPointerTest::TestAll();
      CExpandableBufferTest::TestAll();
      CNodeListTest::TestAll();

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