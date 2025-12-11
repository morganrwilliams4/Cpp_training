#include <vector>
#include <string>
#include <algorithm>
#include <memory>
#include <iostream>
#include "Customer.hpp"

using namespace std;

void removeElement(std::vector<std::weak_ptr<Customer>>& vec, const std::weak_ptr<Customer>& ptr) {
    vec.erase(std::remove_if(vec.begin(), vec.end(),
        [&ptr](const std::weak_ptr<Customer>& element) {
            return !element.owner_before(ptr) && !ptr.owner_before(element);
        }),
        vec.end());
}
