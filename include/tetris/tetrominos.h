//
// Created by Annmay on 22/04/20.
//

#ifndef FINALPROJECT_INCLUDE_TETRIS_TETROMINOS_H_
#define FINALPROJECT_INCLUDE_TETRIS_TETROMINOS_H_

#include <cinder/Color.h>
namespace tetris {
class Tetromino {
 public:
  /**
   * Used to extract value from mPieces given the coordinates and piece type
   * @param pPieceType The piece type out of given seven types(0-6)
   * @param pX The x coordinate from the 2-d array
   * @param pY The y-coordinate from the 2-d array
   * @return The integer in the 2-d array of a piece (1 if it has a block, 0 if it doesn't)
   */
  int GetTetrominoType(int pPieceType, int pX, int pY) const;
  /**
   * Used to give the rgb values of the individual colour of a specific piece type
   * @param index the index of the array depending on piece type
   * @param rbg 0 for red vaue, 1 for blue value, and 2 for green value
   * @return the red, green or blue value of the given tetromino
   */
  float GetColorType(int index, int rbg) const;
  /**
   * Rotates the tetromino by 90 degrees clockwise
   * @param pPieceType the index of the piece type from mPieces
   */
  void RotateTetromino(int pPieceType);
  /**
   * Rotates the tetromino by 90 degrees counter-clockwise
   * @param pPieceType the index of the piece type from mPieces
   */
  void RotateTetrominoCounterClockwise(int pPieceType);
  /**
   *
   * @param tetromino the tetromino piece type
   * @return the west-most point of the piece
   */
  int GetWestmostPoint(int tetromino) const;
  /**
   *
   * @param tetromino the tetromino piece type
   * @return the west-most point of the piece
   */
  int GetEastmostPoint(int tetromino) const;
  /**
   *
   * @param tetromino tetromino the tetromino piece type
   * @return the west-most point of the piece
   */
  int GetSouthernmostPoint(int tetromino) const;

};
}

#endif //TETRIS_INCLUDE_TETRIS_TETROMINOS_H_
