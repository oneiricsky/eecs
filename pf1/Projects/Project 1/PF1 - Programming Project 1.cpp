#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

/*
    Skylar Miles – CSCE 20004-001 - Programming Foundations I – Section 1
    Programming Project 1 – Recipe Scaling Program
*/

/* Store exchange rate as a global constant */
const float USD_TO_EUR = 0.85;

/* Validate user input to ensure float.
    We do this by checking the cin error flag. */
float validateInput(std::string prompt) {
  float input;
  while (true) {
    std::cout << prompt;
    std::cin >> input;
    if (std::cin.fail()) {
      std::cout << "[!] Please use numbers." << std::endl;
      std::cin.clear();  // clear the error flag as we handled the error
      /* We use cin.ignore() to discard invalid input.*/
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else if (input <= 0)  // Avoid dividing by <=0
    {
      std::cout << "[!] Input must be greater than zero." << std::endl;
    } else {
      return input;  // Input is good; return it.
    }
  }
}

int main() {
  /* Declare (and initialize) variables in order to
      reserve our memory space. */
  float usd = 0, eur = 0, servings = 0, scaledServings = 0;

  /* Set precision for currency */
  std::cout << std::fixed << std::setprecision(2);

  /* Initial prompts */
  std::cout
      << "\nWelcome to the Recipe Scaling Program!\n"
         "\nCongratulations on getting hired as Chef!"
         "\nLet's work on scaling your American recipes to metric "
         "measurements and ingredient costs for different serving sizes.\n"
         "\nPlease enter the following details:"
      << std::endl;

  /* Prompt for original recipe servings */
  servings = validateInput("How many servings does your recipe make? ");
  /* Prompt for servings to scale to */
  scaledServings =
      validateInput("How many servings do you want to scale it to? ");
  /* Finally, we prompt for cost of ingredients. */
  usd = validateInput("What is the cost of your ingredients in USD? $");
  /* Convert USD to EUR */
  eur = usd * USD_TO_EUR;

  std::cout << "\nCost per serving in USD:      $" << usd / servings
            << "\nCost of ingredients in EUR:   €" << eur
            << "\nCost per serving in EUR:      €" << eur / servings
            << "\nTo scale your recipe from " << servings << " to "
            << scaledServings
            << ", you will need to multiply each ingredient by "
            << scaledServings / servings << std::endl;

  return 0;
}
