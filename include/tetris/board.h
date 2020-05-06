// Copyright (c) 2020 [Your Name]. All rights reserved.
#ifndef FINALPROJECT_TETRIS_EXAMPLE_H_
#define FINALPROJECT_TETRIS_EXAMPLE_H_
#include <tetris/tetrominos.h>
#include<tetris/location.h>

namespace tetris {
class Board {
  int width_;
  int height_;
  int lines_cleared_;
  int lines_cleared_total_;
  int board_array_[10][20];
  int score_;
  Tetromino tetromino_;
  void DeleteLine(int pY);
  void InstantiateBoard();
 public:
  int GetScore() const;
  int GetWidth() const;
  int GetHeight() const;
  /**
   * Updates the score according to the level the user is in
   * @param level The current level of the user
   */
  void UpdateScore(int level);
  /**
   * Deletes lines which are full
   */
  void DeletePossibleLines();
  /**
   *
   * @param tetromino the piece type
   * @param loc the current location of the piece
   * @return If the tetromino will collide with another tetromino placed below
   */
  bool DetectDownwardCollision(int tetromino, Location loc);
  /**
   *
   * @param tetromino the piece type
   * @param loc the current location of the piece
   * @return If the tetromino will collide with another tetromino placed on the right
   */
  bool DetectRightwardCollision(int tetromino, Location loc);
  /**
   *
   * @param tetromino the piece type
   * @param loc the current location of the piece
   * @return If the tetromino will collide with another tetromino placed on the left
   */
  bool DetectLeftwardCollision(int tetromino, Location loc);
  int GetLinesCleared();
  int GetLinesClearedTotal() const;
  void SetLinesCleared(int setLinesCleared);
  int GetBoardArray(int row, int col) const;
  void SetBoardArray(int row, int col, int value);
  /**
   * Returns true (game is over) if the board's top most row has a block
   * @return if the game is over
   */
  bool CheckGameEnd();
  Board();
};

}  // namespace tetris


#endif // FINALPROJECT_TETRIS_EXAMPLE_H_
