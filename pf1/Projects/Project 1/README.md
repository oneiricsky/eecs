# CSCE 20004 -- Programming Foundations I -- Programming Project 1 Report

**Skylar Miles**  
*August 22nd, 2025*

---

## Academic Integrity Statement

I pledge that I have neither given nor received unauthorized help on this programming assignment. I have written this report myself in my own words.

---

## Problem Statement

I was hired as head chef at a restaurant.  
I need to create a program that allows me to scale American recipes to metric currency.  
First, the program should ask how many the original recipe makes.  
The program should take the amount of servings I need to make.  
Then, it should ask me the pricing of the ingredients in USD.  
After, we should calculate the cost of each serving, first in USD, then in EUR.  
Finally, we can tell how many times we must multiply each ingredient in order to properly scale our recipe.

---

## Design

To solve the problem, I decided to use simple math with `double` data types to preserve precision in currency and serving size calculations. I created a function called `convertUSD()` to handle currency conversion, keeping the logic modular and easy to reuse.

---

## Implementation

I started off by declaring 3 `double` variables: `double usd, servings, scaledServings;` to store needed information in my `main()` function. I wrap `std::cin` and `std::cout` in a function, `validateInput()`, which takes in the prompt, and valides the user input to ensure it is a number. If not, I ask the user to use numbers and reprompt them. I do this by checking the error flag on `std::cin`. I then use my `convertUSD()` function to calculate the currency conversion and return `double eur;`. To find the scaling factor, I simply divide `scaledServings/servings`. I have checks in place to ensure the user can never divide by zero.
 
In order to output currencies with proper formatting, I use `std::setprecision` and `std::fixed` to ensure two decimal places.

---

## Testing

**Results of tests:**

```text
Congratulations on getting hired as Chef! Let's work on scaling your American recipes to metric measurements and ingredient costs for different serving sizes.

Welcome to the Recipe Scaling Program!
Please enter the following details:
How many servings does your recipe make? 4

How many servings do you want to scale it to? 12

What is the cost of your ingredients in USD? $5.21

Cost per serving in USD: $1.30
Cost of ingredients in EUR: €4.43
Cost per serving in EUR: €1.11
To scale your recipe from 4.00 to 12.00, you will need to multiply each ingredient by 3.00
```
```text
Congratulations on getting hired as Chef! Let's work on scaling your American recipes to metric measurements and ingredient costs for different serving sizes.


Welcome to the Recipe Scaling Program!
Please enter the following details:
How many servings does your recipe make? cat
Please use numbers.

How many servings does your recipe make? 4

How many servings do you want to scale it to? dog
Please use numbers.

How many servings do you want to scale it to? 12

What is the cost of your ingredients in USD? $mouse
Please use numbers.

What is the cost of your ingredients in USD? $5.21

Cost per serving in USD: $1.25
Cost of ingredients in EUR: €4.25
Cost per serving in EUR: €1.06
To scale your recipe from 4.00 to 12.00, you will need to multiply each ingredient by 3.00
```
## Conclusions

The overall result of the assignment was a success as I was able to complete all requirements. I already have some knowledge of C++, thus this was a simple project. Overall, the project took approximately two hours to complete, including the report. What I would do differently is implementing error handling (i.e., restarting the program on an invalid input and explaining the error).