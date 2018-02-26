#pragma once

namespace AmstelTech 
{
	
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// IRunnable
///////////////////////////////////////////////////////////////////////////////

/// An interface to code that can be Run() on a thread. Usually passed to the
/// CThread constructor.
class IRunnable
{
   public :

      /// The return value is the exit code of the thread that is run to 
      /// execute the code.
      virtual int Run() throw() = 0;

   protected :

		/// We never delete instances of this interface; you must manage the 
		/// lifetime of the class that implements it.

      ~IRunnable() {}
};

} // End of namespace Win32
} // End of namespace AmstelTech