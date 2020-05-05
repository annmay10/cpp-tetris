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
  void UpdateScore(int level);
  void DeletePossibleLines();
  bool DetectDownwardCollision(int tetromino, Location loc);
  bool DetectRightwardCollision(int tetromino, Location loc);
  bool DetectLeftwardCollision(int tetromino, Location loc);
  int GetLinesCleared();
  int GetLinesClearedTotal() const;
  void SetLinesCleared(int setLinesCleared);
  int GetBoardArray(int row, int col);
  void SetBoardArray(int row, int col, int value);
  bool CheckGameEnd();
  Board();
};

}  // namespace tetris


#endif // FINALPROJECT_TETRIS_EXAMPLE_H_
