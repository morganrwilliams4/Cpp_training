#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <vector>
#include <memory>
#include "Table.hpp"
#include "Customer.hpp"


class Restaurant {
private:
  void notifyWaitlist();
  
public:
  Restaurant(int initialTableCount);
  std::vector<std::unique_ptr<Table>> tables;
  std::vector<std::shared_ptr<Customer>> activeCustomers;
  std::vector<std::weak_ptr<Customer>> waitlist;
  
  bool reserveTable(std::shared_ptr<Customer>& pointer);

  void printWaitlist();

  void releaseTable(int tableNumber);
};



#endif
