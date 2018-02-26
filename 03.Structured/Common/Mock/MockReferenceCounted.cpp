#include "../../Platform/Platform.h"

#include "MockReferenceCounted.h"

#include "../../Tools/Utils.h"

using AmstelTech::Win32::ToString;

namespace AmstelTech 
{
	
namespace Mock 
{

///////////////////////////////////////////////////////////////////////////////
// CMockReferenceCounted
///////////////////////////////////////////////////////////////////////////////

CMockReferenceCounted::CMockReferenceCounted()
   :  m_ref(1)
{
}

void CMockReferenceCounted::AddRef()
{
   m_ref++;

   LogMessage(_T("AddRef: ") + ToString(m_ref));
}

void CMockReferenceCounted::Release()
{
   m_ref--;

   LogMessage(_T("Release: ") + ToString(m_ref));
}

} // End of namespace Mock
} // End of namespace AmstelTech