//
// Created by Annmay on 22/04/20.
//
#include<mylibrary/tetrominos.h>
#include <curses.h>
#include <cinder/Color.h>
using cinder::Color;
namespace mylibrary {
char mPieces[7][4][4] = {
    //I
    {
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    },
    //J
    {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0}
    },
    //J mirrored
    {
        {0, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0}
    },
    //O
    {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    },
    //N
    {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 0, 0}
    },
    //N mirrored
    {
        {0, 0, 0, 0},
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    },
    //T
    {
        {0, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    }
};
int pivots[6][2] {
    //I
    {1,1},
    //J
    {2,1},
    //J-mirrored
    {2,1},
    //N
    {2,1},
    //N-mirrored
    {2,1},
    //T
    {1,2}
};
float colors[7][3] {
    {0,1,1},
    {1,0.5,0},
    {0,0,1},
    {1,1,0},
    {0,1,0},
    {1,0,0},
    {1,0,1}
};
int Tetromino::GetTetrominoType(int pPieceType, int pX, int pY) {
  return mPieces[pPieceType][pX][pY];
}
float Tetromino::GetColorType(int index, int rbg) {
  return colors[index][rbg];
}
void Tetromino::setPivots(int pPieceType) {
  xPivot = pivots[pPieceType][1];
  yPivot = pivots[pPieceType][1];
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      if (mPieces[pPieceType][x][y] == 1) {
        xBrickCenter = xPivot + x;
        yBrickCenter = yPivot + y;
      }
    }
  }
}
void Tetromino::RotateTetromino(int pPieceType)
{
  int N = 4;
  // Traverse each cycle
  for (int x = 0; x < 4 / 2; x++) {
    for (int y = x; y < 4 - x - 1; y++) {

      // Swap elements of each cycle
      // in clockwise direction
      int temp = mPieces[pPieceType][x][y];
      mPieces[pPieceType][x][y] = mPieces[pPieceType][4 - 1 - y][x];
      mPieces[pPieceType][N - 1 - y][x] = mPieces[pPieceType][N - 1 - x][N - 1 - y];
      mPieces[pPieceType][N - 1 - x][N - 1 - y] = mPieces[pPieceType][y][N - 1 - x];
      mPieces[pPieceType][y][N - 1 - x] = temp;
    }
  }
}
void Tetromino::RotateTetrominoCounterClockwise(int pPieceType)
{
  // Consider all squares one by one
  for (int x = 0; x < 4 / 2; x++) {
    // Consider elements in group of 4 in
    // current square
    for (int y = x; y < 4 - x - 1; y++) {
      // store current cell in temp variable
      char temp = mPieces[pPieceType][x][y];

      // move values from right to top
      mPieces[pPieceType][x][y] = mPieces[pPieceType][y][4 - 1 - x];

      // move values from bottom to right
      mPieces[pPieceType][y][4 - 1 - x] = mPieces[pPieceType][4 - 1 - x][4 - 1 - y];

      // move values from left to bottom
      mPieces[pPieceType][4 - 1 - x][4 - 1 - y] = mPieces[pPieceType][4 - 1 - y][x];

      // assign temp to left
      mPieces[pPieceType][4 - 1 - y][x] = temp;
    }
  }
}
int Tetromino::GetSouthernmostPoint(int tetromino) {
  int southernmost = 0;
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      if (GetTetrominoType(tetromino, x, y) == 1) {
        if (y > southernmost) {
          southernmost = y;
        }
      }
    }
  }
  return southernmost;
}
int Tetromino::GetWestmostPoint(int tetromino) {
  int westmost = 3;
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      if (GetTetrominoType(tetromino, x, y) == 1) {
        if (x < westmost) {
          westmost = x;
        }
      }
    }
  }
  return westmost;
}
int Tetromino::GetEastmostPoint(int tetromino) {
  int eastmost = 0;
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      if (GetTetrominoType(tetromino, x, y) == 1) {
        if (x > eastmost) {
          eastmost = x;
        }
      }
    }
  }
  return eastmost;
}



}

