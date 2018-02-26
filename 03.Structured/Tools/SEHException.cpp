#include "../Platform/Platform.h"

#include "SEHException.h"

#include "Utils.h"

namespace AmstelTech 
{
	
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// Static helper functions
///////////////////////////////////////////////////////////////////////////////

static _tstring Where(
   EXCEPTION_POINTERS *pPointers);

static _tstring Message(
   unsigned int code);

///////////////////////////////////////////////////////////////////////////////
// CSEHException
///////////////////////////////////////////////////////////////////////////////

CSEHException::CSEHException(
   unsigned int code, 
   EXCEPTION_POINTERS *pPointers)
   :  m_where(Where(pPointers)), 
      m_message(Message(code)),
      m_code(code),
      m_pPointers(pPointers)
{
}

unsigned int CSEHException::GetCode() const
{
   return m_code;
}

const EXCEPTION_POINTERS &CSEHException::GetExceptionPointers() const
{
   return *m_pPointers;
}

const CONTEXT &CSEHException::GetContext() const
{
   return *m_pPointers->ContextRecord;
}

_tstring CSEHException::GetWhere() const
{
   return m_where;
}

_tstring CSEHException::GetMessage() const
{
   return m_message;
}

CSEHException::Translator::Translator()
   :  m_prev(_set_se_translator(Translator::trans_func))
{

}

CSEHException::Translator::~Translator()
{
   _set_se_translator(m_prev);
}

void CSEHException::Translator::trans_func(
   unsigned int code, 
   EXCEPTION_POINTERS *pPointers)
{
   throw CSEHException(code, pPointers);
}

///////////////////////////////////////////////////////////////////////////////
// Helpful define
///////////////////////////////////////////////////////////////////////////////

#define CASE_MSG(c) case EXCEPTION_##c: \
{ static const _tstring msg = _T(#c); \
return msg; } \
break;

///////////////////////////////////////////////////////////////////////////////
// Static helper functions
///////////////////////////////////////////////////////////////////////////////

static _tstring Where(
   EXCEPTION_POINTERS *pPointers)
{
   TCHAR buffer[11];

   _stprintf_s(buffer, _T("0x%.8x"), pPointers->ExceptionRecord->ExceptionAddress);
   
   return buffer;
}

static _tstring Message(
   unsigned int code)
{
	switch (code)    
   {   
		CASE_MSG(ACCESS_VIOLATION);
		CASE_MSG(DATATYPE_MISALIGNMENT);
		CASE_MSG(BREAKPOINT);
		CASE_MSG(SINGLE_STEP);
		CASE_MSG(ARRAY_BOUNDS_EXCEEDED);
		CASE_MSG(FLT_DENORMAL_OPERAND);
		CASE_MSG(FLT_DIVIDE_BY_ZERO);
		CASE_MSG(FLT_INEXACT_RESULT);
		CASE_MSG(FLT_INVALID_OPERATION);
		CASE_MSG(FLT_OVERFLOW);
		CASE_MSG(FLT_STACK_CHECK);
		CASE_MSG(FLT_UNDERFLOW);
		CASE_MSG(INT_DIVIDE_BY_ZERO);
		CASE_MSG(INT_OVERFLOW);
		CASE_MSG(PRIV_INSTRUCTION);
		CASE_MSG(IN_PAGE_ERROR);
		CASE_MSG(ILLEGAL_INSTRUCTION);
		CASE_MSG(NONCONTINUABLE_EXCEPTION);
		CASE_MSG(STACK_OVERFLOW);
		CASE_MSG(INVALID_DISPOSITION);
		CASE_MSG(GUARD_PAGE);
		CASE_MSG(INVALID_HANDLE);
   }

   return _T("Unknown exception");
}

} // End of namespace Win32
} // End of namespace AmstelTech 