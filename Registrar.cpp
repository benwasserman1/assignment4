/*
Ben Wasserman
2280906
wasse114@mail.chapman.edu
CPSC 350 Section 3
Assignment #4: Registrar's Office

Purpose of this source file:

This file has three main classes implemented in it. The Registrar class,
which reads in the file and sets up the program is the first one. The student class,
which defines some attributes for each student is the next one. Finally, the window class is
implemented, which provides the functions that perform the bulk of the calculations.
*/


#include <iostream>
#include <fstream>
#include "Registrar.h"
#include "Queue.h"

using namespace std;

/*
These are just some global variables that are initialized. The integer, curr,
is used to track the current time that each student needs at the window.
The integer, time1, is used to track the unit of time
the simulation is currently on. The integer, waitArrayIterator, is used to iterate
through the array of wait times to caculate the mean and median of the waits. Finally,
the integer, timeCurr, is used to caclulate the longest idle time of the window.
*/
Queue <Student> q;
int curr = 0;
int time1 = 0;
int waitArrayIterator = 0;
int timeCurr = 0;
int temp = 10000000;

//BASIC REGISTRAR IMPLEMENTATION
/*
This is merely the default constructor. It initializes some variables to 0. Specifically,
windows - the number of windows, necessaryTime - the amount of time each student needs, checkInTime -
when each student arrives at the registrar's office, and students - the number of students
that show up to the registrar's office in a given simulation.
*/
Registrar::Registrar(){

  windows = 0;
  necessaryTime = 0;
  checkInTime = 0;
  students = 0;
}

/*
This is the destructor, and it really doesn't need to do anything in this case
because the objects are deleted in other classes.
*/
Registrar::~Registrar(){
}

/*
The function, fileReadIn, is the main method for the class Registrar.
*/
void Registrar::fileReadIn(string test){

  int curr;
  ifstream inFile(test);
  inFile >> windows;

  while (true){
    if (inFile.eof()){
      break;
    }
    inFile >> checkInTime >> students;
    for (int i = 0; i < students; ++i){
      inFile >> curr;
      Student s(checkInTime, curr);
      q.insert(s);
    }
  }
  Window w(windows);
  int size = q.getSize();
  for (int j = 0; j < size; ++j){
    w.pushToWindow(windows);
  }
}

//STUDENT IMPLEMENTATION
/*
This is the default constructor, which initializes the waitTime, or the time
the student arrives at the registrar. It also initializes the integer, timeAtWindow, which
is the time the student needs at the window.
*/
Student::Student(){
  waitTime = 0;
  timeAtWindow = 0;
}

/*
This is the overloaded constructor. It initializes the same variables as above,
but takes them as parameter inputs.
*/
Student::Student(int wait, int windowTime){
  waitTime = wait;
  timeAtWindow = windowTime;
}

/*
This is the destructor for the Student class, but it doesn't do anything
because the objects are destroyed in other destructors.
*/
Student::~Student()
{
}

/*
The function getWait is a getter for the waitTime, or the time the Student
arrives at the registrar.
*/
int Student::getWait(){
  return waitTime;
}

/*
The function getWindowTime is a getter for the timeAtWindow, or the time the
student needs at the window.
*/
int Student::getWindowTime(){
  return timeAtWindow;
}

/*
The function setWindowTime takes in the a parameter for a new time to set for
the variable timeAtWindow. It doesn't return anything, but sets that new value.
*/
void Student::setWindowTime(int newTime){
  timeAtWindow = newTime;
}

/*
The function setWait takes a parameter for a new time to set for the variable
waitTime, or the time the student arrives at the registrar.
*/
void Student::setWait(int newTime){
  waitTime = newTime;
}

//WINDOW IMPLEMENTATION
/*
This is the window default constructor. It doesn't do anything because the
overloaded constructor is the only thing that's called.
*/
Window::Window(){
}

/*
This is the window destructor. It deletes the arrays, windowArray, waitArray,
and idleArray. WindowArray is an array of students and the other two are arrays
of integers.
*/
Window::~Window(){
  delete [] windowArray;
  delete [] waitArray;
  delete [] idleArray;
}

/*
This is the overloaded constructor. It takes in the integer, windows, as a parameter,
and initializes a few variables. It initializes the numStudents to the size of the
queue. It also initializes a lot of integers that help us calculate the wait times
and idle times. Lastly, it initializes the arrays.
*/
Window::Window(int windows){
  numStudents = q.getSize();
  longWait = 0;
  totalIdleTime = 0;
  longIdle = 0;
  subtractValue = 0;
  tempIdx = windows +1;
  waitArray = new int[q.getSize()];
  idleArray = new int[windows];
  windowArray = new Student[windows];
  for (int i = 0; i < windows; ++i){
    windowArray[i].setWait(0);
  }
}

/*
The function pushToWindow is the main method for the class Window. It takes
the parameter windows as input, and doesn't return anything. It checks if the queue
is empty, iterates through the window of students, checks if the time the student needs
at the window is 0, and then it checks to see if it can send someone from the queue to an
open window. It also calls the functions that calculate the idle time and the wait time. After
each iteration the time is incremented.
*/
void Window::pushToWindow(int windows){

  while (!q.isEmpty())
  {
    for (int i = 0; i < windows; ++i)
    {
      if (windowArray[i].getWindowTime() == 0)
      {
        if (q.isEmpty())
        {
          cout << "The simulation is over" << endl;
          exit(0);
        }
        else{
          if (time1 >= q.peek().getWait())
          {
            windowArray[i] = q.remove();
            int wait = time1 - windowArray[i].getWait();
            calculateStudentWaitTime(wait);
          }
        }
      }
      else if (windowArray[i].getWindowTime() != 0)
      {
        int current = windowArray[i].getWindowTime();
        windowArray[i].setWindowTime(--current);
      }
      idleWindow(i, windows);
    }
  //printArray();
  time1++;
  }
}

/*
The function printArray doesn't take any parameters as input and doesn't return
anything. It merely prints every element of the array, and the time. It's main purpose
is to help debug.
*/
void Window::printArray()
{
  cout << "Window 1" << endl;
  cout << windowArray[0].getWait() << endl;
  cout << windowArray[0].getWindowTime() << endl;
  cout << time1 << endl;

  cout << "Window 2" << endl;
  cout << windowArray[1].getWait() << endl;
  cout << windowArray[1].getWindowTime() << endl;
  cout << time1 << endl;

  cout << "Window 3" << endl;
  cout << windowArray[2].getWait() << endl;
  cout << windowArray[2].getWindowTime() << endl;
  cout << time1 << endl;

  cout << "Window 4" << endl;
  cout << windowArray[3].getWait() << endl;
  cout << windowArray[3].getWindowTime() << endl;
  cout << time1 << endl;

  cout << "Window 5" << endl;
  cout << windowArray[4].getWait() << endl;
  cout << windowArray[4].getWindowTime() << endl;
  cout << time1 << endl;
}

/*
The function calculateStudentWaitTime doesn't return anything but it takes in one
input as a parameter. The integer, wait, which is the time a student goes to a window minus
the time that the arrived at the registrar, is used to caclulate the longest wait time
and the number of students that wait over 10 minutes.
*/
void Window::calculateStudentWaitTime(int wait){

  if (wait > 10)
  {
    longWait +=1;
  }
  if (wait > curr){
    curr = wait;
  }
  if (q.isEmpty())
  {
    //printArray();
    cout << "Longest wait time: " << curr << endl;
    cout << "Number of students waiting over 10 minutes: " << longWait << endl;
  }
  calculateMeanWaitTime(wait);
}

/*
The function calculateMeanWaitTime is called by calculateStudentWaitTime. It takes
in the parameter, wait, as input and doesn't return anything. This function creates
a new array that holds the value of every wait time. It uses this array to determine
the mean of the wait times.
*/
void Window::calculateMeanWaitTime(int wait)
{
  double sum = 0;
  waitArray[waitArrayIterator] = wait;
  waitArrayIterator++;

  if (q.isEmpty())
  {
    for (int i = 0; i < numStudents; ++i)
    {
      sum+=waitArray[i];
    }
    cout << "Mean wait time: " << sum/numStudents << endl;
    sortArray();
  }
}

/*
The funciton sortArray doesn't take in any input as a parameter and it doesn't
return anything. It merely sorts the array, as a helper method for the median calculation.
*/
void Window::sortArray()
{
  for (int i = 0; i < numStudents; ++i)
  {
    if (waitArray[i] > waitArray[i+1])
    {
      int temp = waitArray[i+1];
      waitArray[i+1] = waitArray[i];
      waitArray[i] = temp;
    }
  }
  calculateMedianWaitTime();
}

/*
The function calculateMedianWaitTime finds the median wait time. It does this
by checking if the number of elements in the array is even or odd. If the number
of elements are even, then the calculation is a little more involved, while if they're
odd we can merely divide the number of students by 2 to find the middle element.
*/
void Window::calculateMedianWaitTime()
{
  double median = 0;
  int y = (int) numStudents;
  if (y%2 == 0)
  {
    median = (waitArray[y/2] + waitArray[(y/2) -1])/2;
  }
  else
  {
    median = waitArray[y/2];
  }
  cout << "Median wait time: " << median << endl;
}

/*
The function idleWindow doesn't return anyting, but it takes in a couple parameters as
input. First, it takes in the integer, idx. Second, it takes in the integer, windows. These
are used to figure out if a window is idle, and for how long the window is idle. The function
also calls the function calculateLongestIdleTime.
*/
void Window::idleWindow(int idx, int windows){

  int longestIdleTime = 0;

  double y = (double) windows;

  if (windowArray[idx].getWindowTime() == 0)
  {
    totalIdleTime++;
    if (q.peek().getWait() > time1)
    {
       longestIdleTime = (q.peek().getWait() - time1);
    }
  }
  calculateLongestIdleTime(longestIdleTime, windows, idx);
  if (q.isEmpty())
  {
    cout << "Mean idle time: " << totalIdleTime/y << endl;
    exit(0);
  }
}

/*
The function calculateLongestIdleTime takes in an integer as input and doesn't
return anything. It calculates the longest idle time and the number of windows
that are idle for over 5 minutes. Note that, the number of windows that are
idle for over 5 minutes is checking for the number of instances of a window being
idle for five minutes at once, rather than merely the number of windows that are idle for
5 minutes total.
*/
void Window::calculateLongestIdleTime(int time2, int windows, int idx)
{

  if (time2 > 5 && time1 <= temp)
  {
    tempIdx = idx;
    temp = time1;
    longIdle++;
  }
  if (time2 > timeCurr)
  {
    timeCurr = time2;
  }
  if (q.isEmpty())
  {
    if (timeCurr == 0 && totalIdleTime > 0)
    {
      cout << "Longest idle time: 1" << endl;
    }
    else
    {
      //SHOULD IT BE ++timeCurr
      cout << "Longest idle time: " << timeCurr << endl;
    }
    cout << "Number of windows idle for over 5 minutes: " << longIdle << endl;
  }
}
