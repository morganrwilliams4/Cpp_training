#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

void removeElement(vector<string>& vec, string s) {
    auto it = find(vec.begin(), vec.end(), s);
    if (it != vec.end()) {
      vec.erase(it);
    }
}
