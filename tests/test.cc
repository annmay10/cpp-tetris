// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cinder/Rand.h>
#include <mylibrary/tetrominos.h>

#include <mylibrary/board.h>



TEST_CASE("Check tetrominos - N", "[tetromino]") {
  mylibrary::Tetromino tetromino;
  REQUIRE(tetromino.GetTetrominoType(4,1,2) == 1);
}
TEST_CASE("Check rotation - N", "[tetromino]") {
  mylibrary::Tetromino tetromino;
  tetromino.RotateTetromino(4);
  REQUIRE(tetromino.GetTetrominoType(4, 0, 1) == 1);
}
TEST_CASE("Checking counter rotation - N", "[tetromino]") {
  mylibrary::Tetromino tetromino;
  tetromino.RotateTetrominoCounterClockwise(4);
  REQUIRE(tetromino.GetTetrominoType(4,1,2) == 1);
}
TEST_CASE("Check southern most point", "[tetromino]") {
  mylibrary::Tetromino tetromino;
  int southernmost = tetromino.GetSouthernmostPoint(4);
  REQUIRE(southernmost == 2);
}
TEST_CASE("Check eastern most point", "[tetromino]") {
  mylibrary::Tetromino tetromino;
  int easternmost = tetromino.GetEastmostPoint(4);
  REQUIRE(easternmost == 2);
}
TEST_CASE("Check western most point", "[tetromino]") {
  mylibrary::Tetromino tetromino;
  int westernmost = tetromino.GetWestmostPoint(4);
  REQUIRE(westernmost == 1);
}
TEST_CASE("Check game end", "[board]") {
  mylibrary::Board board = mylibrary::Board();
  board.SetBoardArray(4,0,1);
  REQUIRE(board.CheckGameEnd());
}
TEST_CASE("Check downward collision", "[board]") {
  mylibrary::Board board = mylibrary::Board();
  board.SetBoardArray(4,19,1);
  board.SetBoardArray(3,19,1);
  board.SetBoardArray(2,19,1);
  board.SetBoardArray(1,19,1);
  mylibrary::Location loc = mylibrary::Location(40,680);
  REQUIRE(board.DetectDownwardCollision(6,loc));
}
TEST_CASE("Check rightward collision", "[board]") {
  mylibrary::Board board = mylibrary::Board();
  board.SetBoardArray(4,19,1);
  board.SetBoardArray(4,18,1);
  board.SetBoardArray(4,17,1);
  board.SetBoardArray(4,16,1);
  mylibrary::Location loc = mylibrary::Location(80,720);
  REQUIRE(board.DetectRightwardCollision(6,loc));
}
TEST_CASE("Check leftward collision", "[board]") {
  mylibrary::Board board = mylibrary::Board();
  board.SetBoardArray(4,19,1);
  board.SetBoardArray(4,18,1);
  board.SetBoardArray(4,17,1);
  board.SetBoardArray(4,16,1);
  mylibrary::Location loc = mylibrary::Location(200,720);
  REQUIRE(board.DetectLeftwardCollision(6,loc));
}
TEST_CASE("Delete Possible Lines", "[board]") {
  mylibrary::Board board = mylibrary::Board();
  for (int i = 0; i < 10; i++) {
    board.SetBoardArray(i, 19, 1);
  }
  board.DeletePossibleLines();
  REQUIRE(board.GetBoardArray(4,19) == 0);
}
TEST_CASE("Testing Row Incrementer", "[location]") {
  mylibrary::Location loc = mylibrary::Location(0,0);
  loc.IncrementRow();
  REQUIRE(loc.Row() == 40);
}
TEST_CASE("Testing Row Decrementer", "[location]") {
  mylibrary::Location loc = mylibrary::Location(80,0);
  loc.DecrementRow();
  REQUIRE(loc.Row() == 40);
}
TEST_CASE("Testing Column Incrementer", "[location]") {
  mylibrary::Location loc = mylibrary::Location(0,0);
  loc.IncrementCol();
  REQUIRE(loc.Col() == 40);
}
