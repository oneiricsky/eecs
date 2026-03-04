
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
    int step;
    cout << "Enter step size: ";
    cin >> step;
    cout << endl;

    if (step <= 0) {
        return 0;
    }

    cout << setw(10) << "degrees"
         << setw(10) << "radians"
         << setw(10) << "cos"
         << setw(10) << "sin"
         << endl;

    for (int degrees = 0; degrees <= 360; degrees += step) {
        double radians = degrees * M_PI / 180.0;
        cout << setw(10) << degrees
             << setw(10) << fixed << setprecision(5) << radians
             << setw(10) << fixed << setprecision(5) << cos(radians)
             << setw(10) << fixed << setprecision(5) << sin(radians)
             << endl;
    }

    return 0;
}

