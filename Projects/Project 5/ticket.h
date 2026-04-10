#pragma once
#include <iostream>
#include <string>

// Task 1 - Support Ticket Data Structure
class Ticket {
public:
  struct date {
    int month;
    int day;
    int year;
  };
  Ticket();
  Ticket(int id, const std::string &customerName, const std::string &level,
         int m, int d, int y, int resTime);
  ~Ticket();
  /* Getters */
  int getId();
  std::string getCustomerName();
  std::string getLevel();
  Ticket::date getDateSubmitted();
  int getResTime();
  /* Setters */
  void setId(int newId);
  void setCustomerName(std::string newCustomerName);
  void setLevel(std::string newLevel);
  void setDateSubmitted(int m, int d, int y);
  void setResTime(int newResTime); // Days
  void print();

private:
  int id;
  std::string customerName;
  std::string level;
  Ticket::date dateSubmitted;
  int resTime;
};
