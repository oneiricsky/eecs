#include <cctype>
#include <iostream>

/*
    Skylar Miles – CSCE 20004-001 - Programming Foundations I
    Programming Project 2 - Academic Advising System
*/

int main() {
  /* We declare our variables */
  int major = 0;
  bool calc = false;
  bool digDesign = false;
  char choice;

  /* Get major */
  std::cout << "Select your major\n"
               "-----------------------------------\n"
               "  1. Electrical Engineering (EE)\n"
               "  2. Computer Science (CS)\n"
               "  3. Computer Engineering (CE)\n"
               "-----------------------------------\n"
               "Enter your choice (1-3): ";
  std::cin >> major;

  /* Ask if they've taken calculus */
  std::cout << "Have you taken Calculus I (Y/N): ";
  std::cin >> choice;
  if (std::tolower(choice) == 'y')
    calc = true;

  /* Ask if they've taken digital design */
  std::cout << "Have you taken Digital Design (Y/N): ";
  std::cin >> choice;
  if (std::tolower(choice) == 'y')
    digDesign = true;

  std::cout << "--- Advising ---" << std::endl;
  switch (major) { // Check major
  case 1:          // If its Electrical Engineering
    if (calc) {
      std::cout << "You should consider taking Calculus II and Physics I"
                << std::endl;
    } else
      std::cout << "You should take Calculus I." << std::endl;
    break;

  case 2: // If its Computer Science
    if (calc) {
      std::cout << "You should consider taking Calculus II and Programming "
                   "Foundations I"
                << std::endl;
    } else
      std::cout << "You should take Calculus I." << std::endl;
    break;
  case 3: // If its Computer Engineering
    if (calc) {
      std::cout << "You should consider taking Calculus II and Discrete Math"
                << std::endl;
    } else
      std::cout << "You should take Calculus I." << std::endl;
    break;
  default: // This likely means they didn't give an valid input.
    std::cout << "Error: Invalid Input" << std::endl;
    break;
  }

  /* Check to see if they took digital design */
  if (!digDesign) {
    std::cout << "You should take Digital Design" << std::endl;
  }
  return 0;
}
