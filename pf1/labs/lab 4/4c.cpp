#include <iostream>
using namespace std;

int main() {
  int InputValue = 0;
  int TotalValue = 0;
  int CountValue = 0;

  // While loop to total up the daily sales
  while (true) {
    cout << "Enter input value (or -1 to stop):\n";
    cin >> InputValue;

    if (InputValue == -1) {
      break;
    }

    TotalValue += InputValue;
    ++CountValue;
  }

  if (CountValue > 0) {
    float AverageValue = static_cast<float>(TotalValue) / CountValue;
    cout << "Average: " << AverageValue << endl;
  }

  return 0;
}
