#include <iostream>
#include "ListNode.h"

using namespace std;

/*
This is my exception class used for the pop and a peek operations on an empty queue
*/
class Empty_Stack : public exception{
public:
  const char* what() const throw(){
    return "Queue is empty";
  }
};

template <typename E> class Queue
{
public:
  int numElements;
  DoublyLinkedList<E> list;

  //Queue constructor
  Queue(){
    numElements = 0;
  }

  //Queue destructor
  ~Queue(){
    //cout << "Object deleted" << endl;
  }

  //Inserting into the queue by using the doubly linked list function insertBack
  void insert(E data){
    ++numElements;
    list.insertBack(data);
    }


  //Removing an element from from the front of the queue using the removeFront function from the doubly linked list.
  E remove(){
    E c;
    if (isEmpty()){
      cout << "The queue is empty" << endl;
      return c;
    }
    --numElements;
    return list.removeFront();
    }

  //Returning the front element from the queue without returning it
  E peek(){

    if (isEmpty()){
      cout << "Queue is empty" << endl;
    }
    else{
      return list.checkFront();
  }
  E c;
  return c;
}

  //Checking to see if the queue is empty
  int isEmpty(){
    return (numElements == 0);
  }

  //Return the size of the queue
  int getSize(){
    return numElements;
  }
};
