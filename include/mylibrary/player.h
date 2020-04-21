//
// Created by Annmay on 22/04/20.
//

#ifndef FINALPROJECT_INCLUDE_MYLIBRARY_PLAYER_H_
#define FINALPROJECT_INCLUDE_MYLIBRARY_PLAYER_H_
#include <string>
namespace mylibrary {

struct Player {
  Player(const std::string &name, size_t score) : name(name), score(score) {}
  std::string name;
  size_t score;
};
}
#endif //FINALPROJECT_INCLUDE_MYLIBRARY_PLAYER_H_
