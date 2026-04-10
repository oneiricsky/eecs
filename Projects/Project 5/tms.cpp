#include "tms.h"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>

// Task 2 - Support Ticket Operations

void TMS::loadTickets(std::fstream &file) {
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

void TMS::printTickets() {
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

void TMS::addTicket() {
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

void TMS::editTicket(int ticketId) {
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

void TMS::deleteTicket(int ticketId) {
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

int TMS::levelToInt(const std::string &level) {
  if (level == "Urgent") return 3;
  if (level == "High") return 2;
  if (level == "Medium") return 1;
  return 0; // Low
}

bool TMS::dateIsLess(const Ticket::date &a, const Ticket::date &b) {
  if (a.year != b.year) return a.year < b.year;
  if (a.month != b.month) return a.month < b.month;
  return a.day < b.day;
}

// Insertion sort by Customer Name (ascending alphabetical)
void TMS::sortByName() {
  long long comparisons = 0;
  auto start = std::chrono::high_resolution_clock::now();

  for (int i = 1; i < (int)tickets.size(); ++i) {
    Ticket key = tickets[i];
    int j = i - 1;
    while (j >= 0) {
      ++comparisons;
      if (tickets[j].getCustomerName() > key.getCustomerName()) {
        tickets[j + 1] = tickets[j];
        --j;
      } else {
        break;
      }
    }
    tickets[j + 1] = key;
  }

  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Sorted by Customer Name (ascending)." << std::endl;
  std::cout << "Comparisons: " << comparisons << std::endl;
  std::cout << "Time: " << duration.count() << " microseconds" << std::endl;
}

// Insertion sort by Priority Level (highest first: Critical > High > Medium > Low)
void TMS::sortByLevel() {
  long long comparisons = 0;
  auto start = std::chrono::high_resolution_clock::now();

  for (int i = 1; i < (int)tickets.size(); ++i) {
    Ticket key = tickets[i];
    int keyLevel = levelToInt(key.getLevel());
    int j = i - 1;
    while (j >= 0) {
      ++comparisons;
      if (levelToInt(tickets[j].getLevel()) < keyLevel) {
        tickets[j + 1] = tickets[j];
        --j;
      } else {
        break;
      }
    }
    tickets[j + 1] = key;
  }

  auto end = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  std::cout << "Sorted by Priority Level (highest first)." << std::endl;
  std::cout << "Comparisons: " << comparisons << std::endl;
  std::cout << "Time: " << duration.count() << " microseconds" << std::endl;
}

// Merge sort by Date Submitted (ascending, oldest first)
void TMS::mergeByDate(int left, int mid, int right, long long &cmp) {
  std::vector<Ticket> leftArr(tickets.begin() + left,
                              tickets.begin() + mid + 1);
  std::vector<Ticket> rightArr(tickets.begin() + mid + 1,
                               tickets.begin() + right + 1);
  int i = 0, j = 0, k = left;
  while (i < (int)leftArr.size() && j < (int)rightArr.size()) {
    ++cmp;
    if (!dateIsLess(rightArr[j].getDateSubmitted(),
                    leftArr[i].getDateSubmitted())) {
      tickets[k++] = leftArr[i++];
    } else {
      tickets[k++] = rightArr[j++];
    }
  }
  while (i < (int)leftArr.size()) tickets[k++] = leftArr[i++];
  while (j < (int)rightArr.size()) tickets[k++] = rightArr[j++];
}

void TMS::mergeSortByDate(int left, int right, long long &cmp) {
  if (left < right) {
    int mid = left + (right - left) / 2;
    mergeSortByDate(left, mid, cmp);
    mergeSortByDate(mid + 1, right, cmp);
    mergeByDate(left, mid, right, cmp);
  }
}

void TMS::sortByDate() {
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
void TMS::mergeByResTime(int left, int mid, int right, long long &cmp) {
  std::vector<Ticket> leftArr(tickets.begin() + left,
                              tickets.begin() + mid + 1);
  std::vector<Ticket> rightArr(tickets.begin() + mid + 1,
                               tickets.begin() + right + 1);
  int i = 0, j = 0, k = left;
  while (i < (int)leftArr.size() && j < (int)rightArr.size()) {
    ++cmp;
    if (leftArr[i].getResTime() >= rightArr[j].getResTime()) {
      tickets[k++] = leftArr[i++];
    } else {
      tickets[k++] = rightArr[j++];
    }
  }
  while (i < (int)leftArr.size()) tickets[k++] = leftArr[i++];
  while (j < (int)rightArr.size()) tickets[k++] = rightArr[j++];
}

void TMS::mergeSortByResTime(int left, int right, long long &cmp) {
  if (left < right) {
    int mid = left + (right - left) / 2;
    mergeSortByResTime(left, mid, cmp);
    mergeSortByResTime(mid + 1, right, cmp);
    mergeByResTime(left, mid, right, cmp);
  }
}

void TMS::sortByResTime() {
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