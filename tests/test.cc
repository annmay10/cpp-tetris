// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cinder/Rand.h>
#include <tetris/tetrominos.h>

#include <tetris/board.h>



TEST_CASE("Check tetrominos - N", "[tetromino]") {
  tetris::Tetromino tetromino;
  REQUIRE(tetromino.GetTetrominoType(4,1,2) == 1);
}
TEST_CASE("Check rotation - N", "[tetromino]") {
  tetris::Tetromino tetromino;
  tetromino.RotateTetromino(4);
  REQUIRE(tetromino.GetTetrominoType(4, 0, 1) == 1);
}
TEST_CASE("Checking counter rotation - N", "[tetromino]") {
  tetris::Tetromino tetromino;
  tetromino.RotateTetrominoCounterClockwise(4);
  REQUIRE(tetromino.GetTetrominoType(4,1,2) == 1);
}
TEST_CASE("Check southern most point", "[tetromino]") {
  tetris::Tetromino tetromino;
  int southernmost = tetromino.GetSouthernmostPoint(4);
  REQUIRE(southernmost == 2);
}
TEST_CASE("Check eastern most point", "[tetromino]") {
  tetris::Tetromino tetromino;
  int easternmost = tetromino.GetEastmostPoint(4);
  REQUIRE(easternmost == 2);
}
TEST_CASE("Check western most point", "[tetromino]") {
  tetris::Tetromino tetromino;
  int westernmost = tetromino.GetWestmostPoint(4);
  REQUIRE(westernmost == 1);
}
TEST_CASE("Check game end", "[board]") {
  tetris::Board board = tetris::Board();
  board.SetBoardArray(4,0,1);
  REQUIRE(board.CheckGameEnd());
}
TEST_CASE("Check downward collision", "[board]") {
  tetris::Board board = tetris::Board();
  board.SetBoardArray(4,19,1);
  board.SetBoardArray(3,19,1);
  board.SetBoardArray(2,19,1);
  board.SetBoardArray(1,19,1);
  tetris::Location loc = tetris::Location(40,680);
  REQUIRE(board.DetectDownwardCollision(6,loc));
}
TEST_CASE("Check rightward collision", "[board]") {
  tetris::Board board = tetris::Board();
  board.SetBoardArray(4,19,1);
  board.SetBoardArray(4,18,1);
  board.SetBoardArray(4,17,1);
  board.SetBoardArray(4,16,1);
  tetris::Location loc = tetris::Location(80,720);
  REQUIRE(board.DetectRightwardCollision(6,loc));
}
TEST_CASE("Check leftward collision", "[board]") {
  tetris::Board board = tetris::Board();
  board.SetBoardArray(4,19,1);
  board.SetBoardArray(4,18,1);
  board.SetBoardArray(4,17,1);
  board.SetBoardArray(4,16,1);
  tetris::Location loc = tetris::Location(200,720);
  REQUIRE(board.DetectLeftwardCollision(6,loc));
}
TEST_CASE("Delete Possible Lines", "[board]") {
  tetris::Board board = tetris::Board();
  for (int i = 0; i < 10; i++) {
    board.SetBoardArray(i, 19, 1);
  }
  board.DeletePossibleLines();
  REQUIRE(board.GetBoardArray(4,19) == 0);
}
TEST_CASE("Testing Row Incrementer", "[location]") {
  tetris::Location loc = tetris::Location(0,0);
  loc.IncrementRow();
  REQUIRE(loc.Row() == 40);
}
TEST_CASE("Testing Row Decrementer", "[location]") {
  tetris::Location loc = tetris::Location(80,0);
  loc.DecrementRow();
  REQUIRE(loc.Row() == 40);
}
TEST_CASE("Testing Column Incrementer", "[location]") {
  tetris::Location loc = tetris::Location(0,0);
  loc.IncrementCol();
  REQUIRE(loc.Col() == 40);
}
