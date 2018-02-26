#pragma once

namespace AmstelTech 
{

///////////////////////////////////////////////////////////////////////////////
// TSingleton
///////////////////////////////////////////////////////////////////////////////

template <class T> class TSingleton
{
   public :

      // Construction and destruction

      virtual ~TSingleton();

      // Access to the one instance of the object

      static T &TheObject(); 

   protected :

      // We can only be created in our access function...

      TSingleton();
};

///////////////////////////////////////////////////////////////////////////////
// Construction and destriction
///////////////////////////////////////////////////////////////////////////////

template <class T> TSingleton<T>::TSingleton()
{
   // We can only be created in our access function...
}


template <class T> TSingleton<T>::~TSingleton()
{
   // Nothing to do, we just need to be virtual
}

///////////////////////////////////////////////////////////////////////////////
// Access to the one instance of the object
///////////////////////////////////////////////////////////////////////////////

template <class T> T &TSingleton<T>::TheObject()
{
   static T theObject;

   return theObject;
}

} // End of namespace AmstelTech 
