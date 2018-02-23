#pragma once

#include "CriticalSection.h"
#include "AutoResetEvent.h"
#include "Thread.h"
#include "TODO.h"

#include "../Common/NodeList.h"

#pragma TODO("BUG: - need to handle GetTickCount() wrap")

namespace AmstelTech 
{
	
namespace Win32 
{
	
class IProvideTickCount;

class CCallbackTimer : protected CThread 
{
   public :

      class Handle;

      friend class Handle;

      CCallbackTimer();
	  explicit CCallbackTimer(const IProvideTickCount &tickProvider);
      ~CCallbackTimer();

      void SetTimer(const Handle& hnd, DWORD millisecondTimeout, DWORD userData = 0);

      bool CancelTimer(
         const Handle &hnd);

      void InitiateShutdown();

   private :

      // Implement CThread

      virtual int Run();

      void SignalStateChange();

      class Node;

      friend class Node;

      void InsertNodeIntoPendingList(
         Node* pNode,
         DWORD millisecondTimeout,
         DWORD userData);

      DWORD HandleTimeouts();

      void HandleTimeout(Node* pNode) const;

      bool CancelTimer(Node* pNode);

      TNodeList<Node> m_pendingList;

      CCriticalSection m_criticalSection;
      CAutoResetEvent m_stateChangeEvent;

      volatile bool m_shutdown;
	  const IProvideTickCount& m_tickProvider;
	  
	  class WrapNode;

      friend class WrapNode;

      WrapNode *m_pWrapNode;

      DWORD m_lastTick;
};

///////////////////////////////////////////////////////////////////////////////
// CCallbackTimer::Handle
///////////////////////////////////////////////////////////////////////////////

class CCallbackTimer::Handle
{
   public :

      class Callback
      {
         public :

            virtual void OnTimer(
               Handle &hnd,
               DWORD userData) = 0;

            virtual ~Callback() {}
      };

      class Data;

      explicit Handle(
         Callback &callback);

      explicit Handle(
         Data *pData);
      
      Handle(
         const Handle &rhs);

      ~Handle();

      Handle &operator =(const Handle &rhs);

      bool operator ==(const Handle &rhs) const;
      bool operator !=(const Handle &rhs) const;
      bool operator <(const Handle &rhs) const;

      Data *Detatch();

   private :

      friend class CCallbackTimer::Node;
      friend class CCallbackTimer;

      explicit Handle(
         CCallbackTimer::Node *pNode);

      static CCallbackTimer::Node *SafeAddRef(
         CCallbackTimer::Node *pNode);

      static CCallbackTimer::Node *SafeRelease(
         CCallbackTimer::Node *pNode);

      CCallbackTimer::Node *m_pNode;
};

} // End of namespace Win32
} // End of namespace AmstelTech 