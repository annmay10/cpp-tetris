//
// Created by Annmay on 24/04/20.
//
#include <tetris/location.h>
namespace tetris {
Location::Location(int row, int col) : row_(row), col_(col) {}
int Location::Row() const {
  return row_;
}
int Location::Col() const {
  return col_;
}
void Location::IncrementRow() {
  row_ += 40;
}
void Location::DecrementRow() {
  row_ -= 40;
}
void Location::IncrementCol() {
  col_ += 40;
}
}

