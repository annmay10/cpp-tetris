// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/board.h>
#include<mylibrary/location.h>

namespace mylibrary {
Board::Board() {
  width = 10;
  height = 20;
  linesCleared = 0;
  linesClearedTotal = 0;
}
int Board::GetBoardArray(int i, int j) {
  return boardArray[i][j];
}
void Board::SetBoardArray(int i, int j, int value) {
  boardArray[i][j] = value;
}
bool Board::DetectDownwardCollision(int tetromino, Location loc) {
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      if (tetromino_.GetTetrominoType(tetromino, x, y) == 1) {
        int toCheckCol = (loc.Col() / 40) + y + 1;
        int toCheckRow = (loc.Row() / 40) + x;
        if (boardArray[toCheckRow][toCheckCol] != 0) {
          return true;
        }
      }
    }
  }
  return false;
}
bool Board::DetectLeftwardCollision(int tetromino, Location loc) {
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      if (tetromino_.GetTetrominoType(tetromino, x, y) == 1) {
        int toCheckCol = (loc.Col() / 40) + y;
        int toCheckRow = (loc.Row() / 40) + x - 1;
        if (boardArray[toCheckRow][toCheckCol] != 0) {
          return true;
        }
      }
    }
  }
  return false;
}
bool Board::DetectRightwardCollision(int tetromino, Location loc) {
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      if (tetromino_.GetTetrominoType(tetromino, x, y) == 1) {
        int toCheckCol = (loc.Col() / 40) + y;
        int toCheckRow = (loc.Row() / 40) + x + 1;
        if (boardArray[toCheckRow][toCheckCol] != 0) {
          return true;
        }
      }
    }
  }
  return false;
}
void Board::deleteLine(int pY) {
  int BOARD_WIDTH = 10;
  for (int j = pY; j > 0; j--)
  {
    for (int i = 0; i < BOARD_WIDTH; i++)
    {
      boardArray[i][j] = boardArray[i][j-1];
    }
  }
}
void Board::DeletePossibleLines ()
{
  int BOARD_HEIGHT = 20;
  int BOARD_WIDTH = 10;
  for (int j = 0; j < BOARD_HEIGHT; j++)
  {
    int i = 0;
    while (i < BOARD_WIDTH)
    {
      if (boardArray[i][j] == 0) break;
      i++;
    }
    if (i == BOARD_WIDTH) {
      deleteLine (j);
      linesCleared++;
      linesClearedTotal += 1;
    }

  }
}
bool Board::CheckGameEnd() {
  for (int i = 0; i < width; i++) {
    if (boardArray[i][0] != 0) {
      return true;
    }
  }
  return false;
}
int Board::GetLinesCleared() {
  return linesCleared;
}
int Board::GetLinesClearedTotal() const {
  return linesClearedTotal;
}

void Board::SetLinesCleared(int setLinesCleared) {
  linesCleared = setLinesCleared;
}
}  // namespace mylibrary
