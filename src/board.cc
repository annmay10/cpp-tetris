// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <tetris/board.h>
#include<tetris/location.h>

namespace tetris {
const int kTileSize = 40;
Board::Board() {
  score_ = 0;
  width_ = 10;
  height_ = 20;
  lines_cleared_ = 0;
  lines_cleared_total_ = 0;
  InstantiateBoard();
}
void Board::UpdateScore(int level) {
  if (lines_cleared_ == 1) {
    score_ += (100 * level);
  } else if (lines_cleared_ == 2) {
    score_ += (400 * level);
  } else if (lines_cleared_ == 3) {
    score_ += (900 * level);
  } else if (lines_cleared_ == 4) {
    score_ += (2500 * level);
  }
}
void Board::InstantiateBoard() {
  for (int i = 0; i < width_; i++) {
    for (int j = 0; j < height_; j++) {
      board_array_[i][j] = 0;
    }
  }
}

int Board::GetBoardArray(int row, int col) {
  return board_array_[row][col];
}
void Board::SetBoardArray(int row, int col, int value) {
  board_array_[row][col] = value;
}
bool Board::DetectDownwardCollision(int tetromino, Location loc) {
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      //Gets the valid positions of the tetromino
      if (tetromino_.GetTetrominoType(tetromino, x, y) == 1) {
        //Checks if the board array contains a block below the current tetromino
        int toCheckCol = (loc.Col() / kTileSize) + y + 1;
        int toCheckRow = (loc.Row() / kTileSize) + x;
        if (board_array_[toCheckRow][toCheckCol] != 0) {
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
      //Gets the valid positions of the tetromino
      if (tetromino_.GetTetrominoType(tetromino, x, y) == 1) {
        //Checks if the board array contains a block to the left of the current tetromino
        int toCheckCol = (loc.Col() / kTileSize) + y;
        int toCheckRow = (loc.Row() / kTileSize) + x - 1;
        if (board_array_[toCheckRow][toCheckCol] != 0) {
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
      //Checks the valid positions of the tetromino
      if (tetromino_.GetTetrominoType(tetromino, x, y) == 1) {
        //Checks if the board array contains a block to the right of the current tetromino
        int toCheckCol = (loc.Col() / kTileSize) + y;
        int toCheckRow = (loc.Row() / kTileSize) + x + 1;
        if (board_array_[toCheckRow][toCheckCol] != 0) {
          return true;
        }
      }
    }
  }
  return false;
}
void Board::DeleteLine(int pY) {
  for (int j = pY; j > 0; j--)
  {
    for (int i = 0; i < width_; i++)
    {
      board_array_[i][j] = board_array_[i][j-1];
    }
  }
}
void Board::DeletePossibleLines ()
{
  for (int j = 0; j < height_; j++)
  {
    int i = 0;
    while (i < width_)
    {
      if (board_array_[i][j] == 0) break;
      i++;
    }
    //Checks if an entire line is full
    if (i == width_) {
      DeleteLine (j);
      lines_cleared_++;
      lines_cleared_total_++;
    }

  }
}
bool Board::CheckGameEnd() {
  for (int i = 0; i < width_; i++) {
    //If there is a single block at the top of the screen the game is over
    if (board_array_[i][0] != 0) {
      return true;
    }
  }
  return false;
}
int Board::GetLinesCleared() {
  return lines_cleared_;
}
int Board::GetLinesClearedTotal() const {
  return lines_cleared_total_;
}

void Board::SetLinesCleared(int setLinesCleared) {
  lines_cleared_ = setLinesCleared;
}
int Board::GetWidth() const {
  return width_;
}
int Board::GetHeight() const {
  return height_;
}
int Board::GetScore() const {
  return score_;
}
}  // namespace tetris
