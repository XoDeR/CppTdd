#pragma once

namespace AmstelTech 
{

///////////////////////////////////////////////////////////////////////////////
// CTypeSafeTypedef
///////////////////////////////////////////////////////////////////////////////

template <typename baseType, typename uniqueBase>
class TTypeSafeTypedef : public uniqueBase
{
   public :

      TTypeSafeTypedef()
      {
      }

      explicit TTypeSafeTypedef(
         const baseType &rhs)
         : m_value(rhs)
      {
      }

      TTypeSafeTypedef(
         const TTypeSafeTypedef &rhs)
         :  m_value(rhs.m_value)
      {
      }

      TTypeSafeTypedef &operator=(
         const baseType &rhs)
      {
         m_value = rhs;

         return *this;
      }

      TTypeSafeTypedef &operator=(
         const TTypeSafeTypedef<baseType, uniqueBase> &rhs)
      {
         m_value = rhs.m_value;

         return *this;
      }

      operator baseType() const
      {
         return m_value;
      }

      baseType GetValue() const
      {
         return m_value;
      }

   private :

      baseType m_value;

};

///////////////////////////////////////////////////////////////////////////////
// Macros
///////////////////////////////////////////////////////////////////////////////

#define TYPESAFE_TYPEDEF(type, name)   \
   class name##TTypeSafeTypedef__ {};  \
   typedef AmstelTech::TTypeSafeTypedef<type, name##TTypeSafeTypedef__> name; 

} // End of namespace AmstelTech 
