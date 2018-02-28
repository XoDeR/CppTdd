#include "../Platform/Platform.h"

#include "MockTickCount64Provider.h"

#include "../../Tools/Utils.h"

using AmstelTech::Win32::ToString;

namespace AmstelTech 
{
	
namespace Win32 
{
	
namespace Mock 
{

///////////////////////////////////////////////////////////////////////////////
// CMockTickCount64Provider
///////////////////////////////////////////////////////////////////////////////

CMockTickCount64Provider::CMockTickCount64Provider()
   :  m_tickCount(0)
{
}

CMockTickCount64Provider::CMockTickCount64Provider(
   const ULONGLONG tickCount)
   :  m_tickCount(tickCount)
{
}

void CMockTickCount64Provider::SetTickCount(
   const ULONGLONG tickCount)
{
   ::InterlockedExchange64(const_cast<LONGLONG *>(reinterpret_cast<volatile LONGLONG*>(&m_tickCount)), tickCount);
}

ULONGLONG CMockTickCount64Provider::GetTickCount64() const
{
   LogMessage(_T("GetTickCount: ") + ToString(m_tickCount));
   
   return m_tickCount;
}

} // End of namespace Mock
} // End of namespace Win32
} // End of namespace AmstelTech