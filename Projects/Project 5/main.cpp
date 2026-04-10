#include "tms.h"
#include <fstream>
#include <iostream>

// Task 5 - User Interaction

int main() {
  TMS tms;
  bool running = true;

  while (running) {
    std::cout << "\n=== Ticket Management System ===" << std::endl;
    std::cout << "  1. Load ticket data from file" << std::endl;
    std::cout << "  2. Print all tickets" << std::endl;
    std::cout << "  3. Add a new ticket" << std::endl;
    std::cout << "  4. Edit an existing ticket" << std::endl;
    std::cout << "  5. Delete a ticket" << std::endl;
    std::cout << "  6. Sort by Customer Name" << std::endl;
    std::cout << "  7. Sort by Priority Level" << std::endl;
    std::cout << "  8. Sort by Date Submitted" << std::endl;
    std::cout << "  9. Sort by Estimated Resolution Time" << std::endl;
    std::cout << "  0. Exit" << std::endl;
    std::cout << "Enter choice: ";

    int choice;
    std::cin >> choice;

    switch (choice) {
      case 1: {
        std::string filename;
        std::cout << "Enter filename: ";
        std::cin >> filename;
        std::fstream file(filename);
        tms.loadTickets(file);
        break;
      }
      case 2:
        tms.printTickets();
        break;
      case 3:
        tms.addTicket();
        break;
      case 4: {
        int ticketId;
        std::cout << "Enter ticket ID to edit: ";
        std::cin >> ticketId;
        tms.editTicket(ticketId);
        break;
      }
      case 5: {
        int ticketId;
        std::cout << "Enter ticket ID to delete: ";
        std::cin >> ticketId;
        tms.deleteTicket(ticketId);
        break;
      }
      case 6:
        tms.sortByName();
        break;
      case 7:
        tms.sortByLevel();
        break;
      case 8:
        tms.sortByDate();
        break;
      case 9:
        tms.sortByResTime();
        break;
      case 0:
        running = false;
        std::cout << "Exiting..." << std::endl;
        break;
      default:
        std::cout << "Invalid choice. Please try again." << std::endl;
    }
  }

  return 0;
}