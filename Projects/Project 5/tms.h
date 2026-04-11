#pragma once
#include "ticket.h"
#include <fstream>
#include <iostream>
#include <vector>

class TMS {
public:
  // Task 2 - Support Ticket Operations
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

private:
  std::vector<Ticket> tickets;
  int levelToInt(const std::string &level);
  bool dateIsLess(const Ticket::date &a, const Ticket::date &b);
  void mergeSortByDate(int low, int high, long long &cmp);
  void mergeSortByResTime(int low, int high, long long &cmp);
};