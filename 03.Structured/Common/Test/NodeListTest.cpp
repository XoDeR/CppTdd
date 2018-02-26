#include "../../Platform/Platform.h"

#include "NodeListTest.h"

#include "../NodeList.h"

#include "../Mock/MockNodeListNode.h"

#include "../../Tools/Utils.h"
#include "../../Tools/DebugTrace.h"

#include "../../TestTools/TestException.h"

#include <string>

using AmstelTech::Test::CTestException;

using AmstelTech::Win32::Output;
using AmstelTech::Win32::_tstring;

using AmstelTech::Mock::CMockNodeListNode;

using std::string;

namespace AmstelTech 
{
	
namespace Test 
{

///////////////////////////////////////////////////////////////////////////////
// CNodeListTest
///////////////////////////////////////////////////////////////////////////////

void CNodeListTest::TestAll()
{
   TestConstruct();
   TestAddNode();
}

void CNodeListTest::TestConstruct()
{
   const _tstring functionName = _T("CNodeListTest::TestConstruct");
   
   Output(functionName + _T(" - start"));

   CNodeList list;

   THROW_ON_FAILURE(functionName, 0 == list.Count());

   THROW_ON_FAILURE(functionName, true == list.IsEmpty());

   THROW_ON_FAILURE(functionName, 0 == list.Head());

   THROW_ON_FAILURE(functionName, 0 == list.PopNode());


   Output(functionName + _T(" - stop"));
}

void CNodeListTest::TestAddNode()
{
   const _tstring functionName = _T("CNodeListTest::TestAddNode");
   
   Output(functionName + _T(" - start"));

   CNodeList list;

   CMockNodeListNode node;

   list.PushNode(&node);

   THROW_ON_FAILURE(functionName, 1 == list.Count());

   THROW_ON_FAILURE(functionName, false == list.IsEmpty());

   THROW_ON_FAILURE(functionName, &node == list.Head());

   THROW_ON_FAILURE(functionName, true == node.InList());

   THROW_ON_FAILURE(functionName, true == node.InList(list));

   CNodeList list2;

   THROW_ON_FAILURE(functionName, false == node.InList(list2));

   THROW_ON_FAILURE(functionName, 0 == node.Next());

   THROW_ON_FAILURE(functionName, &node == list.PopNode());

   THROW_ON_FAILURE(functionName, 0 == list.Count());

   THROW_ON_FAILURE(functionName, true == list.IsEmpty());

   THROW_ON_FAILURE(functionName, 0 == list.Head());

   THROW_ON_FAILURE(functionName, 0 == list.PopNode());

   Output(functionName + _T(" - stop"));
}

} // End of namespace Test
} // End of namespace AmstelTech