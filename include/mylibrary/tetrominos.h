//
// Created by Annmay on 22/04/20.
//

#ifndef FINALPROJECT_INCLUDE_MYLIBRARY_TETROMINOS_H_
#define FINALPROJECT_INCLUDE_MYLIBRARY_TETROMINOS_H_

#include <cinder/Color.h>
namespace mylibrary {
class Tetromino {
 private:
  int xBrickCenter;
  int yBrickCenter;
  int xPivot;
  int yPivot;
 public:
  void setPivots(int pPieceType);
  int GetTetrominoType(int pPieceType, int pX, int pY);
  float GetColorType(int index, int rbg);
  void RotateTetromino(int pPieceType);
  void RotateTetrominoCounterClockwise(int pPieceType);
  int GetWestmostPoint(int tetromino);
  int GetEastmostPoint(int tetromino);
  int GetSouthernmostPoint(int tetromino);

};
}

#endif //FINALPROJECT_INCLUDE_MYLIBRARY_TETROMINOS_H_
