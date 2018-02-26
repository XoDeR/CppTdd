#include "../Platform/Platform.h"

#include "CriticalSection.h"
#include "Utils.h"
#include "Win32Exception.h"

namespace AmstelTech 
{
	
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// CCriticalSection
///////////////////////////////////////////////////////////////////////////////

CCriticalSection::CCriticalSection()
{
   ::InitializeCriticalSection(&m_crit);
}

CCriticalSection::CCriticalSection(
   const DWORD spinCount)
{
#if(_WIN32_WINNT >= 0x0403)
   if (!::InitializeCriticalSectionAndSpinCount(&m_crit, spinCount))
   {
      const DWORD lastError = ::GetLastError();

      throw CWin32Exception(_T("CCriticalSection::CCriticalSection()"), lastError);
   }
#else
   spinCount;
   ::InitializeCriticalSection(&m_crit);

   OutputDebugString(_T("CCriticalSection::CCriticalSection() - spin count specified but _WIN32_WINNT < 0x0403, spin count not used\n"));
#endif
}
      
CCriticalSection::~CCriticalSection()
{
   ::DeleteCriticalSection(&m_crit);
}

/*
#if(_WIN32_WINNT >= 0x0400)
bool CCriticalSection::TryEnter()
{
   return ToBool(::TryEnterCriticalSection(&m_crit));
}
#endif
*/

void CCriticalSection::SetSpinCount(
   const DWORD spinCount)
{
#if (_WIN32_WINNT >= 0x0403)
   ::SetCriticalSectionSpinCount(&m_crit, spinCount);
#else
   OutputDebugString(_T("CCriticalSection::SetSpinCount() - _WIN32_WINNT < 0x0403, spin count not used\n"));
#endif
}

void CCriticalSection::Enter()
{
   // can fail if there's contention and the event can't be created and will
   // raise an EXCEPTION_INVALID_HANDLE exception.

   ::EnterCriticalSection(&m_crit);
}

void CCriticalSection::Leave()
{
   ::LeaveCriticalSection(&m_crit);
}

} // End of namespace Win32
} // End of namespace AmstelTech 