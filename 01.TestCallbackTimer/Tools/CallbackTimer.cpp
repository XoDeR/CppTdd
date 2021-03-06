#include "CallbackTimer.h"
#include "Utils.h"
#include "Exception.h"
#include "TickCountProvider.h"

namespace AmstelTech 
{
	
namespace Win32 
{
	
///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////

static const CTickCountProvider s_tickProvider;

static const DWORD s_tickCountMax = 0xFFFFFFFF;

///////////////////////////////////////////////////////////////////////////////
// CCallbackTimer::Node
///////////////////////////////////////////////////////////////////////////////
class CCallbackTimer::Node : public CNodeList::Node
{
   public :

      friend CCallbackTimer;

      explicit Node(
         CCallbackTimer::Handle::Callback &callback);

      void SetTimeout(
         DWORD millisecondTimeout,
         DWORD userData);

      void AddRef();
      void Release();

      void OnTimer();

   private :

      DWORD m_millisecondTimeout;

      long m_ref;

      CCallbackTimer::Handle::Callback &m_callback;

      DWORD m_userData;
};

///////////////////////////////////////////////////////////////////////////////
// CCallbackTimer::WrapNode
///////////////////////////////////////////////////////////////////////////////

class CCallbackTimer::WrapNode : 
   public CCallbackTimer::Node, 
   private CCallbackTimer::Handle::Callback
{
   public :

      WrapNode() : Node(static_cast<CCallbackTimer::Handle::Callback &>(*this)) 
      {
         SetTimeout(0, 0);
      }

      void OnTimer(
         Handle &hnd,
         DWORD userData)
      {
      }
};

///////////////////////////////////////////////////////////////////////////////
// CCallbackTimer
///////////////////////////////////////////////////////////////////////////////

CCallbackTimer::CCallbackTimer(
   const IProvideTickCount &tickProvider)
   :  m_shutdown(false),
      m_tickProvider(tickProvider),
      m_pWrapNode(new WrapNode()),
      m_lastTick(0)
{
   Start();
}

CCallbackTimer::CCallbackTimer()
   :  m_shutdown(false),
      m_tickProvider(s_tickProvider),
      m_pWrapNode(new WrapNode()),
      m_lastTick(0)
{
   Start();
}

CCallbackTimer::~CCallbackTimer()
{
   InitiateShutdown();

   Wait();
   
   m_pWrapNode->RemoveFromList();

   delete m_pWrapNode;

   Node *pNode = m_pendingList.Head();

   while (pNode)
   {
      CancelTimer(pNode);

      pNode = m_pendingList.Head();
   }
}

int CCallbackTimer::Run()
{
   while (!m_shutdown)
   {
      const DWORD timeout = HandleTimeouts();
      
      m_stateChangeEvent.Wait(timeout);
   }
   
   return 0;
}

DWORD CCallbackTimer::HandleTimeouts() const
{
   const DWORD now = m_tickProvider.GetTickCount();

   DWORD timeout = INFINITE;

   CCriticalSection::Owner lock(m_criticalSection);

   Node *pNode = m_pendingList.Head();
   
   while (pNode)
   {
      const DWORD thisTimeout = pNode->m_millisecondTimeout;

      if (thisTimeout > now)
      {   
         timeout = thisTimeout - now;
         break;
      }
      else if (pNode != m_pWrapNode)
      {
         HandleTimeout(pNode);
      }
      else if (now < m_lastTick)
      {
         pNode = m_pendingList.Next(pNode);

         m_pWrapNode->RemoveFromList();
         
         while (pNode && pNode->Next())
         {
            pNode = m_pendingList.Next(pNode);
         }

         if (pNode)
         {
            m_pendingList.InsertAfter(pNode, m_pWrapNode);
         }
      }
      else
      {
         timeout = s_tickCountMax - now;
         break;
      }

      pNode = m_pendingList.Head();
   }
   
   m_lastTick = now;

   return timeout;
}

void CCallbackTimer::HandleTimeout(Node* pNode) const
{
   pNode->RemoveFromList();
   pNode->OnTimer();
   pNode->Release();
}

void CCallbackTimer::SetTimer(
   const Handle &hnd,
   DWORD millisecondTimeout,
   DWORD userData /* = 0 */)
{
   Node *pNode = hnd.m_pNode;

   if (!pNode)
   {
      throw CException(_T("CCallbackTimer::SetTimer()"),_T("Invalid handle"));
   }

   InsertNodeIntoPendingList(pNode, millisecondTimeout, userData);

   SignalStateChange();
}

void CCallbackTimer::InsertNodeIntoPendingList(
   Node *pNewNode,
   DWORD millisecondTimeout,
   DWORD userData)
{
   CCriticalSection::Owner lock(m_criticalSection);

   pNewNode->RemoveFromList();

   const DWORD now = m_tickProvider.GetTickCount();

   const DWORD absoluteTimeout = now + millisecondTimeout;

   pNewNode->SetTimeout(absoluteTimeout, userData);

   pNewNode->AddRef();

   // insert in list in time order ascending

   Node *pPrev = 0;

   Node *pNode = m_pendingList.Head();

   if (!pNode)
   {
      // this will be the only node in the list, so we need to add the 'wrap node'
      m_pendingList.PushNode(m_pWrapNode);
   
      pNode = m_pWrapNode;
   }
   
   if (absoluteTimeout < now)
   {
      // step past the wrap node...

      pPrev = m_pWrapNode;

      pNode = m_pendingList.Next(m_pWrapNode);
   }

   while (pNode && pNode->m_millisecondTimeout < pNewNode->m_millisecondTimeout && pNode != m_pWrapNode)
   {
      pPrev = pNode;

      pNode = m_pendingList.Next(pNode);
   }

   if (pPrev)
   {
      m_pendingList.InsertAfter(pPrev, pNewNode);         
   }
   else
   {
      m_pendingList.PushNode(pNewNode);
   }
}

bool CCallbackTimer::CancelTimer(
   const Handle &hnd)
{
   Node *pNode = hnd.m_pNode;

   if (!pNode)
   {
      throw CException(_T("CCallbackTimer::CancelTimer()"),_T("Invalid handle"));
   }

   const bool wasPending = CancelTimer(pNode);

   SignalStateChange();

   return wasPending;
}

bool CCallbackTimer::CancelTimer(
   Node *pNode)
{
   CCriticalSection::Owner lock(m_criticalSection);

   bool wasPending = false;

   if (pNode->InList(m_pendingList))
   {
      pNode->RemoveFromList();

      pNode->m_millisecondTimeout = 0;

      pNode->Release();

      wasPending = true;
   }

   return wasPending;
}

void CCallbackTimer::InitiateShutdown()
{
   m_shutdown = true;

   SignalStateChange();
}

void CCallbackTimer::SignalStateChange()
{
   m_stateChangeEvent.Set();
}

///////////////////////////////////////////////////////////////////////////////
// CCallbackTimer::Handle
///////////////////////////////////////////////////////////////////////////////

CCallbackTimer::Handle::Handle(
   CCallbackTimer::Handle::Callback &callback)
   :  m_pNode(new Node(callback))
{

}

CCallbackTimer::Handle::Handle(
   CCallbackTimer::Handle::Data *pData)
   :  m_pNode(reinterpret_cast<CCallbackTimer::Node*>(pData))
{

}

CCallbackTimer::Handle::Handle(
   const Handle &rhs)
   :  m_pNode(SafeAddRef(rhs.m_pNode))
{

}

CCallbackTimer::Handle::Handle(
   CCallbackTimer::Node *pNode)
   :  m_pNode(SafeAddRef(pNode))
{

}

CCallbackTimer::Handle::~Handle()
{
   m_pNode = SafeRelease(m_pNode);

   // warning: m_pNode not directly freed of zeroed in dtor
}

CCallbackTimer::Handle::Data *CCallbackTimer::Handle::Detatch()
{
   CCallbackTimer::Node *pNode = m_pNode;

   m_pNode = 0;

   return reinterpret_cast<Data*>(pNode);
}

CCallbackTimer::Handle &CCallbackTimer::Handle::operator =(
   const Handle &rhs)
{
   if (&rhs != this)
   {
      m_pNode = SafeRelease(m_pNode);
      
      m_pNode = SafeAddRef(rhs.m_pNode);
   }

   return *this;
}

bool CCallbackTimer::Handle::operator ==(
   const Handle &rhs) const
{
   return m_pNode == rhs.m_pNode;
}

bool CCallbackTimer::Handle::operator !=(
   const Handle &rhs) const
{
   return !operator ==(rhs);
}

bool CCallbackTimer::Handle::operator <(
   const Handle &rhs) const
{
   // warning: Possible use of null pointer m_pNode

   return m_pNode < rhs.m_pNode;
}

CCallbackTimer::Node *CCallbackTimer::Handle::SafeAddRef(
   CCallbackTimer::Node *pNode)
{
   if (pNode)
   {
      pNode->AddRef();
   }

   return pNode;
}

CCallbackTimer::Node *CCallbackTimer::Handle::SafeRelease(
   CCallbackTimer::Node *pNode)
{
   if (pNode)
   {
      pNode->Release();
   }

   return 0;

   // warning: Custodial pointer 'pNode' has not been freed or returned
}

///////////////////////////////////////////////////////////////////////////////
// CCallbackTimer::Node
///////////////////////////////////////////////////////////////////////////////

CCallbackTimer::Node::Node(
   CCallbackTimer::Handle::Callback &callback)
   :  m_millisecondTimeout(0),
      m_ref(1),
      m_callback(callback),
      m_userData(0)
{

}

void CCallbackTimer::Node::SetTimeout(
   DWORD millisecondTimeout,
   DWORD userData)
{
   const DWORD absoluteTimeout = ::GetTickCount() + millisecondTimeout;

   m_millisecondTimeout = absoluteTimeout;

   m_userData = userData;
}

void CCallbackTimer::Node::OnTimer()
{
   Handle hnd(this);

   const DWORD userData = m_userData;

   m_userData = 0;

   m_callback.OnTimer(hnd, userData);
}

void CCallbackTimer::Node::AddRef()
{
   ::InterlockedIncrement(&m_ref);
}

void CCallbackTimer::Node::Release()
{
   if (m_ref == 0)
   {
      // Error! double release
      throw CException(_T("CCallbackTimer::Node::Release()"), _T("m_ref is already 0"));
   }

   if (0 == ::InterlockedDecrement(&m_ref))
   {
      delete this;
   }
}

} // End of namespace Win32
} // End of namespace AmstelTech 