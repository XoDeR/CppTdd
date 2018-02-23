#pragma once

#pragma warning(disable : 4786)

#include "../Tools/Exception.h"

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
      CTestException(
         const AmstelTech::Win32::_tstring& where, 
         const AmstelTech::Win32::_tstring& message);
};

#define THROW_ON_FAILURE(w, t) do{if(!(t)){throw CTestException(w, _T("Test Failed:")## _T(#t));}}while(0)

#define THROW_ON_NO_EXCEPTION(w, e) do{try{e();throw CTestException(w, _T("No Exception from: ")## _T(#e) ## _T("()"));}catch(CTestException &){throw;}catch(...){}}while(0)

#define THROW_ON_NO_EXCEPTION_1(w, e, p) do{try{e(p);throw CTestException(w, _T("No Exception from: ")## _T(#e) ## _T("(") ## _T(#p) ## _T(")"));}catch(CTestException &){throw;}catch(...){}}while(0)

#define THROW_ON_NO_EXCEPTION_2(w, e, p1, p2) do{try{e(p1, p2);throw CTestException(w, _T("No Exception from: ")## _T(#e) ## _T("(") ## _T(#p1) ## _T(", ") ## _T(#p2) ## _T(")"));}catch(CTestException &){throw;}catch(...){}}while(0)

#define THROW_ON_NO_EXCEPTION_3(w, e, p1, p2, p3) do{try{e(p1, p2, p3);throw CTestException(w, _T("No Exception from: ")## _T(#e) ## _T("(") ## _T(#p1) ## _T(", ") ## _T(#p2) ## _T(", ") ## _T(#p3) ## _T(")"));}catch(CTestException &){throw;}catch(...){}}while(0)

#define THROW_ON_NO_EXCEPTION_4(w, e, p1, p2, p3, p4) do{try{e(p1, p2, p3, p4);throw CTestException(w, _T("No Exception from: ")## _T(#e) ## _T("(") ## _T(#p1) ## _T(", ") ## _T(#p2) ## _T(", ") ## _T(#p3) ## _T(", ") ## _T(#p4) ## _T(")"));}catch(CTestException &){throw;}catch(...){}}while(0)

} //-- namespace Test
} //-- namespace AmstelTech 
