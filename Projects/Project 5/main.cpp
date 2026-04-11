#include "ticket.h"
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Task 2 - Support Ticket Operations
std::vector<Ticket> tickets;

void loadTickets(std::fstream &file) {
  if (!file.is_open()) {
    std::cerr << "Error opening file." << std::endl;
    return;
  }
  // Skip the header line
  std::string header;
  std::getline(file, header);

  // Make sure to clear existing tickets before loading new data
  tickets.clear();
  std::string line;
  while (std::getline(file, line)) { // While there are lines to read
    if (line.empty())                // If the line is empty, skip it
      continue;
    // id,customerName,level,month,day,year,resTime
    std::istringstream stringStream(line); // Get string from line
    int id, month, day, year, resTime;
    std::string customerName, level;
    char comma; // Delimiter

    // Read ID and skip comma
    stringStream >> id >> comma;
    // Get customer name
    std::getline(stringStream, customerName, ',');
    // Get urgency level
    std::getline(stringStream, level, ',');
    // Get date
    stringStream >> month >> comma >> day >> comma >> year >> comma >> resTime;
    // Add ticket to vector
    tickets.emplace_back(id, customerName, level, month, day, year, resTime);
  }
  file.close();
  std::cout << "Loaded " << tickets.size() << " tickets." << std::endl;
}

void printTickets() {
  // If there are no tickets...
  if (tickets.empty()) {
    std::cout << "No tickets to display." << std::endl;
    return;
  }
  // Print header
  std::cout << std::left << std::setw(8) << "ID" << std::setw(25)
            << "Customer Name" << std::setw(10) << "Level" << std::setw(16)
            << "Date Submitted" << "Resolution Time (days)" << std::endl;
  std::cout << std::string(83, '-') << std::endl;

  // Print each ticket
  for (auto &t : tickets) {        // For each ticket in the vector
    auto d = t.getDateSubmitted(); // Get the date submitted for the ticket
    // Convert date to string
    std::string dateStr = std::to_string(d.month) + "/" +
                          std::to_string(d.day) + "/" + std::to_string(d.year);

    // Print ticket details in  columns
    std::cout << std::left << std::setw(8) << t.getId() << std::setw(25)
              << t.getCustomerName() << std::setw(10) << t.getLevel()
              << std::setw(16) << dateStr << t.getResTime() << std::endl;
  }
  std::cout << "Total: " << tickets.size() << " tickets." << std::endl;
}

void addTicket() {
  // Generate new ID as max existing ID + 1
  int maxId = 10000; // Pad IDs to 5 digits
  for (auto &t : tickets) {
    // If the current ticket's ID is greater than maxId, update maxId
    if (t.getId() > maxId)
      maxId = t.getId();
  }
  // New ticket ID will be maxId + 1
  int id = maxId + 1;
  std::string customerName, level;
  int month, day, year, resTime;

  std::cin.ignore(); // Clear input buffer before reading strings
  // Get name
  std::cout << "Enter customer name: ";
  std::getline(std::cin, customerName);
  // Get priority level
  std::cout << "Enter level (Low/Medium/High/Urgent): ";
  std::cin >> level;
  // Get date
  std::cout << "Enter date submitted (month day year): ";
  std::cin >> month >> day >> year;
  // Get resolution time
  std::cout << "Enter estimated resolution time (days): ";
  std::cin >> resTime;
  // Add new ticket to vector
  tickets.emplace_back(id, customerName, level, month, day, year, resTime);
  std::cout << "Ticket " << id << " added successfully." << std::endl;
}

void editTicket(int ticketId) {
  for (auto &t : tickets) {
    if (t.getId() == ticketId) {
      std::cout << "Current ticket details:" << std::endl;
      t.print();
      std::cout << "What would you like to edit?" << std::endl;
      std::cout << "  1. Customer Name" << std::endl;
      std::cout << "  2. Level" << std::endl;
      std::cout << "  3. Date Submitted" << std::endl;
      std::cout << "  4. Resolution Time" << std::endl;

      int choice;
      std::cin >> choice;

      switch (choice) {
      case 1: {
        std::string newName;
        std::cin.ignore();
        std::cout << "Enter new customer name: ";
        std::getline(std::cin, newName);
        t.setCustomerName(newName);
        break;
      }
      case 2: {
        std::string newLevel;
        std::cout << "Enter new level (Low/Medium/High/Urgent): ";
        std::cin >> newLevel;
        t.setLevel(newLevel);
        break;
      }
      case 3: {
        int m, d, y;
        std::cout << "Enter new date (month day year): ";
        std::cin >> m >> d >> y;
        t.setDateSubmitted(m, d, y);
        break;
      }
      case 4: {
        int newResTime;
        std::cout << "Enter new resolution time (days): ";
        std::cin >> newResTime;
        t.setResTime(newResTime);
        break;
      }
      default:
        std::cout << "Invalid choice." << std::endl;
        return;
      }
      std::cout << "Ticket updated successfully." << std::endl;
      return;
    }
  }
  std::cout << "Ticket with ID " << ticketId << " not found." << std::endl;
}

void deleteTicket(int ticketId) {
  // Find the ticket with the given ID
  for (auto it = tickets.begin(); it != tickets.end(); ++it) {
    if (it->getId() == ticketId) { // If found
      tickets.erase(it);           // Delete it
      std::cout << "Ticket " << ticketId << " deleted successfully."
                << std::endl;
      return;
    }
  }
  std::cout << "Ticket with ID " << ticketId << " not found." << std::endl;
}

// Task 3 & 4 - Sorting with timing and comparison counting

int levelToInt(const std::string &level) {
  if (level == "Urgent")
    return 3;
  if (level == "High")
    return 2;
  if (level == "Medium")
    return 1;
  return 0; // Low
}

bool dateIsLess(const Ticket::date &a, const Ticket::date &b) {
  // if years are different
  if (a.year != b.year)
    return a.year < b.year; // Return true if a's year is less than b's year
  // If months are different
  if (a.month != b.month)
    return a.month < b.month; // Return true if a's month is less than b's month
  return a.day < b.day;       // Return true if a's day is less than b's day
}

// Insertion sort by Customer Name (ascending alphabetical)
void sortByName() {
  long long comparisons = 0;
  clock_t time1 = clock();

  int low = 0;
  int high = (int)tickets.size() - 1;
  for (int unsorted = low + 1; unsorted <= high; unsorted++) {
    Ticket value = tickets[unsorted];
    int posn = unsorted;
    while ((posn > low) &&
           (tickets[posn - 1].getCustomerName() > value.getCustomerName())) {
      ++comparisons;
      tickets[posn] = tickets[posn - 1];
      posn--;
    }
    tickets[posn] = value;
  }

  clock_t time2 = clock();
  double duration = (double)(time2 - time1) / CLOCKS_PER_SEC * 1000000;
  std::cout << "Sorted by Customer Name (ascending)." << std::endl;
  std::cout << "Comparisons: " << comparisons << std::endl;
  std::cout << "Time: " << duration << " microseconds" << std::endl;
}

// Insertion sort by Priority Level (highest first: Urgent > High > Medium >
// Low) Algorithm adapted from John Gauch's seven sorting algorithms program
void sortByLevel() {
  long long comparisons = 0;
  clock_t time1 = clock();

  int low = 0;
  int high = (int)tickets.size() - 1;
  for (int unsorted = low + 1; unsorted <= high; unsorted++) {
    Ticket value = tickets[unsorted];
    int valueLevel = levelToInt(value.getLevel());
    int posn = unsorted;
    while ((posn > low) &&
           (levelToInt(tickets[posn - 1].getLevel()) < valueLevel)) {
      ++comparisons;
      tickets[posn] = tickets[posn - 1];
      posn--;
    }
    tickets[posn] = value;
  }

  clock_t time2 = clock();
  double duration = (double)(time2 - time1) / CLOCKS_PER_SEC * 1000000;
  std::cout << "Sorted by Priority Level (highest first)." << std::endl;
  std::cout << "Comparisons: " << comparisons << std::endl;
  std::cout << "Time: " << duration << " microseconds" << std::endl;
}

// Merge sort by Date Submitted (ascending, oldest first)
// Algorithm adapted from John Gauch's seven sorting algorithms program
void mergeSortByDate(int low, int high, long long &cmp) {
  int range = high - low + 1;
  if (range > 1) {
    // Use insertion sort for small sub-arrays (hybrid optimization)
    if (range <= 20) {
      for (int unsorted = low + 1; unsorted <= high; unsorted++) {
        Ticket value = tickets[unsorted];
        int posn = unsorted;
        while ((posn > low) &&
               dateIsLess(value.getDateSubmitted(),
                          tickets[posn - 1].getDateSubmitted())) {
          ++cmp;
          tickets[posn] = tickets[posn - 1];
          posn--;
        }
        tickets[posn] = value;
      }
      return;
    }

    // Divide the array and sort both halves
    int mid = (low + high) / 2;
    mergeSortByDate(low, mid, cmp);
    mergeSortByDate(mid + 1, high, cmp);

    // Create temporary array for merged data
    std::vector<Ticket> copy(range);

    // Initialize array indices
    int index1 = low;
    int index2 = mid + 1;
    int index = 0;

    // Merge smallest data elements into copy array
    while (index1 <= mid && index2 <= high) {
      ++cmp;
      if (!dateIsLess(tickets[index2].getDateSubmitted(),
                      tickets[index1].getDateSubmitted()))
        copy[index++] = tickets[index1++];
      else
        copy[index++] = tickets[index2++];
    }

    // Copy any remaining entries from the first half
    while (index1 <= mid)
      copy[index++] = tickets[index1++];

    // Copy any remaining entries from the second half
    while (index2 <= high)
      copy[index++] = tickets[index2++];

    // Copy data back from the temporary array
    for (index = 0; index < range; index++)
      tickets[low + index] = copy[index];
  }
}

void sortByDate() {
  long long comparisons = 0;
  clock_t time1 = clock();

  mergeSortByDate(0, (int)tickets.size() - 1, comparisons);

  clock_t time2 = clock();
  double duration = (double)(time2 - time1) / CLOCKS_PER_SEC * 1000000;
  std::cout << "Sorted by Date Submitted (oldest first)." << std::endl;
  std::cout << "Comparisons: " << comparisons << std::endl;
  std::cout << "Time: " << duration << " microseconds" << std::endl;
}

// Merge sort by Resolution Time (descending, longest first)
// Algorithm adapted from John Gauch's seven sorting algorithms program
void mergeSortByResTime(int low, int high, long long &cmp) {
  int range = high - low + 1;
  if (range > 1) {
    // Use insertion sort for small sub-arrays (hybrid optimization)
    if (range <= 20) {
      for (int unsorted = low + 1; unsorted <= high; unsorted++) {
        Ticket value = tickets[unsorted];
        int posn = unsorted;
        while ((posn > low) &&
               (tickets[posn - 1].getResTime() < value.getResTime())) {
          ++cmp;
          tickets[posn] = tickets[posn - 1];
          posn--;
        }
        tickets[posn] = value;
      }
      return;
    }

    // Divide the array and sort both halves
    int mid = (low + high) / 2;
    mergeSortByResTime(low, mid, cmp);
    mergeSortByResTime(mid + 1, high, cmp);

    // Create temporary array for merged data
    std::vector<Ticket> copy(range);

    // Initialize array indices
    int index1 = low;
    int index2 = mid + 1;
    int index = 0;

    // Merge largest data elements into copy array (descending)
    while (index1 <= mid && index2 <= high) {
      ++cmp;
      if (tickets[index1].getResTime() >= tickets[index2].getResTime())
        copy[index++] = tickets[index1++];
      else
        copy[index++] = tickets[index2++];
    }

    // Copy any remaining entries from the first half
    while (index1 <= mid)
      copy[index++] = tickets[index1++];

    // Copy any remaining entries from the second half
    while (index2 <= high)
      copy[index++] = tickets[index2++];

    // Copy data back from the temporary array
    for (index = 0; index < range; index++)
      tickets[low + index] = copy[index];
  }
}

void sortByResTime() {
  long long comparisons = 0;
  clock_t time1 = clock();

  mergeSortByResTime(0, (int)tickets.size() - 1, comparisons);

  clock_t time2 = clock();
  double duration = (double)(time2 - time1) / CLOCKS_PER_SEC * 1000000;
  std::cout << "Sorted by Resolution Time (longest first)." << std::endl;
  std::cout << "Comparisons: " << comparisons << std::endl;
  std::cout << "Time: " << duration << " microseconds" << std::endl;
}

// Task 5 - User Interaction

int main() {
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
      loadTickets(file);
      break;
    }
    case 2:
      printTickets();
      break;
    case 3:
      addTicket();
      break;
    case 4: {
      int ticketId;
      std::cout << "Enter ticket ID to edit: ";
      std::cin >> ticketId;
      editTicket(ticketId);
      break;
    }
    case 5: {
      int ticketId;
      std::cout << "Enter ticket ID to delete: ";
      std::cin >> ticketId;
      deleteTicket(ticketId);
      break;
    }
    case 6:
      sortByName();
      break;
    case 7:
      sortByLevel();
      break;
    case 8:
      sortByDate();
      break;
    case 9:
      sortByResTime();
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