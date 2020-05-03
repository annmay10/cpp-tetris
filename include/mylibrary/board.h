// Copyright (c) 2020 [Your Name]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#include <mylibrary/tetrominos.h>
#include<mylibrary/location.h>

namespace mylibrary {
class Board {
  int width;
  int height;
  int linesCleared;
  int linesClearedTotal;
  int boardArray[10][20];
  Tetromino tetromino_;
  void deleteLine(int pY);
 public:
  void DeletePossibleLines();
  bool DetectDownwardCollision(int tetromino, Location loc);
  bool DetectRightwardCollision(int tetromino, Location loc);
  bool DetectLeftwardCollision(int tetromino, Location loc);
  int GetLinesCleared();
  int GetLinesClearedTotal() const;
  void SetLinesCleared(int setLinesCleared);
  int GetBoardArray(int i, int j);
  void SetBoardArray(int i, int j, int value);
  bool CheckGameEnd();
  Board();
};

}  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
