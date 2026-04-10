#include "ticket.h"

// Task 1 - Support Ticket Data Structure

Ticket::Ticket() : id(0), customerName(""), level("Low"), resTime(0) {
  dateSubmitted = {1, 1, 2000};
}

Ticket::Ticket(int id, const std::string &customerName,
               const std::string &level, int m, int d, int y, int resTime)
    : id(id), customerName(customerName), level(level), resTime(resTime) {
  dateSubmitted = {m, d, y};
}

Ticket::~Ticket() {}

int Ticket::getId() { return id; }
std::string Ticket::getCustomerName() { return customerName; }
std::string Ticket::getLevel() { return level; }
Ticket::date Ticket::getDateSubmitted() { return dateSubmitted; }
int Ticket::getResTime() { return resTime; }

void Ticket::setId(int newId) { id = newId; }
void Ticket::setCustomerName(std::string newCustomerName) {
  customerName = newCustomerName;
}
void Ticket::setLevel(std::string newLevel) {
  if (newLevel != "Low" && newLevel != "Medium" && newLevel != "High" &&
      newLevel != "Critical") {
    std::cerr << "Invalid level. Please enter 'Low', 'Medium', 'High', or "
                 "'Critical'."
              << std::endl;
    return;
  }
  level = newLevel;
}
void Ticket::setDateSubmitted(int m, int d, int y) {
  if (d < 1 || d > 31 || m < 1 || m > 12 || y < 1900) {
    std::cerr << "Invalid date. Please enter a valid date." << std::endl;
    return;
  }
  dateSubmitted = {m, d, y};
}
void Ticket::setResTime(int newResTime) { resTime = newResTime; }
void Ticket::print() {
  std::cout << "  Ticket ID:       " << id << std::endl;
  std::cout << "  Customer Name:   " << customerName << std::endl;
  std::cout << "  Level:           " << level << std::endl;
  std::cout << "  Date Submitted:  " << dateSubmitted.month << "/"
            << dateSubmitted.day << "/" << dateSubmitted.year << std::endl;
  std::cout << "  Resolution Time: " << resTime << " days" << std::endl;
}
