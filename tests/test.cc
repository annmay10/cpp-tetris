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
TEST_CASE("Check clockwise rotation - N", "[tetromino]") {
  tetris::Tetromino tetromino;
  tetromino.RotateTetromino(4);
  REQUIRE(tetromino.GetTetrominoType(4, 0, 1) == 1);
}
TEST_CASE("Checking counter-clockwise rotation - N", "[tetromino]") {
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



