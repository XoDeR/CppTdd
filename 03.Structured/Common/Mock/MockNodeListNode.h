#pragma once

#include "../NodeList.h"

namespace AmstelTech 
{
	
namespace Mock 
{

///////////////////////////////////////////////////////////////////////////////
// CMockNodeListNode
///////////////////////////////////////////////////////////////////////////////

/// A mock object that derives from CNodeList::Node and so can be stored in
/// a CNodeList or a TNodeList<CMockNodeListNode>.

class CMockNodeListNode : public CNodeList::Node
{
   public :

      CMockNodeListNode()
      {

      }
};
  
} // End of namespace Mock
} // End of namespace AmstelTech