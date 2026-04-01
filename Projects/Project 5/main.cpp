#include <iostream>

// Support ticket
class Ticket {
public:
  /* Getters */
  int getId() {
    return id;
  }
  std::string getDescription() {
    return description;
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
  void setDescription(std::string newDescription) {
    description = newDescription;
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
  // Editors
  void editTicketId(int newId) {
    setId(newId);
  }
  void editTicketDescription(std::string newDescription) {
    setDescription(newDescription);
  }
  void editTicketLevel(std::string newLevel) {
    setLevel(newLevel);
  }
  void editTicketDateSubmitted(int m, int d, int y) {
    setDateSubmitted(m, d, y);
  }
  void editTicketResTime(int newResTime) {
    setResTime(newResTime);
  }

private:
  int id;
  std::string description;
  std::string level;
  struct date {
    int month;
    int day;
    int year;
  } dateSubmitted;
  int resTime;
};

int main() {
  Ticket t;
  t.setId(123);
  t.setDescription("Computer won't turn on.");
  t.setLevel("High");
  t.setDateSubmitted(10, 5, 2023);
  t.setResTime(4);

  std::cout << "Ticket ID: " << t.getId() << std::endl;
  std::cout << "Description: " << t.getDescription() << std::endl;
  std::cout << "Level: " << t.getLevel() << std::endl;
  auto date = t.getDateSubmitted();
  std::cout << "Date Submitted: " << date.month << "/" << date.day << "/"
            << date.year << std::endl;
  std::cout << "Resolution Time: " << t.getResTime() << " days" << std::endl;

  return 0;
}