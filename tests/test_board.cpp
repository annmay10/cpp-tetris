//
// Created by Annmay on 06/05/20.
//

#include <catch2/catch.hpp>
#include <cinder/Rand.h>
#include <tetris/tetrominos.h>
#include <tetris/board.h>

TEST_CASE("Check game end", "[board]") {
  tetris::Board board = tetris::Board();
  board.SetBoardArray(4,0,1);
  REQUIRE(board.CheckGameEnd());
}
//Checks Downward Collision dynamics between a sleeping I-block and T-block
TEST_CASE("Check downward collision", "[board]") {
  tetris::Board board = tetris::Board();
  board.SetBoardArray(4,19,1);
  board.SetBoardArray(3,19,1);
  board.SetBoardArray(2,19,1);
  board.SetBoardArray(1,19,1);
  tetris::Location loc = tetris::Location(40,680);
  REQUIRE(board.DetectDownwardCollision(6,loc));
}
//Checks Rightward Collision dynamics between a standing I-block and T-block
TEST_CASE("Check rightward collision", "[board]") {
  tetris::Board board = tetris::Board();
  board.SetBoardArray(4,19,1);
  board.SetBoardArray(4,18,1);
  board.SetBoardArray(4,17,1);
  board.SetBoardArray(4,16,1);
  tetris::Location loc = tetris::Location(80,720);
  REQUIRE(board.DetectRightwardCollision(6,loc));
}
//Checks Leftward Collision dynamics between a standing I-block and T-block
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
//A tricky case for downward collision involving one O-block and an N-block
TEST_CASE("Check Downward collision - tricky", "[board]") {
  tetris::Board board = tetris::Board();
  for (int i = 0; i < 9; i++) {
    board.SetBoardArray(i, 19, 1);
  }
  board.SetBoardArray(1,18,1);
  board.SetBoardArray(2,18,1);
  board.SetBoardArray(1,17,1);
  board.SetBoardArray(2,17,1);
  tetris::Location loc = tetris::Location(600, 80);
  REQUIRE(board.DetectDownwardCollision(4, loc));
}
