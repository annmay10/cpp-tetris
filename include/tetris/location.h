//
// Created by Annmay on 24/04/20.
//
#ifndef FINALPROJECT_INCLUDE_TETRIS_LOCATION_H_
#define FINALPROJECT_INCLUDE_TETRIS_LOCATION_H_
namespace tetris {
//Represents a location on the board
class Location{
 private:
  int col_;
  int row_;
 public :
  Location(int row, int col);
  int Row() const;
  int Col() const;
  //Increments the column of the location by tile size(40)
  void IncrementCol();
  //Decrements the row of the location by tile size(40)
  void IncrementRow();
  //Decrements the column of the location by tile size(40)
  void DecrementRow();
};
}
#endif //FINALPROJECT_INCLUDE_TETRIS_LOCATION_H_
