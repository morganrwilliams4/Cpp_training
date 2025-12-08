#include "Library.hpp"
#include "removeElement.hpp"
#include <iostream>

using namespace std;

int Library::totalBorrowedBooks = 0;

Library::Library() : reservedCount(0) {}

void Library::listBooks() {
  for (const auto& book: bookList) {
    cout << "- " << book << endl;
  }
};

void Library::addBook(string title, double bookCost) {
  if (bookList.size() < 100) {
    bookList.push_back(title);
    libraryBudget -= bookCost;
  } else {
    cout << "Library is full!" << endl;
  }
};

bool Library::borrowBook(string title) {
  for (const auto& book : bookList) {
    if (book == title) {
      removeElement(bookList, title);
      cout << "Book borrowed!" << endl;
      totalBorrowedBooks++;
      return true;
    }
  }
  cout << "Book not found!" << endl;
  return false;
};

int Library::getTotalBorrowedBooks() {
  return totalBorrowedBooks;
};

void Library::reserveBook(string title) const {
  bool inLibrary = false;
  for (const auto& book : bookList) {
    if (book == title) {
      inLibrary = true;
      break;
    }
  }  
    if (!inLibrary) {
      cout << "Book not reserved!" << endl;
      return;
    }
    for (const auto& reserved : reservedBooks) {
      if (reserved == title) {
        cout << "Book not reserved!" << endl;
        return;
      }
    }
    reservedBooks.push_back(title);
    reservedCount++;
    cout << "Book reserved: " << title << endl;
    cout << "Reserved book count: " << reservedCount << endl; 
  }
