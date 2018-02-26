#pragma once

namespace AmstelTech 
{
	
namespace Test 
{

///////////////////////////////////////////////////////////////////////////////
// CExpandableBufferTest
///////////////////////////////////////////////////////////////////////////////
class CExpandableBufferTest
{
   public :

      /// Runs all the tests.

      static void TestAll();

      /// Tests the construction of a TExpandableBuffer of various types.
      
      static void TestConstruct();

      /// Tests assignment.
      
      static void TestAssign();

      /// Tests copy construction.

      static void TestCopyConstruct();

      /// Tests that TExpandableBuffer::Expand() is non destructive.
      
      static void TestExpand();

      /// Tests that TExpandableBuffer::Resize() is destructive.

      static void TestResize();

      /// Tests that TExpandableBuffer::ReleaseBuffer() passes ownership to
      /// the caller.

      static void TestRelease();
};

} // End of namespace Test
} // End of namespace AmstelTech