# Library Management System

**Language:** C++11  
**Type:** Intermediate C++ Project  
**Concepts:** OOP, Static Members, Mutable Members, External Variables, STL Containers

## Project Overview

A library management system that simulates real-world library operations including book inventory management, borrowing, and reservation functionality. The system tracks a shared budget across the library and maintains statistics on borrowed books across all library instances.

## Features

### Core Functionality
- **Add Books:** Add new books to the library inventory with cost tracking
- **Borrow Books:** Remove books from available inventory and track borrowing statistics
- **Reserve Books:** Reserve available books without removing them from inventory
- **List Books:** Display all currently available books in the library
- **Budget Management:** Track library budget across all transactions
- **Borrowing Statistics:** Monitor total borrowed books across all library instances

### Technical Highlights
- **Capacity Limit:** Library capped at 100 books maximum
- **Global Budget:** Shared `libraryBudget` variable across translation units
- **Static Tracking:** Class-level counter for all borrowed books
- **Const Safety:** Reservation system uses const member function with mutable state
- **Error Handling:** Validation for non-existent books and duplicate reservations

## Architecture

### File Structure

```
Library_Management_System/
├── README.md              # This file
├── Library.hpp            # Library class declaration
├── Library.cpp            # Library class implementation
├── main.cpp               # Driver program and budget initialization
└── removeElement.hpp      # Helper function for vector element removal (included)
```

### Class Design: `Library`

**Private Members:**
```cpp
vector<string> bookList;              // Dynamic list of available books
static int totalBorrowedBooks;        // Class-level borrowing counter
mutable int reservedCount;            // Per-instance reservation counter
mutable vector<string> reservedBooks; // List of reserved books (modifiable in const)
```

**Public Interface:**
```cpp
Library();                                  // Constructor
void addBook(string title, double cost);    // Add book and deduct from budget
bool borrowBook(string title);              // Borrow book, return success status
void listBooks();                           // Display available books
static int getTotalBorrowedBooks();         // Get class-level borrow count
void reserveBook(string title) const;       // Reserve book (const function)
```

**External Variable:**
```cpp
extern double libraryBudget;  // Shared across all instances (defined in main.cpp)
```

## Key C++ Concepts Demonstrated

### 1. Static Members
```cpp
static int totalBorrowedBooks;
```
- **Purpose:** Track total borrowed books across ALL library instances
- **Initialization:** Must be initialized outside class (in .cpp file)
- **Access:** Via `Library::getTotalBorrowedBooks()` static function
- **Use Case:** Global statistics that transcend individual library objects

### 2. Mutable Members
```cpp
mutable int reservedCount;
mutable vector<string> reservedBooks;
```
- **Purpose:** Allow modification in const member functions
- **Rationale:** Reservation doesn't change library's logical state (available books unchanged)
- **Pattern:** Cache-like behavior - internal bookkeeping in const context

### 3. External Variables
```cpp
extern double libraryBudget;  // in Library.hpp
double libraryBudget = 5000;  // in main.cpp
```
- **Purpose:** Share single budget variable across multiple translation units
- **Linkage:** External linkage allows multiple files to access same variable
- **Scope:** Global scope, but declared extern to avoid multiple definitions

### 4. Const Correctness
```cpp
void reserveBook(string title) const;
```
- **Design Choice:** Reservation queries availability but doesn't modify bookList
- **Mutable Use:** Allows updating reservedCount and reservedBooks despite const
- **Benefit:** Communicates that function doesn't change observable library state

### 5. STL Containers
```cpp
vector<string> bookList;
```
- **Dynamic Sizing:** Automatically manages memory for book titles
- **Iteration:** Range-based for loops for clean syntax
- **Safety:** No manual memory management required

### 6. Multi-file Organization
- **Library.hpp:** Interface (class declaration, function prototypes)
- **Library.cpp:** Implementation (function definitions)
- **main.cpp:** Usage (client code, budget initialization)
- **removeElement.hpp:** Utility function for removing elements from vectors
- **Benefit:** Separation of interface and implementation, reusable components

## Helper Function: removeElement

### Purpose
A utility function to remove the first occurrence of an element from a `vector<string>`.

### Implementation
```cpp
void removeElement(vector<string>& vec, string s) {
    auto it = find(vec.begin(), vec.end(), s);
    if (it != vec.end()) {
        vec.erase(it);
    }
}
```

### How It Works
1. **Search:** Uses STL `find()` to locate the element
2. **Check:** Verifies element exists (iterator != end)
3. **Remove:** Erases the element from the vector
4. **Safety:** If element not found, no action taken (no error)

### Why Separate File?
- **Reusability:** Can be used by multiple classes/files
- **Modularity:** Keeps Library.cpp focused on Library logic
- **Single Responsibility:** One function, one purpose
- **Template Potential:** Could be templated for any vector type in future

### Used In
Called by `Library::borrowBook()` to remove a book from the `bookList` when borrowed:
```cpp
bool Library::borrowBook(string title) {
    for (const auto& book : bookList) {
        if (book == title) {
            removeElement(bookList, title);  // <- Removes book from vector
            cout << "Book borrowed!" << endl;
            totalBorrowedBooks++;
            return true;
        }
    }
    cout << "Book not found!" << endl;
    return false;
}
```

## Usage Example

```cpp
#include "Library.hpp"
#include <iostream>

double libraryBudget = 5000;  // Initialize shared budget

int main() {
    Library myLibrary;
    
    // Add books
    myLibrary.addBook("The Great Gatsby", 300);
    myLibrary.addBook("1984", 400);
    myLibrary.addBook("To Kill a Mockingbird", 350);
    
    // List available books
    myLibrary.listBooks();
    
    // Reserve a book (doesn't remove from inventory)
    myLibrary.reserveBook("1984");
    
    // Borrow a book (removes from inventory)
    myLibrary.borrowBook("To Kill a Mockingbird");
    
    // Check statistics
    int total = Library::getTotalBorrowedBooks();
    std::cout << "Total borrowed books: " << total << std::endl;
    
    return 0;
}
```

## Expected Output

```
Current library budget is: 5000
- The Great Gatsby
- 1984
- To Kill a Mockingbird
Book reserved: 1984
Reserved book count: 1
Book borrowed!
The total number of borrowed books is: 1
```

## Compilation and Execution

### Using g++
```bash
# Compile all source files
g++ -std=c++11 -o library main.cpp Library.cpp

# Run the program
./library
```

### Using clang++
```bash
clang++ -std=c++11 -o library main.cpp Library.cpp
./library
```

### Using MSVC (Windows)
```bash
cl /EHsc /std:c++11 main.cpp Library.cpp
library.exe
```

## Design Decisions

### Why Static for totalBorrowedBooks?
- Tracks library-wide statistics across all instances
- Useful for multi-branch library systems
- Demonstrates class-level vs. instance-level data

### Why Mutable for Reservations?
- Reservations are internal bookkeeping, not part of observable state
- Available books (bookList) remain unchanged during reservation
- Allows const correctness while maintaining flexibility

### Why External for libraryBudget?
- Simulates shared resource across entire library system
- All library instances affect same budget
- Demonstrates external linkage and scope management

### Why Vector over Array?
- Dynamic sizing (don't need to know number of books upfront)
- Automatic memory management (no manual new/delete)
- Rich STL interface (iterators, algorithms)
- Safety (bounds checking with .at())

## Potential Enhancements

### Functional Improvements
- **Return borrowed books:** Add `returnBook()` method
- **Search functionality:** Find books by author, genre, ISBN
- **Due dates:** Track when books should be returned
- **Late fees:** Calculate penalties for overdue books
- **User accounts:** Associate borrowers with borrowed books

### Technical Improvements
- **Input validation:** Check for empty strings, negative costs
- **Exception handling:** Use try-catch for error conditions
- **Smart pointers:** Replace raw data with unique_ptr/shared_ptr
- **File I/O:** Persist library state to disk
- **Book class:** Create dedicated Book object with attributes (author, ISBN, genre)
- **Overloaded operators:** Operator<< for printing, operator== for comparison
- **Template removeElement:** Generalize helper function for any vector type

### Advanced Features
- **Template version:** Generic library for any item type
- **Inheritance:** Base Library class, derived DigitalLibrary, PhysicalLibrary
- **Polymorphism:** Virtual functions for different library types
- **Move semantics:** Efficient book transfers between libraries
- **Concurrency:** Thread-safe borrowing for multi-user scenarios

## Learning Objectives Achieved

✅ **Class Design:** Created well-encapsulated class with clear interface  
✅ **Static Members:** Implemented class-level data sharing  
✅ **Mutable Members:** Used mutable for const-correct design  
✅ **External Variables:** Shared data across translation units  
✅ **STL Proficiency:** Leveraged vector for dynamic storage  
✅ **Const Correctness:** Proper use of const member functions  
✅ **Multi-file Projects:** Organized code across headers and implementations  
✅ **Error Handling:** Validated operations and provided user feedback  

## Implementation Notes

### Static Member Initialization
The static member `totalBorrowedBooks` is correctly initialized in Library.cpp:
```cpp
int Library::totalBorrowedBooks = 0;
```
This is required for all static members - they must be defined outside the class declaration.

### External Variable Definition
The `libraryBudget` variable is correctly defined in main.cpp:
```cpp
double libraryBudget = 5000;  // Defined once in main.cpp
```
And declared as `extern` in Library.hpp:
```cpp
extern double libraryBudget;  // Declared in header
```
This allows all files that include Library.hpp to access the same shared budget variable.

## Reflection

This project demonstrates intermediate C++ proficiency through:
- Proper use of OOP encapsulation and interfaces
- Understanding of storage classes (static, mutable, extern)
- Multi-file project organization
- STL container usage
- Const correctness principles

The combination of static members (class-level data), mutable members (flexible const functions), and external variables (cross-file sharing) showcases sophisticated understanding of C++ storage and scope management.

---

**Project Type:** Educational / Portfolio  
**Complexity:** Intermediate  
**Estimated Time:** 2-3 hours for initial implementation
