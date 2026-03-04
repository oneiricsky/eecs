#include <cstdlib>
#include <iostream>
using namespace std;

int main()
{
  // Declare array of integers
  const int DATA_SIZE = 20;
  int data[DATA_SIZE] = {0};

  // Zeros
  for (int i = 0; i < DATA_SIZE; ++i)
    cout << data[i] << " ";
  cout << endl;

  // Initialize array
  for (int index = 0; index < DATA_SIZE; index++)
    data[index] = random() % 100;

  // Print array
  for (int index = 0; index < DATA_SIZE; index++)
    cout << data[index] << " ";
  cout << endl;

  // Reverse array
  for (int index = 0; index < DATA_SIZE /2; index++)
  {
    int t = data[index];
    data[index] = data[DATA_SIZE-1-index];
    data[DATA_SIZE-1-index] = t;
  }

  // Print array
  for (int index = 0; index < DATA_SIZE; index++)
    cout << data[index] << " ";
  cout << endl;

  return 0 ;
}


