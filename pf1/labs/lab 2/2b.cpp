// Include statements
#include <iostream>
using namespace std;

// Main function
int main() {
  // Constant declaration
  float x = 100;

  // Get user input
  float y = 0;
  cout << "Enter value for y: " << endl;
  cin >> y;

  // Perform arithmetic operations
  float sum = x + y;
  float difference = x - y;
  float quotient = x / y;
  float remainder = int(x) % int(y);
  float product = x * y;

  // Prfloat results
  cout << "The sum (x + y) is: " << sum << endl;
  cout << "The difference (x - y) is: " << difference << endl;
  cout << "The quotient (x / y) is: " << quotient << endl;
  cout << "The remainder (x % y) is: " << remainder << endl;
  cout << "The product (x * y) is: " << product << endl;
  return 0;
}
