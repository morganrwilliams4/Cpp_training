#include "Customer.hpp"

using namespace std;

Customer::Customer(const string& n) : name(n) {}
string Customer::getName() const { 
  return name; 
}
