//
// Created by Annmay on 22/04/20.
//
#include<mylibrary/tetrominos.h>

namespace mylibrary {
char mPieces[7][4][4] = {
    //I
    {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0}
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
int Tetromino::GetTetrominoType(int pPieceType, int pX, int pY) {
  return mPieces[pPieceType][pX][pY];
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
void Tetromino::RotateTetromino(int pPieceType) {
  xBrickCenter = xPivot + yPivot - yBrickCenter;
  yBrickCenter = yPivot - xPivot + xBrickCenter;
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      if (mPieces[pPieceType][x][y] == 1) {
        xBrickCenter = xPivot + x + xBrickCenter;
        yBrickCenter = yPivot + y + yBrickCenter;
      }
    }
  }
}


}

