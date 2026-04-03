#include "ticket.h"
#include <iostream>
class TMS {
public:
  void loadTickets(std::fstream &file) {};
  void printTickets() {};
  void addTicket() {};
  void editTicket(int ticketId) {};
  void deleteTicket(int ticketId) {};

private:
  std::vector<Ticket> tickets;
};