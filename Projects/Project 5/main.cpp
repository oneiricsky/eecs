#include "tms.h"
#include <fstream>
#include <iostream>

// Task 3 - Sorting Functionalities
// TODO: Implement first classic sorting algorithm (e.g. bubble sort or
//       insertion sort) to sort tickets by:
//         - Customer Name (ascending alphabetical order)
//         - Priority Level (highest priority ticket first)
// TODO: Implement second classic sorting algorithm (e.g. merge sort or
//       quick sort) to sort tickets by:
//         - Date Submitted (oldest ticket first)
//         - Estimated Resolution Time (longest time first)

// Task 4 - Performance Analysis
// TODO: Add execution timer to each sort function using <chrono> and print
//       elapsed time after each sort
// TODO: Add a data comparison counter to each sort function (incremented only
//       when comparing ticket attributes, not loop counters) and print the
//       number of comparisons after each sort

// Task 5 - User Interaction
// TODO: Implement a menu-based interface in main() that lets users:
//         1. Load ticket data from file
//         2. Print all tickets
//         3. Add a new ticket
//         4. Edit an existing ticket
//         5. Delete a ticket
//         6. Sort by Customer Name
//         7. Sort by Priority Level
//         8. Sort by Date Submitted
//         9. Sort by Estimated Resolution Time
//         0. Exit

int main() {
  std::fstream file("tickets.csv");
  TMS tms;
  tms.loadTickets(file);
  tms.printTickets();
  // TODO: Replace the demo code above with the menu-based interface (Task 5)

  return 0;
}