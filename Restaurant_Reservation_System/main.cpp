#include <iostream>
#include "Restaurant.hpp"

using namespace std;
int main() {
  // Initialize Restaurant with 2 tables
  Restaurant restaurant(2);
  // Create customers and make reservations
  std::shared_ptr<Customer> customer1 = make_shared<Customer>("Morgan");
  std::shared_ptr<Customer> customer2 = make_shared<Customer>("Lottie");
  std::shared_ptr<Customer> customer3 = make_shared<Customer>("Nathan");
  std::shared_ptr<Customer> customer4 = make_shared<Customer>("Dai");

    bool r1 = restaurant.reserveTable(customer1);
    cout << "Reserving table for " << (*customer1).getName()
              << ": " << (r1 ? "Success!" : "Added to waitlist!") << endl;

    bool r2 = restaurant.reserveTable(customer2);
    cout << "Reserving table for " << (*customer2).getName()
              << ": " << (r2 ? "Success!" : "Added to waitlist!") << endl;

    bool r3 = restaurant.reserveTable(customer3);
    cout << "Reserving table for " << (*customer3).getName()
              << ": " << (r3 ? "Success!" : "Added to waitlist!") << endl;

    bool r4 = restaurant.reserveTable(customer4);
    cout << "Reserving table for " << (*customer4).getName()
              << ": " << (r4 ? "Success!" : "Added to waitlist!") << endl;
  // Release a table and demonstrate waitlist notification
  restaurant.releaseTable(1);

  restaurant.printWaitlist();

  return 0;
}
