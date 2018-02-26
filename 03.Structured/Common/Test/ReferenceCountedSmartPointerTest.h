#pragma once

namespace AmstelTech 
{
	
namespace Test 
{

///////////////////////////////////////////////////////////////////////////////
// CReferenceCountedSmartPointerTest
///////////////////////////////////////////////////////////////////////////////
class CReferenceCountedSmartPointerTest
{
   public :

      /// Runs all the tests.

      static void TestAll();

      /// Tests the construction of a TReferenceCountedSmartPointer

      static void TestConstruct();

      /// Tests that destruction releases a managed object.

      static void TestDestruct();

      /// Tests assigning a bare pointer to a smart pointer passes
      /// ownership to the TReferenceCountedSmartPointer without
      /// incurring an AddRef() call.

      static void TestAssignPointer();

      /// Tests assigning a TReferenceCountedSmartPointer to another
      /// TReferenceCountedSmartPointer

      static void TestAssignSmartPointer();

      /// Tests assigning a TReferenceCountedSmartPointer to itself.

      static void TestAssignSmartPointerToSelf();

      /// Tests copy constructing a TReferenceCountedSmartPointer

      static void TestCopyConstruct();

      /// Tests that calling TReferenceCountedSmartPointer::Detach()
      /// passes ownership of the managed pointer to the caller.

      static void TestDetach();
      
      /// Tests that calling TReferenceCountedSmartPointer::Get() returns
      /// the managed pointer without affecting the reference count.
      
      static void TestGet();

      /// Tests that the 'arrow' operator allows access to the underlying
      /// pointer's methods.

      static void TestOperatorArrow();
};

} // End of namespace Test
} // End of namespace AmstelTech