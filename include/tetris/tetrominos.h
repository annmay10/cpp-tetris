//
// Created by Annmay on 22/04/20.
//

#ifndef FINALPROJECT_INCLUDE_TETRIS_TETROMINOS_H_
#define FINALPROJECT_INCLUDE_TETRIS_TETROMINOS_H_

#include <cinder/Color.h>
namespace tetris {
class Tetromino {
 public:
  int GetTetrominoType(int pPieceType, int pX, int pY);
  float GetColorType(int index, int rbg);
  void RotateTetromino(int pPieceType);
  void RotateTetrominoCounterClockwise(int pPieceType);
  int GetWestmostPoint(int tetromino);
  int GetEastmostPoint(int tetromino);
  int GetSouthernmostPoint(int tetromino);

};
}

#endif //TETRIS_INCLUDE_TETRIS_TETROMINOS_H_
