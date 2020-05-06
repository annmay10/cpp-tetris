//
// Created by Annmay on 06/05/20.
//
#include <catch2/catch.hpp>
#include <tetris/location.h>

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
