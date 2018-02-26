#pragma once

namespace AmstelTech 
{

///////////////////////////////////////////////////////////////////////////////
// CNodeList
///////////////////////////////////////////////////////////////////////////////

/// An invasive doubly linked list where classes that wish to be nodes in the 
/// list must derive from CNodeList::Node. The list allows nodes to remove 
/// themselves from the list as a constant time operation.

class CNodeList
{
   public :

      /// The node class that classes must derive from to be able to be stored
      /// in the list.

      class Node
      {
         public :

            /// Return the next node in the list

            Node *Next() const;

            /// Set the given node to be this nodes 'next node'.

            void Next(
               Node *pNext);

            /// If this node is currently in a list then it is removed.

            void RemoveFromList();

            /// Returns true if this node is currently in the specified list.

            bool InList(
               const CNodeList &list) const;

            /// Returns true if this node is currently in any list.

            bool InList() const;

         protected :

            Node();
            ~Node();

         private :

            friend class CNodeList;

            void AddToList(
               CNodeList *pList);

            void Unlink();

            Node *m_pNext;
            Node *m_pPrev;

            CNodeList *m_pList;

            /// No copies do not implement
            Node(const Node &rhs);
            /// No copies do not implement
            Node &operator=(const Node &rhs);
      };

      /// Construct an empty node list.

      CNodeList();

      /// Push the given node onto the list.

      void PushNode(
         Node *pNode);

      /// Pop the head of the list and return it. Returns 0 if the list is
      /// empty.

      Node *PopNode();

      /// Return the head of the list. Returns 0 if the list is empty.

      Node *Head() const;

      /// Insert pNewNode after pNode in the list. If pNode is 0 then this
      /// degenerates to a PushNode().

      void InsertAfter(
         Node *pNode, 
         Node *pNewNode);

      /// Returns the number of nodes in the list.

      unsigned long Count() const;

      /// Returns true if the list contains no nodes.

      bool IsEmpty() const;

   private :

      friend void Node::RemoveFromList();

      void RemoveNode(Node &node);

      Node *m_pHead; 

      unsigned long m_numNodes;

      /// No copies do not implement
      CNodeList(const CNodeList &rhs);
      /// No copies do not implement
      CNodeList &operator=(const CNodeList &rhs);
};

///////////////////////////////////////////////////////////////////////////////
// TNodeList
///////////////////////////////////////////////////////////////////////////////

/// A template wrapper that makes an instance of CNodeList typesafe with respect
/// of the classes stored within it. Simply wraps the CNodeList::Node access
/// methods to work in terms of the template T rather than any class that 
/// happens to derive from CNodeList::Node.

template <class T> class TNodeList : public CNodeList
{
   public :
         
      T *PopNode();

      T *Head() const;

      static T *Next(
         const T *pNode);
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
T *TNodeList<T>::Next(
   const T *pNode)
{
   return static_cast<T*>(pNode->Next());
}

} // End of namespace AmstelTech