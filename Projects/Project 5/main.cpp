#include "ticket.h"
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Task 2 - Support Ticket Operations
std::vector<Ticket> tickets;

void loadTickets(std::fstream &file);
void printTickets();
void addTicket();
void editTicket(int ticketId);
void deleteTicket(int ticketId);
// Task 3 - Sorting Functionalities
void sortByName();    // insertion sort, ascending alphabetical
void sortByLevel();   // insertion sort, highest priority first
void sortByDate();    // merge sort, oldest first
void sortByResTime(); // merge sort, longest time first
int levelToInt(const std::string &level);
bool dateIsLess(const Ticket::date &a, const Ticket::date &b);
void mergeSortByDate(int low, int high, long long &cmp);
void mergeSortByResTime(int low, int high, long long &cmp);

// Task 2 - Support Ticket Operations

void loadTickets(std::fstream &file) {
  if (!file.is_open()) {
    std::cerr << "Error opening file." << std::endl;
    return;
  }
  // Skip the header line
  std::string header;
  std::getline(file, header);

  tickets.clear();
  std::string line;
  while (std::getline(file, line)) {
    if (line.empty()) continue;
    // id,customerName,level,month,day,year,resTime
    std::istringstream ss(line);
    int id, month, day, year, resTime;
    std::string customerName, level;
    char comma;

    ss >> id >> comma;
    std::getline(ss, customerName, ',');
    std::getline(ss, level, ',');
    ss >> month >> comma >> day >> comma >> year >> comma >> resTime;

    tickets.emplace_back(id, customerName, level, month, day, year, resTime);
  }
  file.close();
  std::cout << "Loaded " << tickets.size() << " tickets." << std::endl;
}

void printTickets() {
  if (tickets.empty()) {
    std::cout << "No tickets to display." << std::endl;
    return;
  }
  std::cout << std::left << std::setw(8) << "ID" << std::setw(25)
            << "Customer Name" << std::setw(10) << "Level" << std::setw(16)
            << "Date Submitted" << "Resolution Time (days)" << std::endl;
  std::cout << std::string(83, '-') << std::endl;
  for (auto &t : tickets) {
    auto d = t.getDateSubmitted();
    std::string dateStr = std::to_string(d.month) + "/" +
                          std::to_string(d.day) + "/" + std::to_string(d.year);
    std::cout << std::left << std::setw(8) << t.getId() << std::setw(25)
              << t.getCustomerName() << std::setw(10) << t.getLevel()
              << std::setw(16) << dateStr << t.getResTime() << std::endl;
  }
  std::cout << "Total: " << tickets.size() << " tickets." << std::endl;
}

void addTicket() {
  // Generate new ID as max existing ID + 1
  int maxId = 10000;
  for (auto &t : tickets) {
    if (t.getId() > maxId) maxId = t.getId();
  }
  int id = maxId + 1;

  std::string customerName, level;
  int month, day, year, resTime;

  std::cin.ignore();
  std::cout << "Enter customer name: ";
  std::getline(std::cin, customerName);

  std::cout << "Enter level (Low/Medium/High/Urgent): ";
  std::cin >> level;

  std::cout << "Enter date submitted (month day year): ";
  std::cin >> month >> day >> year;

  std::cout << "Enter estimated resolution time (days): ";
  std::cin >> resTime;

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
  for (auto it = tickets.begin(); it != tickets.end(); ++it) {
    if (it->getId() == ticketId) {
      tickets.erase(it);
      std::cout << "Ticket " << ticketId << " deleted successfully."
                << std::endl;
      return;
    }
  }
  std::cout << "Ticket with ID " << ticketId << " not found." << std::endl;
}

// Task 3 & 4 - Sorting with timing and comparison counting

int levelToInt(const std::string &level) {
  if (level == "Urgent") return 3;
  if (level == "High") return 2;
  if (level == "Medium") return 1;
  return 0; // Low
}

bool dateIsLess(const Ticket::date &a, const Ticket::date &b) {
  if (a.year != b.year) return a.year < b.year;
  if (a.month != b.month) return a.month < b.month;
  return a.day < b.day;
}

// Insertion sort by Customer Name (ascending alphabetical)
// Algorithm adapted from John Gauch's seven sorting algorithms program
void sortByName() {
  long long comparisons = 0;
  auto start = std::chrono::high_resolution_clock::now();

  int low = 0;
  int high = (int)tickets.size() - 1;
  for (int unsorted = low + 1; unsorted <= high; unsorted++) {
    Ticket value = tickets[unsorted];
    int posn = unsorted;
    while ((posn > low) && (tickets[posn - 1].getCustomerName() > value.getCustomerName())) {
      ++comparisons;
      tickets[posn] = tickets[posn - 1];
      posn--;
    }
    tickets[posn] = value;
  }

  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Sorted by Customer Name (ascending)." << std::endl;
  std::cout << "Comparisons: " << comparisons << std::endl;
  std::cout << "Time: " << duration.count() << " microseconds" << std::endl;
}

// Insertion sort by Priority Level (highest first: Urgent > High > Medium > Low)
// Algorithm adapted from John Gauch's seven sorting algorithms program
void sortByLevel() {
  long long comparisons = 0;
  auto start = std::chrono::high_resolution_clock::now();

  int low = 0;
  int high = (int)tickets.size() - 1;
  for (int unsorted = low + 1; unsorted <= high; unsorted++) {
    Ticket value = tickets[unsorted];
    int valueLevel = levelToInt(value.getLevel());
    int posn = unsorted;
    while ((posn > low) && (levelToInt(tickets[posn - 1].getLevel()) < valueLevel)) {
      ++comparisons;
      tickets[posn] = tickets[posn - 1];
      posn--;
    }
    tickets[posn] = value;
  }

  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Sorted by Priority Level (highest first)." << std::endl;
  std::cout << "Comparisons: " << comparisons << std::endl;
  std::cout << "Time: " << duration.count() << " microseconds" << std::endl;
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
        while ((posn > low) && dateIsLess(value.getDateSubmitted(),
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
  auto start = std::chrono::high_resolution_clock::now();

  mergeSortByDate(0, (int)tickets.size() - 1, comparisons);

  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Sorted by Date Submitted (oldest first)." << std::endl;
  std::cout << "Comparisons: " << comparisons << std::endl;
  std::cout << "Time: " << duration.count() << " microseconds" << std::endl;
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
        while ((posn > low) && (tickets[posn - 1].getResTime() < value.getResTime())) {
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
  auto start = std::chrono::high_resolution_clock::now();

  mergeSortByResTime(0, (int)tickets.size() - 1, comparisons);

  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Sorted by Resolution Time (longest first)." << std::endl;
  std::cout << "Comparisons: " << comparisons << std::endl;
  std::cout << "Time: " << duration.count() << " microseconds" << std::endl;
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