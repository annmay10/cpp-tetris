//
// Created by Annmay on 24/04/20.
//
#include <mylibrary/location.h>
namespace mylibrary {
Location::Location(int row, int col) : row_(row), col_(col) {}
int Location::Row() const {
  return row_;
}
int Location::Col() const {
  return col_;
}
}
