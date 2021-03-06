#pragma once

// MSVC only
#pragma warning(disable: 4127)   // conditional expression is constant

#include "../Tools/Exception.h"
#include "../Tools/SEHException.h"

#include <string>

namespace AmstelTech 
{
	
namespace Test 
{

///////////////////////////////////////////////////////////////////////////////
// CTestException
///////////////////////////////////////////////////////////////////////////////
class CTestException : public AmstelTech::Win32::CException
{
   public :

      explicit CTestException(
         const AmstelTech::Win32::_tstring &message);

      CTestException(
         const AmstelTech::Win32::_tstring &where, 
         const AmstelTech::Win32::_tstring &message);
};

#define THROW_ON_FAILURE(w, t) do{if(!(t)){throw CTestException(w, _T("Test Failed:")## _T(#t));}}while(0)

#define THROW_IF_STRINGS_DONT_MATCH(w, s1, s2) do{if(!(s1 == s2)){throw CTestException(w, _T("Test Failed:\n \"") + s1 + _T("\" !=\n \"") + s2 + _T("\")"));}}while(0)

#define THROW_ON_NO_EXCEPTION(w, e) do{try{e();throw CTestException(w, _T("No Exception from: ")## _T(#e) ## _T("()"));}catch(CTestException &){throw;}catch(AmstelTech::Win32::CSEHException &){throw;}catch(...){}}while(0)

#define THROW_ON_NO_EXCEPTION_1(w, e, p) do{try{e(p);throw CTestException(w, _T("No Exception from: ")## _T(#e) ## _T("(") ## _T(#p) ## _T(")"));}catch(CTestException &){throw;}catch(AmstelTech::Win32::CSEHException &){throw;}catch(...){}}while(0)

#define THROW_ON_NO_EXCEPTION_2(w, e, p1, p2) do{try{e(p1, p2);throw CTestException(w, _T("No Exception from: ")## _T(#e) ## _T("(") ## _T(#p1) ## _T(", ") ## _T(#p2) ## _T(")"));}catch(CTestException &){throw;}catch(AmstelTech::Win32::CSEHException &){throw;}catch(...){}}while(0)

#define THROW_ON_NO_EXCEPTION_3(w, e, p1, p2, p3) do{try{e(p1, p2, p3);throw CTestException(w, _T("No Exception from: ")## _T(#e) ## _T("(") ## _T(#p1) ## _T(", ") ## _T(#p2) ## _T(", ") ## _T(#p3) ## _T(")"));}catch(CTestException &){throw;}catch(AmstelTech::Win32::CSEHException &){throw;}catch(...){}}while(0)

#define THROW_ON_NO_SEH_EXCEPTION_3(w, e, p1, p2, p3) do{try{e(p1, p2, p3);throw CTestException(w, _T("No Exception from: ")## _T(#e) ## _T("(") ## _T(#p1) ## _T(", ") ## _T(#p2) ## _T(", ") ## _T(#p3) ## _T(")"));}catch(CTestException &){throw;}catch(AmstelTech::Win32::CSEHException &){}catch(...){throw;}}while(0)

#define THROW_ON_NO_EXCEPTION_4(w, e, p1, p2, p3, p4) do{try{e(p1, p2, p3, p4);throw CTestException(w, _T("No Exception from: ")## _T(#e) ## _T("(") ## _T(#p1) ## _T(", ") ## _T(#p2) ## _T(", ") ## _T(#p3) ## _T(", ") ## _T(#p4) ## _T(")"));}catch(CTestException &){throw;}catch(AmstelTech::Win32::CSEHException &){throw;}catch(...){}}while(0)

#define THROW_ON_NO_EXCEPTION_5(w, e, p1, p2, p3, p4, p5) do{try{e(p1, p2, p3, p4, p5);throw CTestException(w, _T("No Exception from: ")## _T(#e) ## _T("(") ## _T(#p1) ## _T(", ") ## _T(#p2) ## _T(", ") ## _T(#p3) ## _T(", ") ## _T(#p4) ## _T(", ") ## _T(#p5) ## _T(")"));}catch(CTestException &){throw;}catch(AmstelTech::Win32::CSEHException &){throw;}catch(...){}}while(0)

#define THROW_ON_NO_EXCEPTION_6(w, e, p1, p2, p3, p4, p5, p6) do{try{e(p1, p2, p3, p4, p5, p6);throw CTestException(w, _T("No Exception from: ")## _T(#e) ## _T("(") ## _T(#p1) ## _T(", ") ## _T(#p2) ## _T(", ") ## _T(#p3) ## _T(", ") ## _T(#p4) ## _T(", ") ## _T(#p5) ## _T(", ") ## _T(#p6) ## _T(")"));}catch(CTestException &){throw;}catch(AmstelTech::Win32::CSEHException &){throw;}catch(...){}}while(0)

#define THROW_ON_NO_EXCEPTION_7(w, e, p1, p2, p3, p4, p5, p6, p7) do{try{e(p1, p2, p3, p4, p5, p6, p7);throw CTestException(w, _T("No Exception from: ")## _T(#e) ## _T("(") ## _T(#p1) ## _T(", ") ## _T(#p2) ## _T(", ") ## _T(#p3) ## _T(", ") ## _T(#p4) ## _T(", ") ## _T(#p5) ## _T(", ") ## _T(#p6)  ## _T(", ") ## _T(#p7) ## _T(")"));}catch(CTestException &){throw;}catch(AmstelTech::Win32::CSEHException &){throw;}catch(...){}}while(0)

#define THROW_ON_NO_EXCEPTION_8(w, e, p1, p2, p3, p4, p5, p6, p7, p8) do{try{e(p1, p2, p3, p4, p5, p6, p7, p8);throw CTestException(w, _T("No Exception from: ")## _T(#e) ## _T("(") ## _T(#p1) ## _T(", ") ## _T(#p2) ## _T(", ") ## _T(#p3) ## _T(", ") ## _T(#p4) ## _T(", ") ## _T(#p5) ## _T(", ") ## _T(#p6) ## _T(", ") ## _T(#p7) ## _T(", ") ## _T(#p8) ## _T(")"));}catch(CTestException &){throw;}catch(AmstelTech::Win32::CSEHException &){throw;}catch(...){}}while(0)

#define THROW_ON_NO_EXCEPTION_9(w, e, p1, p2, p3, p4, p5, p6, p7, p8, p9) do{try{e(p1, p2, p3, p4, p5, p6, p7, p8, p9);throw CTestException(w, _T("No Exception from: ")## _T(#e) ## _T("(") ## _T(#p1) ## _T(", ") ## _T(#p2) ## _T(", ") ## _T(#p3) ## _T(", ") ## _T(#p4) ## _T(", ") ## _T(#p5) ## _T(", ") ## _T(#p6) ## _T(", ") ## _T(#p7) ## _T(", ") ## _T(#p8) _T(", ") ## _T(#p9) ## _T(")"));}catch(CTestException &){throw;}catch(AmstelTech::Win32::CSEHException &){throw;}catch(...){}}while(0)

#define ERROR_TIMEOUT_STRINGIZE(L) #L
#define ERROR_TIMEOUT_MAKESTRING(M,L) M(L)
#define ERROR_TIMEOUT_MACROASSTRING(x) ERROR_TIMEOUT_MAKESTRING( ERROR_TIMEOUT_STRINGIZE, x) 

#ifndef REASONABLE_TIME 
#define REASONABLE_TIME 60000    
#endif

#define THROW_IF_NOT_SIGNALLED_IN_TIME(w, e, t) do{if (false == e.Wait(static_cast<AmstelTech::Milliseconds>(t))) { throw CTestException(w, _T("Timeout waiting for ")## _T(#e) ## _T(" after ") ## _T(ERROR_TIMEOUT_MACROASSTRING(t)) ## _T("ms")); } }while(0)

#define THROW_IF_NOT_SIGNALLED_IN_REASONABLE_TIME(w, e) THROW_IF_NOT_SIGNALLED_IN_TIME(w, e, REASONABLE_TIME)

#define THROW_IF_SIGNALLED_WITHIN_GIVEN_TIME(w, e, t) do{if (true == e.Wait(static_cast<AmstelTech::Milliseconds>(t))) { throw CTestException(w, _T(#e) ## _T(" was signalled after ") ## _T(ERROR_TIMEOUT_MACROASSTRING(t)) ## _T("ms and it should never be signalled")); } }while(0)

#ifndef SHORT_TIME_NON_ZERO
#define SHORT_TIME_NON_ZERO   2000
#endif

#define THROW_IF_SIGNALLED(w, e) THROW_IF_SIGNALLED_WITHIN_GIVEN_TIME(w, e, SHORT_TIME_NON_ZERO)

#define THROW_ON_FAILURE_EX(t) do{if(!(t)){throw CTestException(_T("Test Failed:")## _T(#t));}}while(0)

#define THROW_IF_STRINGS_DONT_MATCH_EX(s1, s2) do{if(!(s1 == s2)){throw CTestException(_T("Test Failed:\n \"") + s1 + _T("\" !=\n \"") + s2 + _T("\")"));}}while(0)

#define THROW_ON_NO_EXCEPTION_EX(e) do{try{e();throw CTestException(_T("No Exception from: ")## _T(#e) ## _T("()"));}catch(CTestException &){throw;}catch(AmstelTech::Win32::CSEHException &){throw;}catch(...){}}while(0)

#define THROW_ON_NO_EXCEPTION_EX_1(e, p) do{try{e(p);throw CTestException(_T("No Exception from: ")## _T(#e) ## _T("(") ## _T(#p) ## _T(")"));}catch(CTestException &){throw;}catch(AmstelTech::Win32::CSEHException &){throw;}catch(...){}}while(0)

#define THROW_ON_NO_EXCEPTION_EX_2(e, p1, p2) do{try{e(p1, p2);throw CTestException(_T("No Exception from: ")## _T(#e) ## _T("(") ## _T(#p1) ## _T(", ") ## _T(#p2) ## _T(")"));}catch(CTestException &){throw;}catch(AmstelTech::Win32::CSEHException &){throw;}catch(...){}}while(0)

#define THROW_ON_NO_EXCEPTION_EX_3(e, p1, p2, p3) do{try{e(p1, p2, p3);throw CTestException(_T("No Exception from: ")## _T(#e) ## _T("(") ## _T(#p1) ## _T(", ") ## _T(#p2) ## _T(", ") ## _T(#p3) ## _T(")"));}catch(CTestException &){throw;}catch(AmstelTech::Win32::CSEHException &){throw;}catch(...){}}while(0)

#define THROW_ON_NO_SEH_EXCEPTION_EX_3(e, p1, p2, p3) do{try{e(p1, p2, p3);throw CTestException(_T("No Exception from: ")## _T(#e) ## _T("(") ## _T(#p1) ## _T(", ") ## _T(#p2) ## _T(", ") ## _T(#p3) ## _T(")"));}catch(CTestException &){throw;}catch(AmstelTech::Win32::CSEHException &){}catch(...){throw;}}while(0)

#define THROW_ON_NO_EXCEPTION_EX_4(e, p1, p2, p3, p4) do{try{e(p1, p2, p3, p4);throw CTestException(_T("No Exception from: ")## _T(#e) ## _T("(") ## _T(#p1) ## _T(", ") ## _T(#p2) ## _T(", ") ## _T(#p3) ## _T(", ") ## _T(#p4) ## _T(")"));}catch(CTestException &){throw;}catch(AmstelTech::Win32::CSEHException &){throw;}catch(...){}}while(0)

#define THROW_ON_NO_EXCEPTION_EX_5(e, p1, p2, p3, p4, p5) do{try{e(p1, p2, p3, p4, p5);throw CTestException(_T("No Exception from: ")## _T(#e) ## _T("(") ## _T(#p1) ## _T(", ") ## _T(#p2) ## _T(", ") ## _T(#p3) ## _T(", ") ## _T(#p4) ## _T(", ") ## _T(#p5) ## _T(")"));}catch(CTestException &){throw;}catch(AmstelTech::Win32::CSEHException &){throw;}catch(...){}}while(0)

#define THROW_ON_NO_EXCEPTION_EX_6(e, p1, p2, p3, p4, p5, p6) do{try{e(p1, p2, p3, p4, p5, p6);throw CTestException(_T("No Exception from: ")## _T(#e) ## _T("(") ## _T(#p1) ## _T(", ") ## _T(#p2) ## _T(", ") ## _T(#p3) ## _T(", ") ## _T(#p4) ## _T(", ") ## _T(#p5) ## _T(", ") ## _T(#p6) ## _T(")"));}catch(CTestException &){throw;}catch(AmstelTech::Win32::CSEHException &){throw;}catch(...){}}while(0)

#define THROW_ON_NO_EXCEPTION_EX_7(e, p1, p2, p3, p4, p5, p6, p7) do{try{e(p1, p2, p3, p4, p5, p6, p7);throw CTestException(_T("No Exception from: ")## _T(#e) ## _T("(") ## _T(#p1) ## _T(", ") ## _T(#p2) ## _T(", ") ## _T(#p3) ## _T(", ") ## _T(#p4) ## _T(", ") ## _T(#p5) ## _T(", ") ## _T(#p6)  ## _T(", ") ## _T(#p7) ## _T(")"));}catch(CTestException &){throw;}catch(AmstelTech::Win32::CSEHException &){throw;}catch(...){}}while(0)

#define THROW_ON_NO_EXCEPTION_EX_8(e, p1, p2, p3, p4, p5, p6, p7, p8) do{try{e(p1, p2, p3, p4, p5, p6, p7, p8);throw CTestException(_T("No Exception from: ")## _T(#e) ## _T("(") ## _T(#p1) ## _T(", ") ## _T(#p2) ## _T(", ") ## _T(#p3) ## _T(", ") ## _T(#p4) ## _T(", ") ## _T(#p5) ## _T(", ") ## _T(#p6) ## _T(", ") ## _T(#p7) ## _T(", ") ## _T(#p8) ## _T(")"));}catch(CTestException &){throw;}catch(AmstelTech::Win32::CSEHException &){throw;}catch(...){}}while(0)

#define THROW_IF_NOT_SIGNALLED_EX(e) do{if (false == e.Wait(static_cast<AmstelTech::Milliseconds>(0))) { throw CTestException(_T("Expected ")## _T(#e) ## _T(" to be signalled")); } }while(0)

#define THROW_IF_NOT_SIGNALLED_IN_TIME_EX(e, t) do{if (false == e.Wait(static_cast<AmstelTech::Milliseconds>(t))) { throw CTestException(_T("Timeout waiting for ")## _T(#e) ## _T(" after ") ## _T(ERROR_TIMEOUT_MACROASSTRING(t)) ## _T("ms")); } }while(0)

#define THROW_IF_NOT_SIGNALLED_IN_REASONABLE_TIME_EX(e) THROW_IF_NOT_SIGNALLED_IN_TIME_EX(e, REASONABLE_TIME)

#define THROW_IF_SIGNALLED_WITHIN_GIVEN_TIME_EX(e, t) do{if (true == e.Wait(static_cast<AmstelTech::Milliseconds>(t))) { throw CTestException(_T(#e) ## _T(" was signalled after ") ## _T(ERROR_TIMEOUT_MACROASSTRING(t)) ## _T("ms and it should never be signalled")); } }while(0)

#define THROW_IF_SIGNALLED_EX(e) THROW_IF_SIGNALLED_WITHIN_GIVEN_TIME_EX(e, SHORT_TIME_NON_ZERO)


} //-- namespace Test
} //-- namespace AmstelTech 
