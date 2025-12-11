#ifndef TABLE_H
#define TABLE_H

class Table {
private:
  int number;
  bool isAvailable;

public:
  Table(int num);
  void reserve();
  void release();
  bool getIsAvailable() const;
  int getNumber() const;
};

#endif
