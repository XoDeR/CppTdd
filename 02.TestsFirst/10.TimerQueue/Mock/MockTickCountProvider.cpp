#include "MockTickCountProvider.h"

#include "../../Tools/Utils.h"

using AmstelTech::Win32::ToString;

namespace AmstelTech 
{
	
namespace Win32 
{
	
namespace Mock 
{

///////////////////////////////////////////////////////////////////////////////
// CMockTickCountProvider
///////////////////////////////////////////////////////////////////////////////

CMockTickCountProvider::CMockTickCountProvider()
   : m_tickCount(0)
{
}

CMockTickCountProvider::CMockTickCountProvider(
   const DWORD tickCount)
   :  m_tickCount(tickCount),
{
}

void CMockTickCountProvider::SetTickCount(
   const DWORD tickCount)
{
   ::InterlockedExchange(reinterpret_cast<volatile long *>(&m_tickCount), tickCount);
}

DWORD CMockTickCountProvider::GetTickCount() const
{
   LogMessage(_T("GetTickCount: ") + ToString(m_tickCount));
   
   return m_tickCount;
}

} // End of namespace Mock
} // End of namespace Win32
} // End of namespace AmstelTech 

