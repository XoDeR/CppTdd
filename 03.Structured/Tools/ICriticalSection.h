#pragma once

namespace AmstelTech 
{
	
namespace Win32 
{

///////////////////////////////////////////////////////////////////////////////
// ICriticalSection
///////////////////////////////////////////////////////////////////////////////

/// An interface onto the operating system 
/// Critical Section API. Note that this class only provides the basic Enter() and 
/// Leave() functionality, should TryEnter() ever be required then it's likely 
/// that a new interface will be added that includes this rather than extending 
/// this interface to include it.
class ICriticalSection 
{
   public :
   
      /// A class that takes ownership of an instance of ICriticalSection. That
      /// is it calls Enter() in the constructor and Leave() in the destructor 
      /// and can therefore be used to support RAII "scope based" locking 
      /// and unlocking of instances of ICriticalSection.

      class Owner
      {
         public:

            explicit Owner(
               ICriticalSection &crit);

            ~Owner();
      
         private :

            ICriticalSection &m_crit;

            /// No copies do not implement
            Owner(const Owner &rhs);
            /// No copies do not implement
            Owner &operator=(const Owner &rhs);
      };

      /// A class that may take ownership of an instance of ICriticalSection. 
      /// That is it calls Enter() in the constructor and Leave() in the 
      /// destructor (but only if locked passed as true to the constructor) 
      /// and can therefore be used to support RAII "scope based" locking
      /// and unlocking of instances of ICriticalSection.
      class ConditionalOwner
      {
         public:

            explicit ConditionalOwner(
               ICriticalSection &crit,
               bool locked = true);

            ~ConditionalOwner();

            void Leave();
      
         private :

            ICriticalSection &m_crit;

            bool m_locked;

            /// No copies do not implement
            ConditionalOwner(const ConditionalOwner &rhs);
            /// No copies do not implement
            ConditionalOwner &operator=(const ConditionalOwner &rhs);
      };

      /// Enter the critical section and lock other threads outside.

      virtual void Enter() = 0;

      /// Leave the critical section and allow another thread to enter.

      virtual void Leave() = 0;

      /// Instances of this interface can be deleted by their users.

      virtual ~ICriticalSection() {}
};

} // End of namespace Win32
} // End of namespace AmstelTech