#include "../../Platform/Platform.h"

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
   const Milliseconds tickCount)
   :  m_tickCount(tickCount),
{
}

void CMockTickCountProvider::SetTickCount(
   const Milliseconds tickCount)
{
   ::InterlockedExchange(const_cast<long *>(reinterpret_cast<volatile long*>(&m_tickCount)), tickCount);
}

Milliseconds CMockTickCountProvider::GetTickCount() const
{
   LogMessage(_T("GetTickCount: ") + ToString(m_tickCount));
   
   return m_tickCount;
}

} // End of namespace Mock
} // End of namespace Win32
} // End of namespace AmstelTech 

