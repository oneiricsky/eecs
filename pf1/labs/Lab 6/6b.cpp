#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double num, root, error;

    cout << "Enter number:\n";
    cin >> num;

    // Square root using sqrt
    root = sqrt(num);
    cout << "sqrt(" << num << ") = " << root << endl;
    error = num - root * root;
    cout << "error= " << error << endl << endl;

    // Square root using pow
    root = pow(num, 0.5);
    cout << "pow(" << num << ",1/2) = " << root << endl;
    error = num - root * root;
    cout << "error= " << error << endl << endl;

    // Cube root using cbrt
    root = cbrt(num);
}
