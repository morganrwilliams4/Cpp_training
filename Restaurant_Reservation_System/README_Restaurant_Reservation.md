# Restaurant Reservation System

**Language:** C++11  
**Type:** Intermediate C++ Project  
**Concepts:** Smart Pointers, Memory Management, OOP, STL Containers, Resource Management

## Project Overview

A restaurant reservation system demonstrating modern C++ memory management through smart pointers. The system manages tables, customers, and a waitlist with automatic resource cleanup, eliminating manual memory management and preventing memory leaks.

## Features

### Core Functionality
- **Table Management:** Create and manage multiple restaurant tables
- **Reservations:** Assign customers to available tables
- **Waitlist:** Queue customers when all tables are occupied
- **Automatic Notification:** Move waitlist customers to tables when they become available
- **Table Release:** Free tables and trigger waitlist processing
- **Memory Safety:** No manual `new`/`delete` - all memory handled by smart pointers

### Technical Highlights
- **Unique Ownership:** Tables owned exclusively by Restaurant (`unique_ptr`)
- **Shared Ownership:** Customers shared between activeCustomers and waitlist (`shared_ptr`)
- **Weak References:** Waitlist holds non-owning references to prevent circular dependencies (`weak_ptr`)
- **Automatic Cleanup:** Resources automatically freed when no longer needed
- **RAII Principle:** Resource Acquisition Is Initialization throughout

## Architecture

### File Structure

```
Restaurant_Reservation_System/
├── README.md              # This file
├── Restaurant.hpp         # Restaurant class declaration
├── Restaurant.cpp         # Restaurant class implementation
├── Table.hpp              # Table class declaration
├── Table.cpp              # Table class implementation
├── Customer.hpp           # Customer class declaration
├── Customer.cpp           # Customer class implementation
├── removeElement.hpp      # Helper for removing weak_ptr from vector
└── main.cpp               # Driver program demonstrating the system
```

### Class Design

#### `Restaurant` Class
**Purpose:** Manages tables, active customers, and waitlist

**Data Members:**
```cpp
std::vector<std::unique_ptr<Table>> tables;           // Exclusive table ownership
std::vector<std::shared_ptr<Customer>> activeCustomers; // Customers with tables
std::vector<std::weak_ptr<Customer>> waitlist;        // Non-owning waitlist references
```

**Public Methods:**
```cpp
Restaurant(int initialTableCount);              // Constructor
bool reserveTable(std::shared_ptr<Customer>&);  // Reserve table or add to waitlist
void printWaitlist();                           // Display waiting customers
void releaseTable(int tableNumber);             // Free table and notify waitlist
```

**Private Methods:**
```cpp
void notifyWaitlist();  // Process waitlist when table becomes available
```

#### `Table` Class
**Purpose:** Represents a restaurant table with availability status

**Data Members:**
```cpp
int number;          // Table identifier
bool isAvailable;    // Availability status
```

**Public Methods:**
```cpp
Table(int num);                  // Constructor
void reserve();                  // Mark as occupied
void release();                  // Mark as available
bool getIsAvailable() const;     // Check availability
int getNumber() const;           // Get table number
```

#### `Customer` Class
**Purpose:** Represents a customer with a name

**Data Members:**
```cpp
std::string name;  // Customer name
```

**Public Methods:**
```cpp
Customer(const std::string& n);  // Constructor
std::string getName() const;     // Get customer name
```

## Key C++ Concepts Demonstrated

### 1. Smart Pointers - Modern Memory Management

#### `unique_ptr<Table>` - Exclusive Ownership
```cpp
std::vector<std::unique_ptr<Table>> tables;
```

**Why unique_ptr?**
- Restaurant has **exclusive ownership** of tables
- Tables cannot be shared or copied
- Automatic cleanup when Restaurant is destroyed
- Prevents memory leaks and double-deletion

**Creation:**
```cpp
tables.push_back(std::make_unique<Table>(i));
```

#### `shared_ptr<Customer>` - Shared Ownership
```cpp
std::vector<std::shared_ptr<Customer>> activeCustomers;
std::shared_ptr<Customer> customer1 = make_shared<Customer>("Morgan");
```

**Why shared_ptr?**
- Customers can be in **multiple locations** (active list, waitlist, main)
- Reference counting tracks all owners
- Deleted only when last reference goes out of scope
- Safe sharing across containers

#### `weak_ptr<Customer>` - Non-Owning Reference
```cpp
std::vector<std::weak_ptr<Customer>> waitlist;
```

**Why weak_ptr?**
- Waitlist doesn't "own" customers
- Prevents circular references and memory leaks
- Allows checking if customer still exists
- Main or activeCustomers owns; waitlist just observes

**Usage Pattern:**
```cpp
std::shared_ptr<Customer> customerPtr = customer.lock();
if (customerPtr) {  // Check if still valid
    // Use customerPtr safely
}
```

### 2. RAII (Resource Acquisition Is Initialization)

**Principle:** Resources (memory, files, locks) tied to object lifetime

**In This Project:**
- Tables created in Restaurant constructor
- Automatically freed when Restaurant destroyed
- No manual cleanup needed
- Exception-safe resource management

### 3. Container of Smart Pointers

**Pattern:**
```cpp
std::vector<std::unique_ptr<Table>> tables;  // Container of owning pointers
```

**Benefits:**
- Dynamic number of tables
- Efficient memory management
- Clean iteration and access
- No array size limitations

### 4. Dereference with Smart Pointers

**Syntax:**
```cpp
(*table).getNumber()      // Dereference and call method
(*pointer).getName()      // Access through dereferenced pointer
table->getNumber()        // Alternative arrow syntax
```

### 5. Lambda Expressions (Advanced)

**In removeElement.hpp:**
```cpp
[&ptr](const std::weak_ptr<Customer>& element) {
    return !element.owner_before(ptr) && !ptr.owner_before(element);
}
```

**Purpose:** Compare `weak_ptr` for equality in `remove_if` algorithm

### 6. Move Semantics (Implicit)

**In push_back:**
```cpp
tables.push_back(std::make_unique<Table>(i));
```

`unique_ptr` cannot be copied (disabled copy constructor), so it's **moved** into the vector.

## System Workflow

### Scenario 1: Successful Reservation
```
1. Customer created with shared_ptr
2. reserveTable() called
3. Available table found
4. Table marked as reserved
5. Customer added to activeCustomers
6. Success message printed
```

### Scenario 2: Waitlist Addition
```
1. Customer created with shared_ptr
2. reserveTable() called
3. No tables available
4. Customer added to waitlist (weak_ptr)
5. Waitlist message printed
```

### Scenario 3: Table Release & Waitlist Processing
```
1. releaseTable() called with table number
2. Table marked as available
3. notifyWaitlist() automatically called
4. First waitlist customer retrieved via lock()
5. If valid, reserveTable() called
6. Customer removed from waitlist
```

## Usage Example

```cpp
#include "Restaurant.hpp"
#include <memory>

int main() {
    // Create restaurant with 2 tables
    Restaurant restaurant(2);
    
    // Create customers using shared_ptr
    auto customer1 = std::make_shared<Customer>("Alice");
    auto customer2 = std::make_shared<Customer>("Bob");
    auto customer3 = std::make_shared<Customer>("Charlie");
    
    // Make reservations
    restaurant.reserveTable(customer1);  // Success - Table 1
    restaurant.reserveTable(customer2);  // Success - Table 2
    restaurant.reserveTable(customer3);  // Waitlisted
    
    // Release a table (Charlie automatically gets it)
    restaurant.releaseTable(1);
    
    // Print remaining waitlist
    restaurant.printWaitlist();
    
    return 0;
}
// All memory automatically cleaned up here
```

## Expected Output

```
Reserved table 1 for Morgan .
Reserving table for Morgan: Success!
Reserved table 2 for Lottie .
Reserving table for Lottie: Success!
No tables free. Added Nathan to the waitlist.
Reserving table for Nathan: Added to waitlist!
No tables free. Added Dai to the waitlist.
Reserving table for Dai: Added to waitlist!
Released table 1.
Reserved table 1 for Nathan .
The following people are waiting for a table: 
Dai
```

## Compilation and Execution

### Using g++
```bash
# Compile all source files
g++ -std=c++14 -o restaurant main.cpp Restaurant.cpp Table.cpp Customer.cpp

# Run the program
./restaurant
```

### Using clang++
```bash
clang++ -std=c++14 -o restaurant main.cpp Restaurant.cpp Table.cpp Customer.cpp
./restaurant
```

### Using MSVC (Windows)
```bash
cl /EHsc /std:c++14 main.cpp Restaurant.cpp Table.cpp Customer.cpp
restaurant.exe
```

**Note:** Requires C++14 or later for `std::make_unique`

## Design Decisions

### Why unique_ptr for Tables?
- **Exclusive ownership:** Only Restaurant owns tables
- **Cannot be shared:** Tables belong to one restaurant
- **Efficient:** No reference counting overhead
- **Clear semantics:** Ownership is obvious

### Why shared_ptr for Customers?
- **Multiple locations:** Customers in activeCustomers and possibly waitlist
- **Shared lifetime:** Managed by reference counting
- **Safe deletion:** Deleted only when all references gone
- **Flexibility:** Can be passed around safely

### Why weak_ptr for Waitlist?
- **Non-owning:** Waitlist doesn't extend customer lifetime
- **Prevents leaks:** Avoids circular references
- **Validation:** Can check if customer still exists before use
- **Correct semantics:** Waitlist observes, doesn't own

### Why Private notifyWaitlist()?
- **Encapsulation:** Internal implementation detail
- **Automatic:** Called by releaseTable(), not by users
- **Consistency:** Ensures waitlist always processed correctly
- **Single responsibility:** One place to manage waitlist logic

## Memory Safety Benefits

### Traditional C++ (Manual Memory)
```cpp
// OLD WAY - Error-prone!
Customer* customer = new Customer("Alice");
// ... use customer ...
delete customer;  // Easy to forget or double-delete
```

**Problems:**
- Memory leaks if delete forgotten
- Double-deletion if called twice
- Dangling pointers if deleted too early
- Exception-unsafe

### Modern C++ (Smart Pointers)
```cpp
// NEW WAY - Safe and automatic!
auto customer = std::make_shared<Customer>("Alice");
// ... use customer ...
// Automatically deleted when last reference goes away
```

**Benefits:**
- ✅ No memory leaks
- ✅ No double-deletion
- ✅ No dangling pointers
- ✅ Exception-safe
- ✅ Clear ownership semantics

## Advanced Concepts

### Reference Counting (shared_ptr)
```cpp
{
    auto customer = make_shared<Customer>("Alice");  // ref_count = 1
    activeCustomers.push_back(customer);             // ref_count = 2
    waitlist.push_back(customer);                    // ref_count = 2 (weak_ptr doesn't count!)
}  // customer goes out of scope, ref_count = 1 (still in activeCustomers)
// Customer deleted only when activeCustomers cleared
```

### weak_ptr Validation
```cpp
void processWaitlist() {
    for (auto weakCustomer : waitlist) {
        shared_ptr<Customer> customer = weakCustomer.lock();
        if (customer) {
            // Customer still exists - safe to use
            reserveTable(customer);
        } else {
            // Customer was deleted - skip safely
        }
    }
}
```

### Move-Only Types (unique_ptr)
```cpp
unique_ptr<Table> table1 = make_unique<Table>(1);
unique_ptr<Table> table2 = table1;  // ERROR: Cannot copy
unique_ptr<Table> table2 = std::move(table1);  // OK: Moved ownership
// table1 is now nullptr, table2 owns the Table
```

## Helper Function: removeElement (weak_ptr version)

### Purpose
Remove a `weak_ptr` from a vector by comparing underlying ownership.

### Implementation
```cpp
void removeElement(std::vector<std::weak_ptr<Customer>>& vec, 
                  const std::weak_ptr<Customer>& ptr) {
    vec.erase(std::remove_if(vec.begin(), vec.end(),
        [&ptr](const std::weak_ptr<Customer>& element) {
            return !element.owner_before(ptr) && !ptr.owner_before(element);
        }),
        vec.end());
}
```

### Why This Approach?
- `weak_ptr` doesn't have `operator==`
- Must use `owner_before()` to compare underlying ownership
- Lambda captures `ptr` by reference for comparison
- `remove_if` + `erase` idiom for efficient removal

## Potential Enhancements

### Functional Improvements
- **Reservation IDs:** Unique identifiers for each reservation
- **Time limits:** Auto-release tables after time limit
- **Party size:** Match table capacity to party size
- **Cancellations:** Allow customers to cancel reservations
- **Priority waitlist:** VIP or special ordering
- **Table preferences:** Request specific tables

### Technical Improvements
- **Exception handling:** Try-catch for error conditions
- **Custom deleters:** Special cleanup for resources
- **make_unique_for_overwrite:** For performance-critical code
- **enable_shared_from_this:** Allow objects to create shared_ptr to themselves
- **Thread safety:** Mutex for concurrent reservations
- **Observer pattern:** Notify customers when table ready

### Advanced Features
- **Multiple restaurants:** Shared customer database
- **Reservation system:** Time-based bookings
- **Database integration:** Persist reservations
- **Notification system:** Email/SMS alerts
- **Capacity tracking:** Monitor restaurant fullness
- **Analytics:** Track usage patterns

## Learning Objectives Achieved

✅ **Smart Pointers:** Mastery of unique_ptr, shared_ptr, weak_ptr  
✅ **Memory Management:** Automatic resource cleanup, no manual new/delete  
✅ **RAII Principle:** Resources tied to object lifetime  
✅ **Ownership Semantics:** Clear understanding of exclusive vs shared ownership  
✅ **Reference Counting:** Understanding shared_ptr mechanics  
✅ **Weak References:** Non-owning pointers for observer patterns  
✅ **Container Usage:** Vectors of smart pointers  
✅ **Modern C++:** Using C++11/14 features effectively  
✅ **OOP Design:** Multiple collaborating classes with clear responsibilities  

## Common Pitfalls Avoided

### Avoided: Raw Pointers
```cpp
// DON'T DO THIS
Customer* customer = new Customer("Alice");
tables.push_back(new Table(1));  // Memory leak risk!
```

### Used: Smart Pointers
```cpp
// DO THIS INSTEAD
auto customer = make_shared<Customer>("Alice");
tables.push_back(make_unique<Table>(1));  // Safe and automatic!
```

### Avoided: Circular References
```cpp
// PROBLEM: Customer owns Table, Table owns Customer -> Memory leak!
// SOLUTION: Use weak_ptr for one direction
```

### Used: weak_ptr for Observation
```cpp
// Waitlist observes customers without owning them
std::vector<std::weak_ptr<Customer>> waitlist;
```

## Reflection

This project demonstrates intermediate-to-advanced C++ proficiency through:
- **Modern memory management** replacing manual new/delete
- **Smart pointer mastery** understanding when to use each type
- **Resource safety** automatic cleanup preventing leaks
- **Clear ownership** explicit semantics through pointer types
- **Real-world patterns** applicable to professional C++ development

The combination of `unique_ptr` (exclusive ownership), `shared_ptr` (shared ownership), and `weak_ptr` (non-owning observation) showcases sophisticated understanding of modern C++ resource management and represents industry-standard practices.

---

**Project Type:** Educational / Portfolio  
**Complexity:** Intermediate-Advanced  
**Key Skill:** Modern C++ Memory Management  
**Estimated Time:** 3-4 hours for initial implementation
