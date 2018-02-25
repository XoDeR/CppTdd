#include "CallbackTimerQueue.h"
#include "Utils.h"
#include "Exception.h"
#include "TickCountProvider.h"

namespace AmstelTech 
{
	
namespace Win32 
{
	
///////////////////////////////////////////////////////////////////////////////
// CCallbackTimerQueue::TimerData
///////////////////////////////////////////////////////////////////////////////

class CCallbackTimerQueue::TimerData
{
	public :
	
   TimerData(
      Timer &timer,
      DWORD timeout,
      UserData userData);

   void UpdateData(
         Timer &timer,
         DWORD timeout,
         UserData userData);

      void OnTimer();

      bool IsBefore(
         const TimerData &rhs) const;

      DWORD TimeUntilTimeout(
         const DWORD now) const;

   private :
   
      Timer *m_pTimer;
   
      DWORD m_timeout;
   
      UserData m_userData;
};

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

static const CTickCountProvider s_tickProvider;

static const DWORD s_tickCountMax = 0xFFFFFFFF;

static const DWORD s_timeoutMax = s_tickCountMax / 4 * 3;

///////////////////////////////////////////////////////////////////////////////
// CCallbackTimerQueue
///////////////////////////////////////////////////////////////////////////////

CCallbackTimerQueue::CCallbackTimerQueue(
   const IProvideTickCount &tickProvider)
   :  m_tickProvider(tickProvider),
      m_wrapPoint(m_queue.end()),
      m_maxTimeout(s_timeoutMax)
{   
}

CCallbackTimerQueue::CCallbackTimerQueue(
   const DWORD maxTimeout,
   const IProvideTickCount &tickProvider)
   :  m_tickProvider(tickProvider),
      m_wrapPoint(m_queue.end()),
      m_maxTimeout(maxTimeout)
{   
}

CCallbackTimerQueue::CCallbackTimerQueue()
   :  m_tickProvider(s_tickProvider),
      m_wrapPoint(m_queue.end()),
      m_maxTimeout(s_timeoutMax)
{
}

CCallbackTimerQueue::CCallbackTimerQueue(
   const DWORD maxTimeout)
   :  m_tickProvider(s_tickProvider),
      m_wrapPoint(m_queue.end()),
      m_maxTimeout(maxTimeout)
{
}

CCallbackTimerQueue::~CCallbackTimerQueue()
{
   for (TimerQueue::iterator it = m_queue.begin(); it != m_queue.end(); ++it)
   {
      if (it != m_wrapPoint)
      {
         delete *it;
      }
   }
}

CCallbackTimerQueue::Handle CCallbackTimerQueue::SetTimer(
   Timer &timer,
   const DWORD timeoutMillis,
   const UserData userData)
{
   bool wrapped = false;

   TimerData *pData = CreateTimer(timer, timeoutMillis, userData, wrapped);

   return InsertTimer(pData, wrapped);
}

CCallbackTimerQueue::TimerData *CCallbackTimerQueue::CreateTimer(
   Timer &timer,
   const DWORD timeoutMillis,
   const UserData userData,
   bool &wrapped) const
{
   if (timeoutMillis > m_maxTimeout)
   {
      throw CException(_T("CCallbackTimerQueue::CreateTimer()"), _T("Timeout value is too large, max = ") + ToString(m_maxTimeout));
   }

   const DWORD timeout = GetAbsoluteTimeout(timeoutMillis, wrapped);

   return new TimerData(timer, timeout, userData);
}

DWORD CCallbackTimerQueue::GetAbsoluteTimeout(
   const DWORD timeoutMillis,
   bool &wrapped) const
{
   const DWORD now = m_tickProvider.GetTickCount();

   const DWORD timeout = now + timeoutMillis;

   wrapped = (timeout < now);

   return timeout;
}

CCallbackTimerQueue::Handle CCallbackTimerQueue::InsertTimer(
   TimerData *pData,
   const bool wrapped)
{
   if (wrapped && m_wrapPoint == m_queue.end())
   {
      m_wrapPoint = m_queue.insert(m_queue.end(), 0);      
   }
   
   TimerQueue::iterator wrapPoint = m_wrapPoint;

   TimerQueue::iterator it = (wrapped ? ++wrapPoint :  m_queue.begin());
   // insert into the list in the right place

   while (it != m_queue.end() && it != m_wrapPoint && (*it)->IsBefore(*pData))
   {
      ++it;
   }

   it = m_queue.insert(it, pData);

   Handle handle = reinterpret_cast<Handle>(pData);

   m_handleMap[handle] = it;

   return handle;
}

bool CCallbackTimerQueue::ResetTimer(
   Handle &handle, 
   Timer &timer,
   const DWORD timeoutMillis,
   const UserData userData)
{
   bool wasPending = false;

   TimerData *pData = 0;
   
   if (handle != InvalidHandleValue)
   {
      pData = RemoveTimer(handle);
   }

   bool wrapped = false;

   if (pData)
   {
      const DWORD timeout = GetAbsoluteTimeout(timeoutMillis, wrapped);
   
      pData->UpdateData(timer, timeout, userData);

      wasPending = true;
   }
   else
   {
      pData = CreateTimer(timer, timeoutMillis, userData, wrapped);
   }

   handle = InsertTimer(pData, wrapped);

   return wasPending;
}

bool CCallbackTimerQueue::CancelTimer(
   Handle &handle)
{
   TimerData *pData = RemoveTimer(handle);
      
   handle = InvalidHandleValue;

   bool wasPending = pData != 0;

   delete pData;

   return wasPending;
}

CCallbackTimerQueue::TimerData *CCallbackTimerQueue::RemoveTimer(
   Handle handle)
{
   TimerData *pData = 0;

   HandleMap::iterator mapIt = m_handleMap.find(handle);

   if (mapIt != m_handleMap.end())
   {
      TimerQueue::iterator it = mapIt->second;

      pData = *it;

      m_queue.erase(it);
      m_handleMap.erase(mapIt);
   }

   return pData;
}

DWORD CCallbackTimerQueue::GetNextTimeout() const
{
   DWORD timeout = INFINITE;

   TimerQueue::const_iterator it = m_queue.begin();

   if (it != m_queue.end())
   {
      const DWORD now = m_tickProvider.GetTickCount();

      if (it == m_wrapPoint)
      {
         ++it;
      }

      TimerData *pData = *it;

      timeout = pData->TimeUntilTimeout(now);

      if (timeout > s_timeoutMax)
      {
         timeout = 0;
      }
   }  

   return timeout;
}

void CCallbackTimerQueue::HandleTimeouts()
{
   while (0 == GetNextTimeout())
   {
      TimerQueue::iterator it = m_queue.begin();
      
      if (it != m_queue.end())
      {
         if (it == m_wrapPoint)
         {  
            ++it;
          
            m_queue.erase(m_wrapPoint);

            m_wrapPoint = m_queue.end();
         }

         TimerData *pData = *it;

         m_queue.erase(it);
         m_handleMap.erase(reinterpret_cast<Handle>(pData));

         pData->OnTimer();

         delete pData;
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
// CCallbackTimerQueue::TimerData
///////////////////////////////////////////////////////////////////////////////

CCallbackTimerQueue::TimerData::TimerData(
   Timer &timer,
   DWORD timeout,
   UserData userData)
   :  m_pTimer(&timer), 
      m_timeout(timeout),
      m_userData(userData)
{
}

void CCallbackTimerQueue::TimerData::UpdateData(
   Timer &timer,
   DWORD timeout,
   UserData userData)
{
   m_pTimer = &timer; 
   m_timeout = timeout;
   m_userData = userData;
}

void CCallbackTimerQueue::TimerData::OnTimer()
{
   m_pTimer->OnTimer(m_userData);
}

bool CCallbackTimerQueue::TimerData::IsBefore(
   const TimerData &rhs) const
{
   return m_timeout < rhs.m_timeout;
}

DWORD CCallbackTimerQueue::TimerData::TimeUntilTimeout(
   const DWORD now) const
{
   return m_timeout - now;
}

} // End of namespace Win32
} // End of namespace AmstelTech 