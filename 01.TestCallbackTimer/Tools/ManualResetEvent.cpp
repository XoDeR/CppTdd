#include "ManualResetEvent.h"

namespace AmstelTech 
{
	
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// CManualResetEvent
///////////////////////////////////////////////////////////////////////////////

CManualResetEvent::CManualResetEvent(
   bool initialState /* = false */)
   :  CEvent(0, true, initialState)
{

}

CManualResetEvent::CManualResetEvent(
   const _tstring &name, 
   bool initialState /* = false */)
   :  CEvent(0, true, initialState, name)
{
   
}
    
} // End of namespace Win32
} // End of namespace AmstelTech 