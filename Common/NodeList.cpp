#include "NodeList.h"

namespace AmstelTech 
{

CNodeList::CNodeList() 
   :  m_pHead(0), 
      m_numNodes(0) 
{
}

void CNodeList::PushNode(
   Node *pNode)
{
   pNode->AddToList(this);

   pNode->Next(m_pHead);

   m_pHead = pNode;

   ++m_numNodes;
}

CNodeList::Node *CNodeList::PopNode()
{
   Node *pNode = m_pHead;

   if (pNode)
   {
      RemoveNode(*pNode);
   }

   return pNode;
}

CNodeList::Node *CNodeList::Head() const
{
   return m_pHead;
}

size_t CNodeList::Count() const
{
   return m_numNodes;
}

bool CNodeList::IsEmpty() const
{
   return (0 == m_numNodes);
}

void CNodeList::RemoveNode(
   Node &node)
{
   if (&node == m_pHead)
   {
      m_pHead = node.Next();
   }

   node.Unlink();

   --m_numNodes;
}

void CNodeList::InsertAfter(
   Node *pNode, 
   Node *pNewNode)
{
   if (pNode)
   {
      pNewNode->AddToList(this);

      pNewNode->Next(pNode->m_pNext);

      pNode->Next(pNewNode);

      ++m_numNodes;
   }
   else
   {
      PushNode(pNewNode);
   }
}

///////////////////////////////////////////////////////////////////////////////
// CNodeList::Node
///////////////////////////////////////////////////////////////////////////////

CNodeList::Node::Node() 
   :  m_pNext(0), 
      m_pPrev(0), 
      m_pList(0) 
{
}

CNodeList::Node::~Node() 
{
   RemoveFromList();   

   m_pNext = 0;
   m_pPrev = 0;
   m_pList = 0;
}

CNodeList::Node *CNodeList::Node::Next() const
{
   return m_pNext;
}

void CNodeList::Node::Next(Node *pNext)
{
   m_pNext = pNext;

   if (pNext)
   {
      pNext->m_pPrev = this;
   }
}

void CNodeList::Node::AddToList(CNodeList *pList)
{
   m_pList = pList;
}

void CNodeList::Node::RemoveFromList()
{
   if (m_pList)
   {
      m_pList->RemoveNode(*this);
   }
}

bool CNodeList::Node::InList(
   const CNodeList &list) const
{
   return (m_pList == &list);
}

bool CNodeList::Node::InList() const
{
   return (m_pList != 0);
}

void CNodeList::Node::Unlink()
{
   if (m_pPrev)
   {
      m_pPrev->m_pNext = m_pNext;
   }

   if (m_pNext)
   {
      m_pNext->m_pPrev = m_pPrev;
   }
   
   m_pNext = 0;
   m_pPrev = 0;

   m_pList = 0;
}

} // namespace AmstelTech 