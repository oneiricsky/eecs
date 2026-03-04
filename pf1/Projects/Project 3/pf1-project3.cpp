#include <iostream>

/* 
  CSCE 20004 – Programming Foundations I
  Project 3 -- Drawing Shapes -- Skylar Miles
*/

int main() {

  int choice;
  int size;

  std::cout << "Choose what to draw:\n" << "1: Triangle\n" << "2: Diamond\n"
  << "3: Checkerboard\n" << "4: Exit\n" << "Enter your choice (1-4): ";

  std::cin >> choice;
  switch (choice) {
  case 1:
    std::cout << "Enter the size of the triangle (positive number): ";
    std::cin >> size;
    for (int row = 1; row <= size; row++) { // Rows
      for (int col = 1; col <= row; col++) {  // Columns
        std::cout << "* ";
      }
      std::cout << std::endl;
    }
    break;
  case 2:
    std::cout << "Enter the size of the diamond (positive number): ";
    std::cin >> size;

    // Loop through each row of the diamond
    for (int row = 1; row <= 2 * size - 1; row++) {
        int stars, spaces;
        // Determine number of stars and spaces for current row
        if (row <= size) { // Upper half
            // Calculate number of stars and spaces for current row
            stars = 2 * row - 1;
            spaces = size - row;
        } else { // Lower half
            stars = 2 * (2 * size - row) - 1;
            spaces = row - size;
        }
        
        // Print spaces
        for (int i = 0; i < spaces; i++) {
            std::cout << " ";
        }
        
        // Print stars
        for (int i = 0; i < stars; i++) {
            std::cout << "*";
        }
        
        std::cout << std::endl;
    }
    break;

  case 3:
    std::cout << "Enter the size of the checkerboard (positive number): ";
    std::cin >> size;

    for (int row = 0; row < size; row++) {        // Rows
      for (int col = 0; col < size; col++) {      // Columns
        /* Check for even sum of column and row counters */
        if ((row + col) % 2 == 0) {           
          std::cout << "* ";
        } else {
          std::cout << ". ";
        }
      }
      std::cout << std::endl;
    }

    default:
      std::cout << "Exiting program." << std::endl;
      break;
  }
  return 0;
}



