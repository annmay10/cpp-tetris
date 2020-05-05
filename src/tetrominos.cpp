//
// Created by Annmay on 22/04/20.
//
#include<tetris/tetrominos.h>
#include <curses.h>
#include <cinder/Color.h>
using cinder::Color;
namespace tetris {
//Stores the orientation of each of the piece types
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
//Stores the rgb values of the tetrominos in the same order as tetrominos are stored in mPieces
float colors[7][3] {
    {0,1,1},
    {1,0.5,0},
    {0,0,1},
    {1,1,0},
    {0,1,0},
    {1,0,0},
    {1,0,1}
};
int Tetromino::GetTetrominoType(int pPieceType, int pX, int pY) const {
  return mPieces[pPieceType][pX][pY];
}
float Tetromino::GetColorType(int index, int rbg) const {
  return colors[index][rbg];
}
void Tetromino::RotateTetromino(int pPieceType)
{
  int N = 4;
  // Traverse each cycle
  for (int x = 0; x < N / 2; x++) {
    // Consider elements in group of 4 in
    // current square
    for (int y = x; y < N - x - 1; y++) {

      // Swap elements of each cycle
      // in clockwise direction
      //store current cell in temp variable
      char temp = mPieces[pPieceType][x][y];
      //move values from left to top
      mPieces[pPieceType][x][y] = mPieces[pPieceType][N - 1 - y][x];
      //move values from bottom to left
      mPieces[pPieceType][N - 1 - y][x] = mPieces[pPieceType][N - 1 - x][N - 1 - y];
      //moves values from right to bottom
      mPieces[pPieceType][N - 1 - x][N - 1 - y] = mPieces[pPieceType][y][N - 1 - x];
      //assigns value to right
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
int Tetromino::GetSouthernmostPoint(int tetromino) const {
  int southernmost = 0;
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      if (GetTetrominoType(tetromino, x, y) == 1) {
        //Checks if the y-current point is the southermost
        if (y > southernmost) {
          southernmost = y;
        }
      }
    }
  }
  return southernmost;
}
int Tetromino::GetWestmostPoint(int tetromino) const {
  int westmost = 3;
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      if (GetTetrominoType(tetromino, x, y) == 1) {
        //Checks if the current x-point is the westhermost
        if (x < westmost) {
          westmost = x;
        }
      }
    }
  }
  return westmost;
}
int Tetromino::GetEastmostPoint(int tetromino) const {
  int eastmost = 0;
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      if (GetTetrominoType(tetromino, x, y) == 1) {
        //Checks if the current x-point is the southermost
        if (x > eastmost) {
          eastmost = x;
        }
      }
    }
  }
  return eastmost;
}



}

