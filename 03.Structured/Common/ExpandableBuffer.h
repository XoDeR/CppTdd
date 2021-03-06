#pragma once

namespace AmstelTech 
{

///////////////////////////////////////////////////////////////////////////////
// TExpandableBuffer
///////////////////////////////////////////////////////////////////////////////

/// A template class for an expandable buffer, that is a buffer that can be 
/// expanded and which will, if expanded, maintain its contents.

template <class T> class TExpandableBuffer
{
   public :

      /// Create a buffer of the specified initialSize. If the size is 0 then
      /// the buffer must be resized or expanded before use.
      explicit TExpandableBuffer(
         size_t intialSize = 0);

      TExpandableBuffer(
         const TExpandableBuffer &rhs);

      ~TExpandableBuffer();

      TExpandableBuffer &operator=(
         const TExpandableBuffer &rhs);

      /// Access the buffer.

      T *GetBuffer() const; 
      
      /// Access the buffer.

      operator T *() const; 

      /// Obtain the size of the buffer

      size_t GetSize() const;

      /// Make the buffer bigger, but do not copy the previous contents to
      /// the new buffer. Return the new size.

      size_t Resize(
         const size_t newSize);    

      /// Make the buffer bigger and copy the previous contents to the new 
      /// buffer. Return the new size.

      size_t Expand(
         const size_t newSize);    

      /// Remove the actual memory used to store the date from the buffer. The
      /// buffer is left with a buffer of size 0. The caller is responsible for
      /// destroying the memory returned, using delete [], once they've finished 
      /// with it

      T *ReleaseBuffer();

   private :

      T *m_pBuffer;

      size_t m_size;
};

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction
///////////////////////////////////////////////////////////////////////////////

template <class T> 
TExpandableBuffer<T>::TExpandableBuffer(
   const size_t initialSize) 
   :  m_pBuffer(0), 
      m_size(0) 
{ 
   Resize(initialSize); 
}

template <class T> 
TExpandableBuffer<T>::TExpandableBuffer(
   const TExpandableBuffer<T> &rhs) 
   :  m_pBuffer(0), 
      m_size(0) 
{ 
   Resize(rhs.m_size); 

   for (DWORD i = 0; i < m_size; i++)
   {
      m_pBuffer[i] = rhs.m_pBuffer[i];
   }
}

template <class T>
TExpandableBuffer<T>::~TExpandableBuffer() 
{ 
   delete[] m_pBuffer; 
}

template <class T>
TExpandableBuffer<T> &TExpandableBuffer<T>::operator=(
   const TExpandableBuffer<T> &rhs)
{
   if (this != &rhs)
   {
      Resize(rhs.m_size);

      for (size_t i = 0; i < m_size; i++)
      {
         m_pBuffer[i] = rhs.m_pBuffer[i];
      }
   }

   return *this;
}

///////////////////////////////////////////////////////////////////////////////
// Access functions
///////////////////////////////////////////////////////////////////////////////

template <class T> 
T *TExpandableBuffer<T>::GetBuffer() const 
{ 
   return m_pBuffer; 
}

template <class T> 
TExpandableBuffer<T>::operator T *() const 
{ 
   return GetBuffer(); 
}

template <class T> 
size_t TExpandableBuffer<T>::GetSize() const 
{ 
   return m_size; 
}

template <class T> 
T *TExpandableBuffer<T>::ReleaseBuffer()
{ 
   T *pBuffer = m_pBuffer;

   m_pBuffer = 0;
   m_size = 0;

   return pBuffer; 
}

///////////////////////////////////////////////////////////////////////////////
// Make the buffer bigger
///////////////////////////////////////////////////////////////////////////////

template <class T> 
size_t TExpandableBuffer<T>::Resize(
   const size_t newSize)
{
   if (m_size < newSize)
   {
      T *pNewBuffer = new T[newSize];
      
      delete[] m_pBuffer;

      m_pBuffer = pNewBuffer;

      m_size = newSize;
   }
   
   return m_size;
}

template <class T> 
size_t TExpandableBuffer<T>::Expand(
   const size_t newSize)
{
   if (m_size < newSize)
   {
      T *pNewBuffer = new T[newSize];

      if (m_pBuffer)
      {
         for (size_t i = 0; i < m_size; i++)
         {
            pNewBuffer[i] = m_pBuffer[i];
         }

         delete[] m_pBuffer;
      }

      m_pBuffer = pNewBuffer;

      m_size = newSize;
   }
   
   return m_size;
}

} // End of namespace AmstelTech