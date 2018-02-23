#pragma once

#include <wtypes.h>

namespace AmstelTech 
{

///////////////////////////////////////////////////////////////////////////////
// CNodeList
///////////////////////////////////////////////////////////////////////////////

class CNodeList
{
   public :

      class Node
      {
         public :

            Node *Next() const;

            void Next(Node *pNext);

            void AddToList(
               CNodeList *pList);

            void RemoveFromList();

            bool InList(
               const CNodeList &list) const;

            bool InList() const;

         protected :

            Node();
            ~Node();

         private :

            friend class CNodeList;

            void Unlink();

            Node *m_pNext;
            Node *m_pPrev;

            CNodeList *m_pList;
      };

      CNodeList();

      void PushNode(Node* pNode);

      Node* PopNode();

      Node* Head() const;

      void InsertAfter(
         Node *pNode, 
         Node *pNewNode);

      size_t Count() const;

      bool IsEmpty() const;

   private :

      friend void Node::RemoveFromList();

      void RemoveNode(Node &node);

      Node *m_pHead; 

      size_t m_numNodes;
};

///////////////////////////////////////////////////////////////////////////////
// TNodeList
///////////////////////////////////////////////////////////////////////////////

template <class T> class TNodeList : public CNodeList
{
   public :
      T *PopNode();
      T *Head() const;
      static T *Next(const T *pNode);
};

template <class T>
T *TNodeList<T>::PopNode()
{
   return static_cast<T*>(CNodeList::PopNode());
}

template <class T>
T *TNodeList<T>::Head() const
{
   return static_cast<T*>(CNodeList::Head());
}

template <class T>
T *TNodeList<T>::Next(const T *pNode)
{
   return static_cast<T*>(pNode->Next());
}

} // namespace AmstelTech 