//
// Created by Annmay on 24/04/20.
//
#ifndef FINALPROJECT_INCLUDE_MYLIBRARY_LOCATION_H_
#define FINALPROJECT_INCLUDE_MYLIBRARY_LOCATION_H_
namespace mylibrary {
class Location{
 public :
  Location(int row, int col);
  int Row() const;
  int Col() const;
  int col_;
  int row_;
};
}
#endif //FINALPROJECT_INCLUDE_MYLIBRARY_LOCATION_H_
