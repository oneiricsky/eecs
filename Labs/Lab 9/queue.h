//-----------------------------------------------------------
//  Purpose:    Header file for the Queue class.
//  Author:     John Gauch
//-----------------------------------------------------------
#ifndef QUEUE_H
#define QUEUE_H

#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

const int QUEUE_SIZE = 1000;

//-----------------------------------------------------------
// Define the queue class interface.
//-----------------------------------------------------------
class Queue {
public:
  // constructor functions
  Queue();
  ~Queue();

  // general queue operations
  bool IsFull();
  bool IsEmpty();
  void Insert(int Number);
  void Remove(int &Number);
  int Remove();
  int GetLength();
  void Print();

private:
  int Data[QUEUE_SIZE];
  int End;
};

#endif
