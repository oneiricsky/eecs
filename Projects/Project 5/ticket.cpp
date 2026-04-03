#include <iostream>
#include <string>

// Task 1 - Support Ticket Data Structure
// TODO: Add constructors (default and parameterized)
// TODO: Add destructor
class Ticket {
public:
  /* Getters */
  int getId() {
    return id;
  }
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
  void print() {
    std::cout << "Ticket ID: " << id << std::endl;
    std::cout << "Customer Name: " << customerName << std::endl;
    std::cout << "Level: " << level << std::endl;
    auto date = dateSubmitted;
    std::cout << "Date Submitted: " << date.month << "/" << date.day << "/"
              << date.year << std::endl;
    std::cout << "Resolution Time: " << resTime << " days" << std::endl;
  }

private:
  int id;
  std::string customerName;
  std::string level;
  struct date {
    int month;
    int day;
    int year;
  } dateSubmitted;
  int resTime;
};
