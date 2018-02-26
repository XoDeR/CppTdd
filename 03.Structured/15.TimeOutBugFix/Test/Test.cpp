#include "../../Platform/Platform.h"

#include "../../Tools/DebugTrace.h"

#include "../../TestTools/TestException.h"

#include "CallbackTimerTest.h"
#include "ThreadedCallbackTimerQueueTest.h"

#include "../../Tools/Utils.h"
#include "../../Tools/Exception.h"
#include "../../Tools/SEHException.h"
#include "../../Tools/StringConverter.h"

using AmstelTech::Win32::OutputEx;
using AmstelTech::Win32::CDebugTrace;
using AmstelTech::Win32::CException;
using AmstelTech::Win32::CStringConverter;
using AmstelTech::Win32::CSEHException;
using AmstelTech::Win32::SetCurrentDirectory;

using AmstelTech::Test::CTestException;

using namespace AmstelTech::Win32::Test;

int main(int /*argc*/, char * /*argv[ ]*/)
{
   int nArgc = __argc;
#ifdef UNICODE
   PWSTR *ppArgv = CommandLineToArgvW(GetCommandLine(), &nArgc);
#else
   PCSTR *ppArgv = (PCSTR*) __argv;
#endif

   ::SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);

   CSEHException::Translator sehTranslator;

   CDebugTrace::Instance().SetLogName("Win32ToolsTest.log");

   bool ok = false;

   try
   {
      if (nArgc == 2)
      {
         SetCurrentDirectory(ppArgv[1]);
      }

      CCallbackTimerQueueTest::TestAll();
      CThreadedCallbackTimerQueueTest::TestAll();

      ok = true;
   }
   catch(const CTestException &e)
   {
      OutputEx("Test Exception: " + CStringConverter::TtoA(e.GetWhere() + _T(" - ") + e.GetMessage()));

      ok = false;
   }
   catch(const CException &e)
   {
      OutputEx("Exception: " + CStringConverter::TtoA(e.GetWhere() + _T(" - ") + e.GetMessage()));

      ok = false;
   }
   catch(const CSEHException &e)
   {
      OutputEx("Exception: " + CStringConverter::TtoA(e.GetWhere() + _T(" - ") + e.GetMessage()));

      ok = false;
   }
   catch(const char *p)
   {
      OutputEx(std::string("Exception: ") + p);
   }
   catch(...)
   {
      OutputEx("Unexpected exception");

      ok = false;
   }

   OutputEx(std::string("Test ") + (ok ? "Passed" : "Failed"));

   return ok ? 0 : 1;
}