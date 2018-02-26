#include "../Platform/Platform.h"

#include "ICriticalSection.h"

namespace AmstelTech 
{
	
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// ICriticalSection::Owner
///////////////////////////////////////////////////////////////////////////////

ICriticalSection::Owner::Owner(
   ICriticalSection &crit)
   : m_crit(crit)
{
   m_crit.Enter();
}

ICriticalSection::Owner::~Owner()
{
   m_crit.Leave();
}
     
///////////////////////////////////////////////////////////////////////////////
// ICriticalSection::ConditionalOwner
///////////////////////////////////////////////////////////////////////////////

ICriticalSection::ConditionalOwner::ConditionalOwner(
   ICriticalSection &crit,
   bool locked)
   :  m_crit(crit),
      m_locked(locked)
{
   if (m_locked)
   {
      m_crit.Enter();
   }
}

ICriticalSection::ConditionalOwner::~ConditionalOwner()
{
   if (m_locked)
   {
      m_crit.Leave();
   }
}

void ICriticalSection::ConditionalOwner::Leave()
{
   if (m_locked)
   {
      m_locked = false;

      m_crit.Leave();
   }
}
 
} // End of namespace Win32
} // End of namespace AmstelTech