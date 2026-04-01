//-----------------------------------------------------------
// Main program.
//-----------------------------------------------------------
#include "Stack.h"
using namespace std;

int main()
{
  Stack stack;
  array<int, 6> numbers = {3, 1, 4, 1, 5, 9};
  for (int num : numbers) {
    stack.Push(num);
    cout << "Pushed: " << num << endl;
    stack.Print();
  }
  cout << endl;
  for (int i = 0; i < numbers.size(); i++) {
    int num;
    stack.Pop(num);
    cout << "Popped: " << num << endl;
    stack.Print();
  }
}