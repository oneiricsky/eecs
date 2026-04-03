#include "ticket.h"
#include <fstream>
#include <iostream>
#include <string>

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

/*
Ticket Management System
*/
class TMS {
public:
  void loadTickets(std::fstream &file) {
    if (!file.is_open()) {
      std::cerr << "Error opening file." << std::endl;
      return;
    }
    for (int i = 0; i < 1001; i++) {
      if (file.eof()) {
        break;
      }
      // id,customerName,level,month,day,year,resTime
      int id, month, day, year, resTime;
      std::string customerName, level;
      char comma; // To consume the commas in the CSV

      file >> id >> comma; // Find the ID and consume the comma
      std::getline(file, customerName, ',');
      std::getline(file, level, ',');
      file >> month >> comma >> day >> comma >> year >> comma >> resTime;
      tickets[i].setId(id);
      tickets[i].setCustomerName(customerName);
      tickets[i].setLevel(level);
      tickets[i].setDateSubmitted(month, day, year);
      tickets[i].setResTime(resTime);
    }
    file.close();
  };
  void printTickets() {
    std::cout
        << "ID\tCustomer Name\tLevel\tDate Submitted\tResolution Time (days)"
        << std::endl;
    for (int i = 0; i < 1000; i++) {
      if (tickets[i].getId() == 0) {
        break; // Assuming ID 0 means an empty slot
      }
      tickets[i].print();
      std::cout << std::endl;
    }
  };
  void addTicket() {};
  void editTicket(int ticketId) {};
  void deleteTicket(int ticketId) {};

private:
  Ticket tickets[1000]; // Assuming a maximum of 100 tickets for simplicity
};