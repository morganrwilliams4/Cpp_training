#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include "Table.hpp"

class Customer {
private:
  std::string name;

public:
  Customer(const std::string& n);
  std::string getName() const;
};

#endif
