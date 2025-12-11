#include "Table.hpp"

Table::Table(int num) : number(num), isAvailable(true) {}

void Table::reserve() { 
  isAvailable = false; 
}
void Table::release() { 
  isAvailable = true; 
}
bool Table::getIsAvailable() const { 
  return isAvailable; 
}
int Table::getNumber() const { 
  return number; 
}
