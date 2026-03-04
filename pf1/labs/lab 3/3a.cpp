
#include <iostream>
using namespace std;

int main() {
    // Calculate area and volume of a cube
    double Height = 3.0;
    double Area = 6 * Height * Height;    // Correct formula for surface area
    double Volume = Height * Height * Height; // Correct formula for volume

    // Print results
    cout << "Height = " << Height << "\n";
    cout << "Area = " << Area << "\n";
    cout << "Volume = " << Volume << "\n";

    return 0;
}
