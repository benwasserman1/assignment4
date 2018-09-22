/*
Ben Wasserman
2280906
wasse114@mail.chapman.edu
CPSC 350 Section 3
Assignment #4: Registrar's Office
*/


#include <iostream>
#include "Queue.h"
#include "Registrar.h"


using namespace std;

int main(int argc, char** argv){

  if (argc > 1){
    string test = argv[1];
    Registrar q;
    q.fileReadIn(test);
  }
  else{
    cout << "Enter a parameter" << endl;
  }
}
