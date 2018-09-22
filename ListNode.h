#include <iostream>

using namespace std;

template <class E> class ListNode
{
public:
  ListNode *next;
  ListNode *prev;
  E data;

  //Default constructor for the list node.
  ListNode()
  {
    next = NULL;
    prev = NULL;
  }

  //Overloaded constructor for the list node.
  ListNode(E d)
  {
    data = d;
    next = NULL;
    prev = NULL;
  }

  //Destructor for the list node.
  ~ListNode(){
    next = NULL;
    prev = NULL;
  }
};


template <class E>
class DoublyLinkedList //: protected List
{
private:
  ListNode<E> *front;
  ListNode<E> *back;
  unsigned int size;

public:

  //Default constructor for the doubly linked list
  DoublyLinkedList()
  {
    size = 0;
    front = NULL;
    back = NULL;
  }

  //Destructor for the doubly linked list.
  ~DoublyLinkedList()
  {
    cout << "Object deleted" << endl;
    ListNode<E> *curr = front;
    ListNode<E> *temp = front;
    while(curr != NULL){
      curr = curr -> next;
      temp = curr;
      delete curr;
      curr = temp;
    }
    delete temp;
    front = NULL;
    back = NULL;
  }

  //Returns the value at the front of the list without removing it.
  E checkFront(){
    ListNode<E> *node = front;
    return node-> data;
  }

  //Inserts a value at the front of the list
  void insertFront(E d)
  {
    ListNode<E> *node = new ListNode<E>(d);
    if (size == 0)
    {
      back = node;
    }
    else
    {
      front -> prev = node;
      node -> next = front;
    }
    front = node;
    ++size;
  }

  //Inserts a value at the back of the list
  void insertBack(E d)
  {
    ListNode<E> *node = new ListNode<E>(d);

    if (size == 0){
      front = node; //think about this..
    }
    else{
      back -> next = node;
      node -> prev = back;
    }
    back = node;
    ++size;
  }

  //Removes a value from the front of the list
  E removeFront()
  {
    ListNode<E> *node = front;
    if (front -> next == NULL)
    {
      back = NULL;
    }
    else
    {
      front -> next -> prev = NULL;
    }
    front = front -> next;
    --size;
    node-> next = NULL;
    E temp = node-> data;

    delete node;
    return temp;
  }

  //Removes a value from the back of the list
  E removeBack()
  {
    ListNode<E> *node = back;
    if (back -> prev == NULL)
    {
      front = NULL;
    }
    else
    {
      back -> prev -> next = NULL;
    }
    back = back -> prev;
    --size;
    node -> prev = NULL;
    E temp = node-> data;

    delete node;
    return temp;
  }

  //Removes a value based on the key
  E remove(int key)
  {
    ListNode<E> *curr = front;

    while(curr->data != key)
    {
      curr = curr-> next;
      if (curr == NULL){
        return 0;
      }
    }
    //found it - now let's delete it
    if (curr == front)
    {
      //removeFront();
      front = curr-> next;
    }
    else
    {
      curr->prev->next = curr-> next;

    }
    if (curr == back)
    {
      //removeBack();
      back = curr-> prev;
    }
    else{
      curr-> next-> prev = curr-> prev;
    }

    curr -> next = NULL;
    curr -> prev = NULL;
    --size;

    E temp = curr -> data;
    delete curr;

    return temp;
  }

  //Prints the list
  void printList()
  {
    ListNode<E> *curr = front;

    while(curr)
    {
      cout << curr -> data << endl;
      curr = curr -> next;
    }
  }

  //Finds a node based on the value
  int find(E value)
  {
    int idx = -1;
    ListNode<E> *curr = front;

    while(curr!=NULL) //while current is not equal to null or while the size is empty
    {
      ++idx;
      if (curr->data == value)
      {
        break;
      }
      else{
        curr = curr->next;
      }
    }
    if (curr == NULL)
      idx = -1;

    return idx;
  }

  // bool insertAfter(int pos, int value)
  // {
  //   return true;
  // }

  //Deletes a specified position of the list (through a parameter)
  E deletePos(int pos)
  {
    int idx = 0;
    ListNode<E> *curr = front;
    ListNode<E> *prev = front;

    while(idx != pos) //while the index isn't equal to the position we're looking for
    {
      prev = curr;
      curr = curr->next;
      idx++;
    }
    //found it
    prev->next = curr->next;
    curr->next = NULL;
    E d = curr->data;
    size--;

    delete curr;
    return d;

  }
};
