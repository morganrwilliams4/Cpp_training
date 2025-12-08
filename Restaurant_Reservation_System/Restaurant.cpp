#include "Restaurant.hpp"
#include "Customer.hpp"
#include "removeElement.hpp"
#include "Table.hpp"

#include <iostream>

using namespace std;

Restaurant::Restaurant(int initialTableCount) {
  for(int i = 1; i <= initialTableCount; i++) {
    tables.push_back(std::make_unique<Table>(i));
  }
}

bool Restaurant::reserveTable(std::shared_ptr<Customer>& pointer) {
  for (std::unique_ptr<Table>& table : tables) {
    if ((*table).getIsAvailable()) {
      (*table).reserve();
      activeCustomers.push_back(pointer);

      cout << "Reserved table " << (*table).getNumber() << " for " << (*pointer).getName() << " ." << endl;

      return true;
    }
  }
  waitlist.push_back(pointer);

  cout << "No tables free. Added " << (*pointer).getName() << " to the waitlist." << endl;

  return false;
}

void Restaurant::printWaitlist() {
  cout << "The following people are waiting for a table: " << endl;

  for (auto customer : waitlist) {
    shared_ptr<Customer> customerPtr;
    customerPtr = customer.lock();
    if (customerPtr) {  // check if still valid
      cout << (*customerPtr).getName() << endl;
    }
  }
}

void Restaurant::releaseTable(int tableNumber) {
  for (std::unique_ptr<Table>& table : tables) {
    if((*table).getNumber() == tableNumber) {
      if(!(*table).getIsAvailable()) {
        (*table).release();

        cout << "Released table " << tableNumber << "." << endl;

        notifyWaitlist();
      } else {
          cout << "Table " << tableNumber << " was already free." << endl;
      }
    }
  }
}

void Restaurant::notifyWaitlist() {
  if(waitlist.empty()) {
    return;
  } 
  
  std::shared_ptr<Customer> customer = waitlist[0].lock();
  if (customer) {
    reserveTable(customer);
    removeElement(waitlist, waitlist[0]);
  }
}










