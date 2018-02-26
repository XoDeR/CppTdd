#pragma once

namespace AmstelTech 
{
	
namespace Test 
{

///////////////////////////////////////////////////////////////////////////////
// CNodeListTest
///////////////////////////////////////////////////////////////////////////////
class CNodeListTest
{
   public :

      /// Runs all the tests.
      
      static void TestAll();

      /// Tests the construction of a CNodeList
      
      static void TestConstruct();

      /// Tests CNodeList::AddNode()

      static void TestAddNode();
};

} // End of namespace Test
} // End of namespace AmstelTech