#include "../Platform/Platform.h"

#include "CallbackTimerQueue.h"
#include "Utils.h"
#include "Exception.h"
#include "TickCountProvider.h"
#include "ICriticalSection.h"

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
	
	TimerData();
	
   TimerData(
      Timer &timer,
      UserData userData);

   void UpdateData(
         Timer &timer,
         UserData userData);

      void OnTimer();

		bool IsOneShotTimer() const;
		
		bool IsMaintenanceTimer(
         const CCallbackTimerQueue *pQueue) const;

   private :
   
      Timer *m_pTimer;
   
      UserData m_userData;
	  
	  const bool m_oneShotTimer;
};

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

static const CTickCountProvider s_tickProvider;

static const Milliseconds s_tickCountMax = 0xFFFFFFFF;

static const Milliseconds s_timeoutMax = s_tickCountMax - 1;

#pragma warning(push, 4)
#pragma warning(disable: 4268)   // 'const' static/global data initialized with 
                                 // compiler generated default constructor fills 
                                 // the object with zeros

static const LARGE_INTEGER s_zeroLargeInteger;  // Rely on static init to provide 
                                                // us with a LARGE_INTEGER zero.
#pragma warning(pop)

///////////////////////////////////////////////////////////////////////////////
// Static members
///////////////////////////////////////////////////////////////////////////////

#pragma TODO("Move to its own file?")

IQueueTimers::Handle IQueueTimers::InvalidHandleValue = 0;

///////////////////////////////////////////////////////////////////////////////
// CCallbackTimerQueue
///////////////////////////////////////////////////////////////////////////////

CCallbackTimerQueue::CCallbackTimerQueue(
   const IProvideTickCount &tickProvider)
   :  m_tickProvider(tickProvider),
      m_maxTimeout(s_timeoutMax),
      m_lastCount(s_zeroLargeInteger),
      m_maintenanceTimer(CreateTimer())
{   
   SetMaintenanceTimer();
}

CCallbackTimerQueue::CCallbackTimerQueue()
   :  m_tickProvider(s_tickProvider),
      m_maxTimeout(s_timeoutMax),
      m_lastCount(s_zeroLargeInteger),
      m_maintenanceTimer(CreateTimer())
{
   SetMaintenanceTimer();
}

CCallbackTimerQueue::~CCallbackTimerQueue()
{
   try
   {
      for (HandleMap::iterator it = m_handleMap.begin(); it != m_handleMap.end(); ++it)
      {
         TimerData *pData = reinterpret_cast<TimerData*>(it->first);

         delete pData;
      }
   }
   catch(...)
   {
#pragma TODO("what exception should we be catching here???")
   }
}

CCallbackTimerQueue::Handle CCallbackTimerQueue::CreateTimer()
{
   TimerData *pData = new TimerData();

   Handle handle = reinterpret_cast<Handle>(pData);

   MarkHandleUnset(handle);

   return reinterpret_cast<Handle>(pData);
}

bool CCallbackTimerQueue::SetTimer(
   const Handle &handle, 
   Timer &timer,
   const Milliseconds timeout,
   const UserData userData)
{
   if (timeout > m_maxTimeout)
   {
      throw CException(
         _T("CCallbackTimerQueue::SetTimer()"), 
         _T("Timeout value is too large, max = ") + ToString(m_maxTimeout));
   }

   HandleMap::iterator it = ValidateHandle(handle);

   const bool wasPending = CancelTimer(handle, it);

   TimerData *pData = reinterpret_cast<TimerData*>(it->first);

   pData->UpdateData(timer, userData);

   InsertTimer(handle, pData, timeout);

   return wasPending;
}

bool CCallbackTimerQueue::CancelTimer(
   const Handle &handle)
{
   return CancelTimer(handle, ValidateHandle(handle));
}

bool CCallbackTimerQueue::DestroyTimer(
   Handle &handle)
{
   HandleMap::iterator it = ValidateHandle(handle);

   TimerData *pData = reinterpret_cast<TimerData*>(it->first);

   const bool wasPending = CancelTimer(handle, it);

   m_handleMap.erase(it);

   delete pData;

   handle = InvalidHandleValue;

   return wasPending;
}

bool CCallbackTimerQueue::DestroyTimer(
   const Handle &handle)
{
   Handle handle_ = handle;

   return DestroyTimer(handle_);
}

void CCallbackTimerQueue::SetTimer(
   Timer &timer,
   const Milliseconds timeout,
   const UserData userData)
{
   if (timeout > m_maxTimeout)
   {
      throw CException(
         _T("CCallbackTimerQueue::SetTimer()"), 
         _T("Timeout value is too large, max = ") + ToString(m_maxTimeout));
   }

   TimerData *pData = new TimerData(timer, userData);

   Handle handle = reinterpret_cast<Handle>(pData);

   IInsertTimer(handle, pData, timeout);
}

Milliseconds CCallbackTimerQueue::GetMaximumTimeout() const
{
   return m_maxTimeout;
}

ULONGLONG CCallbackTimerQueue::GetTickCount64()
{
   const DWORD lastCount = m_lastCount.LowPart;

   m_lastCount.LowPart = m_tickProvider.GetTickCount();

   if (m_lastCount.LowPart < lastCount)
   {
      ICriticalSection::Owner lock(m_criticalSection);

      if (m_lastCount.LowPart < lastCount)
      {
         m_lastCount.HighPart++;

         SetMaintenanceTimer();
      }
   }

   return m_lastCount.QuadPart;
}

void CCallbackTimerQueue::InsertTimer(
   const Handle &handle,
   TimerData * const pData,
   const Milliseconds timeout)
{
   const ULONGLONG now = GetTickCount64();

   const ULONGLONG absoluteTimeout = now + timeout;

   if (absoluteTimeout < now)
   {
      throw CException(
         _T("CCallbackTimerQueue::InsertTimer()"), 
         _T("Timeout will extend beyond the wrap point of GetTickCount64(). ")
         _T("Well done at having your machine running for this long, ")
         _T("but this is outside of our specificiation..."));
   }

   TimerQueue::iterator it = m_queue.insert(TimerQueue::value_type(absoluteTimeout, pData));

   m_handleMap[handle] = it;
}

CCallbackTimerQueue::HandleMap::iterator CCallbackTimerQueue::ValidateHandle(
   const Handle &handle)
{
   HandleMap::iterator it = m_handleMap.find(handle);

   if (it == m_handleMap.end())
   {
// The following warning is generated when /Wp64 is set in a 32bit build. At present I think
// it's due to some confusion, and even if it isn't then it's not that crucial...
#pragma warning(push, 4)
#pragma warning(disable: 4244)
      throw CException(
         _T("CCallbackTimerQueue::ValidateHandle()"), 
         _T("Invalid timer handle: ") + ToString(handle));
#pragma warning(pop)
   }
   
   return it;
}

bool CCallbackTimerQueue::CancelTimer(
   const Handle &handle,
   const HandleMap::iterator &it)
{
   bool wasPending = false;
   
   if (it->second != m_queue.end())
   {
      m_queue.erase(it->second);

      MarkHandleUnset(handle);

      wasPending = true;
   }

   return wasPending;
}

Milliseconds CCallbackTimerQueue::GetNextTimeout() 
{
   Milliseconds timeUntilTimeout = INFINITE;

   TimerQueue::const_iterator it = m_queue.begin();

   if (it != m_queue.end())
   {
      if (it->second->IsMaintenanceTimer(this))
      {
         it++;
      }

      if (it != m_queue.end())
      {
         const ULONGLONG now = GetTickCount64();

         const ULONGLONG timeout = it->first;

         const ULONGLONG ticksUntilTimeout = timeout - now;
 
         if (ticksUntilTimeout > s_timeoutMax)
         {
            timeUntilTimeout = 0;
         }
         else
         {
            timeUntilTimeout = static_cast<Milliseconds>(ticksUntilTimeout);
         }
      }  
   }

   return timeUntilTimeout;
}

void CCallbackTimerQueue::HandleTimeouts()
{
   while (0 == GetNextTimeout())
   {
      TimerQueue::iterator it = m_queue.begin();
      
      TimerData *pData = it->second;

      m_queue.erase(it);

      Handle handle = reinterpret_cast<Handle>(pData);

      MarkHandleUnset(handle);

      pData->OnTimer();

      if (pData->IsOneShotTimer())
      {
         DestroyTimer(handle);
      }
   }
}

void CCallbackTimerQueue::MarkHandleUnset(
   Handle handle)
{
   m_handleMap[handle] = m_queue.end();
}

void CCallbackTimerQueue::SetMaintenanceTimer()
{
   // Sets a timer for the next GetTickCount() roll over...

   HandleMap::iterator it = ValidateHandle(m_maintenanceTimer);

   CancelTimer(m_maintenanceTimer, it);

   TimerData *pData = reinterpret_cast<TimerData*>(it->first);

   pData->UpdateData(m_maintenanceTimerHandler, reinterpret_cast<UserData>(this));

  {
      Handle handle = reinterpret_cast<Handle>(pData);

      const ULONGLONG now = GetTickCount64();

      const ULONGLONG absoluteTimeout = (now & 0xFFFFFFFF00000000) + 0x0000000100000000;
  
      TimerQueue::iterator it = m_queue.insert(TimerQueue::value_type(absoluteTimeout, pData));

      m_handleMap[handle] = it;
   }
}

///////////////////////////////////////////////////////////////////////////////
// CCallbackTimerQueue::MaintenanceTimerHandler
///////////////////////////////////////////////////////////////////////////////

void CCallbackTimerQueue::MaintenanceTimerHandler::OnTimer(
   UserData userData)
{
   reinterpret_cast<CCallbackTimerQueue *>(userData)->SetMaintenanceTimer();
}

///////////////////////////////////////////////////////////////////////////////
// CCallbackTimerQueue::TimerData
///////////////////////////////////////////////////////////////////////////////

CCallbackTimerQueue::TimerData::TimerData()
   :  m_pTimer(0), 
      m_userData(0),
      m_oneShotTimer(false)
{
}

CCallbackTimerQueue::TimerData::TimerData(
   Timer &timer,
   UserData userData)
   :  m_pTimer(&timer), 
      m_userData(userData),
      m_oneShotTimer(true)
{
}

void CCallbackTimerQueue::TimerData::UpdateData(
   Timer &timer,
   UserData userData)
{
   if (m_oneShotTimer)
   {
      throw CException(
         _T("CCallbackTimerQueue::UpdateData()"), 
         _T("Internal Error: Can't update one shot timers"));
   }

   m_pTimer = &timer; 
   m_userData = userData;
}

void CCallbackTimerQueue::TimerData::OnTimer()
{
   if (!m_pTimer)
   {
      throw CException(
         _T("CCallbackTimerQueue::OnTimer()"), 
         _T("Internal Error: Timer not set"));
   }

   m_pTimer->OnTimer(m_userData);
}

bool CCallbackTimerQueue::TimerData::IsOneShotTimer() const
{
   return m_oneShotTimer;
}

bool CCallbackTimerQueue::TimerData::IsMaintenanceTimer(
   const CCallbackTimerQueue *pQueue) const
{
   return m_userData == reinterpret_cast<UserData>(pQueue);
}

} // End of namespace Win32
} // End of namespace AmstelTech 