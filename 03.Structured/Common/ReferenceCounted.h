#pragma once

namespace AmstelTech 
{

///////////////////////////////////////////////////////////////////////////////
// TReferenceCounted
///////////////////////////////////////////////////////////////////////////////

/// A template class that wraps a class to provide it with and manage an 
/// external reference count.

template <class T, class B> class TReferenceCounted
{
   public :

      // Construction and destruction

      TReferenceCounted(T counted);

      // Access functions 

      const T &GetCounted() const;

      T &GetCounted();

      operator T &() const;

      operator T *() const;

      // Manage the reference count

      B *AddRef();

      B *Release() throw();

      // Copy a pointer to a TReferenceCounted...

      static B *Copy(
         B *pRefCounted);

   protected :

      virtual void PreRelease() = 0;

      T m_counted;
      
      // We can't be deleted except by ourself...

      virtual ~TReferenceCounted();

   private :

      long m_count;

      // Restrict copying, don't implement

      TReferenceCounted(const TReferenceCounted &rhs);
      TReferenceCounted &operator=(const TReferenceCounted &rhs);
};

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction
///////////////////////////////////////////////////////////////////////////////

template <class T, class B>
TReferenceCounted<T,B>::TReferenceCounted(T counted) 
   : m_counted(counted), m_count(1) 
{ 

}

template <class T, class B>
TReferenceCounted<T,B>::~TReferenceCounted() 
{ 
   
}

///////////////////////////////////////////////////////////////////////////////
// Access the underlying object
///////////////////////////////////////////////////////////////////////////////

template <class T, class B>
const T &TReferenceCounted<T,B>::GetCounted() const
{
   return m_counted;
}

template <class T, class B>
T &TReferenceCounted<T,B>::GetCounted()
{
   return m_counted;
}

template <class T, class B>
TReferenceCounted<T,B>::operator T &() const
{
   return m_counted;
}

template <class T, class B>
TReferenceCounted<T,B>::operator T *() const
{
   return &m_counted;
}

///////////////////////////////////////////////////////////////////////////////
// Manage the reference count
///////////////////////////////////////////////////////////////////////////////

template <class T, class B>
B *TReferenceCounted<T,B>::AddRef()
{
   ::InterlockedIncrement(&m_count);

   return (B*)this;
}

template <class T, class B>
B *TReferenceCounted<T,B>::Release() throw()
{
   if (0 == ::InterlockedDecrement(&m_count))
   {
      try
      {
         PreRelease();
      }
      catch (...)
      {
         // Release() mustn't throw...
      }

      delete this;
   }

   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Copy a reference counted pointer
///////////////////////////////////////////////////////////////////////////////

template <class T, class B>
B *TReferenceCounted<T,B>::Copy(
   B *pRefCounted)
{
   return (pRefCounted ? pRefCounted->AddRef() : 0);
}

} // End of namespace AmstelTech