//
// Created by Annmay on 22/04/20.
//

#ifndef FINALPROJECT_INCLUDE_MYLIBRARY_TETROMINOS_H_
#define FINALPROJECT_INCLUDE_MYLIBRARY_TETROMINOS_H_

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
  void RotateTetromino(int pPieceType);
};
}

#endif //FINALPROJECT_INCLUDE_MYLIBRARY_TETROMINOS_H_
