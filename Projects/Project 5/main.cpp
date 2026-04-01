#include <iostream>

// Task 1 - Support Ticket Data Structure
// TODO: Add constructors (default and parameterized)
// TODO: Add destructor
class Ticket {
public:
  /* Getters */
  int getId() {
    return id;
  }
  // TODO: Rename getDescription() to getCustomerName() and update usages
  std::string getCustomerName() {
    return customerName;
  }
  std::string getLevel() {
    return level;
  }
  auto getDateSubmitted() {
    return dateSubmitted;
  }
  int getResTime() {
    return resTime;
  }
  /* Setters */
  void setId(int newId) {
    id = newId;
  }
  // TODO: Rename setDescription() to setCustomerName() and update usages
  void setCustomerName(std::string newCustomerName) {
    customerName = newCustomerName;
  }
  void setLevel(std::string newLevel) {
    if (newLevel != "Low" && newLevel != "Medium" && newLevel != "High" &&
        newLevel != "Urgent") {
      std::cerr << "Invalid level. Please enter 'Low', 'Medium', or 'High', or "
                   "'Urgent'."
                << std::endl;
      return;
    }
    level = newLevel;
  }
  void setDateSubmitted(int m, int d, int y) {
    if (d < 1 || d > 31 || m < 1 || m > 12 || y < 1900) {
      std::cerr << "Invalid date. Please enter a valid date." << std::endl;
      return;
    };
    dateSubmitted = {m, d, y};
  }
  void setResTime(int newResTime) {
    resTime = newResTime;
  }
  // TODO: Add print() method to display all ticket fields in a readable format

private:
  int id;
  // TODO: Renamed from description to customerName per project spec
  std::string customerName;
  std::string level;
  struct date {
    int month;
    int day;
    int year;
  } dateSubmitted;
  int resTime;
};

// Task 2 - Support Ticket Operations
// TODO: Implement loadTickets(Ticket tickets[], int &count, std::string
//       filename) to read ticket records from an input file
// TODO: Implement printTickets(Ticket tickets[], int count) to display all
//       stored support records in tabular format
// TODO: Implement addTicket(Ticket tickets[], int &count) to add a new support
//       ticket through menu-based input
// TODO: Implement editTicket(Ticket tickets[], int count, int ticketId) to
//       update the details of an existing ticket by its Ticket ID
// TODO: Implement deleteTicket(Ticket tickets[], int &count, int ticketId) to
//       remove a ticket from the system by its Ticket ID

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
  Ticket t;
  t.setId(123);
  t.setCustomerName("John Smith");
  t.setLevel("High");
  t.setDateSubmitted(10, 5, 2023);
  t.setResTime(4);

  std::cout << "Ticket ID: " << t.getId() << std::endl;
  std::cout << "Customer Name: " << t.getCustomerName() << std::endl;
  std::cout << "Level: " << t.getLevel() << std::endl;
  auto date = t.getDateSubmitted();
  std::cout << "Date Submitted: " << date.month << "/" << date.day << "/"
            << date.year << std::endl;
  std::cout << "Resolution Time: " << t.getResTime() << " days" << std::endl;

  // TODO: Replace the demo code above with the menu-based interface (Task 5)

  return 0;
}