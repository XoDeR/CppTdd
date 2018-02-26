#include "../../Platform/Platform.h"

#include "DebugTrace.h"

namespace AmstelTech 
{

///////////////////////////////////////////////////////////////////////////////
// CDebugTrace
///////////////////////////////////////////////////////////////////////////////

CDebugTrace::CDebugTrace()
{
}

CDebugTrace &CDebugTrace::Instance()
{
   static CDebugTrace theInstance;

   return theInstance;
}

} // End of namespace AmstelTech 
