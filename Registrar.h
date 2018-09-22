#include <iostream>

using namespace std;

class Registrar
{
public:
  int totalTime;
  int checkInTime;
  int windows;
  int necessaryTime;
  int students;
  Registrar();
  ~Registrar();
  void fileReadIn(string test);
};

class Student
{
public:
  int timeAtWindow;
  int waitTime;
  Student();
  Student(int windowTime, int waitTime);
  ~Student();
  int getWait();
  int getWindowTime();
  void setWindowTime(int newTime);
  void setWait(int newTime);
};

class Window
{
public:
  double numStudents;
  int longWait;
  int longIdle;
  double totalIdleTime;
  int subtractValue;
  int *waitArray;
  Student *windowArray;
  int *idleArray;
  int tempIdx;
  Window();
  Window(int windows);
  ~Window();
  void pushToWindow(int windows);
  void calculateStudentWaitTime(int wait);
  void calculateMeanWaitTime(int wait);
  void printArray();
  void sortArray();
  void calculateMedianWaitTime();
  void idleWindow(int idx, int windows);
  void calculateLongestIdleTime(int time, int windows, int idx);
};
