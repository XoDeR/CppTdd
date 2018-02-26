#pragma once

#include <string>

namespace AmstelTech 
{

///////////////////////////////////////////////////////////////////////////////
// ILogMessages
///////////////////////////////////////////////////////////////////////////////

class ILogMessages
{
   public :

      /// Sets the identifier used in the log for the current thread to the 
      /// supplied string. The thread identifier defaults to the thread id
      /// in the form "XXX: ", the string supplied as an identifier does not
      /// need to include the ": " as this will be appended automatically. 
      /// It can be any string that will help you to identify the thread
      /// concerned.

      virtual void SetThreadIdentifier(
         const std::string &identifier) = 0;

      /// Sets the identifier used in the log for the current thread to the 
      /// supplied string. The thread identifier defaults to the thread id
      /// in the form "XXX: ", the string supplied as an identifier does not
      /// need to include the ": " as this will be appended automatically. 
      /// It can be any string that will help you to identify the thread
      /// concerned.

      virtual void SetThreadIdentifier(
         const std::wstring &identifier) = 0;

      virtual void SetLogName(
         const std::string &name) = 0;

      virtual void SetLogName(
         const std::wstring &name) = 0;

      typedef unsigned long DataLength;

      virtual void LogMessage(
         const std::string &message) = 0;

      virtual void LogMessage(
         const std::wstring &message) = 0;

      virtual void LogMessage(
         const char * const pString) = 0;

      virtual void LogMessage(
         const wchar_t * const pString) = 0;

      virtual void LogMessage(
         const char * const pString,
         const DataLength stringLength) = 0;

      virtual void LogMessage(
         const wchar_t * const pString,
         const DataLength stringLength) = 0;

   protected :
      
		/// We never delete instances of this interface; you must manage the 
		/// lifetime of the class that implements it.

      ~ILogMessages() {}
};

} // End of namespace AmstelTech 
