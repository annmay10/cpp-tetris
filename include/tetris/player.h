//
// Created by Annmay on 22/04/20.
//

#ifndef FINALPROJECT_INCLUDE_TETRIS_PLAYER_H_
#define FINALPROJECT_INCLUDE_TETRIS_PLAYER_H_
#include <string>
namespace tetris {

struct Player {
  Player(const std::string &name, size_t score) : name_(name), score_(score) {}
  std::string name_;
  size_t score_;
};
}
#endif //FINALPROJECT_INCLUDE_TETRIS_PLAYER_H_
