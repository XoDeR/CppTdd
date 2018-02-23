#include "AutoResetEvent.h"

namespace AmstelTech 
{
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// CAutoResetEvent
///////////////////////////////////////////////////////////////////////////////

CAutoResetEvent::CAutoResetEvent(
   bool initialState /* = false */)
   :  CEvent(0, false, initialState)
{

}

CAutoResetEvent::CAutoResetEvent(
   const _tstring &name, 
   bool initialState /* = false */)
   :  CEvent(0, false, initialState, name)
{
   
}
 
} // End of namespace Win32
} // End of namespace AmstelTech 