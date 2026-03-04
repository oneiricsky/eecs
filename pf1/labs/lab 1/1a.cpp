// Include statements
#include <iostream>
using namespace std;

// Main function
int main() {
  // Initialize variables
  string name = "Dad";
  float amount = 99.99;

  cout << "Enter name\n";
  cin >> name;
  cout << "Enter amount\n";
  cin >> amount;

  // Print an output message
  cout << "Hello " << name << endl;
  cout << "Please send " << amount << " dollars" << endl;
  cout << "Thanks!!" << endl;
  return 0;
}
