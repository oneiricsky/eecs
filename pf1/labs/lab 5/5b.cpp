#include <iostream>
using namespace std;

int main()
{
   // Get number from user
   int input = 0;
   cout << "Enter a number:\n";
   cin >> input;

   // Print numbers from [1..input]
   for (int num = 1; num <= input; num++)
      cout << num << " ";
   cout << endl;

   // Print EVEN numbers from [0..input]
   for (int num = 0; num < input; num++)
      if (num % 2 == 0)
         cout << num << " ";
   cout << endl;

   // Print ODD numbers from [input..1]
   for (int num = input; num >= 1; num--)
      if (num % 2 == 1)
         cout << num << " ";
   cout << endl;

   return 0;
}

