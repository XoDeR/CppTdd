#include "CriticalSection.h"
#include "Utils.h"

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
   const size_t spinCount)
{
#if(_WIN32_WINNT >= 0x0403)
   ::InitializeCriticalSectionAndSpinCount(&m_crit, spinCount);
#else
   spinCount;
   ::InitializeCriticalSection(&m_crit);
   
   OutputEx(_T("CCriticalSection::CCriticalSection() - spin count specified but _WIN32_WINNT < 0x0403, spin count not used"));
#endif
}
      
CCriticalSection::~CCriticalSection()
{
   ::DeleteCriticalSection(&m_crit);
}

#if(_WIN32_WINNT >= 0x0400)
bool CCriticalSection::TryEnter()
{
   return ToBool(::TryEnterCriticalSection(&m_crit));
}
#endif

void CCriticalSection::Enter()
{
   ::EnterCriticalSection(&m_crit);
}

void CCriticalSection::Leave()
{
   ::LeaveCriticalSection(&m_crit);
}

///////////////////////////////////////////////////////////////////////////////
// CCriticalSection::Owner
///////////////////////////////////////////////////////////////////////////////

CCriticalSection::Owner::Owner(
   CCriticalSection &crit)
   : m_crit(crit)
{
   m_crit.Enter();
}

CCriticalSection::Owner::~Owner()
{
   m_crit.Leave();
}
     
///////////////////////////////////////////////////////////////////////////////
// CCriticalSection::ConditionalOwner
///////////////////////////////////////////////////////////////////////////////

CCriticalSection::ConditionalOwner::ConditionalOwner(
   CCriticalSection &crit,
   bool lock)
   :  m_crit(crit),
      m_lock(lock)
{
   if (m_lock)
   {
      m_crit.Enter();
   }
}

CCriticalSection::ConditionalOwner::~ConditionalOwner()
{
   if (m_lock)
   {
      m_crit.Leave();
   }
}
 
} // End of namespace Win32
} // End of namespace AmstelTech 