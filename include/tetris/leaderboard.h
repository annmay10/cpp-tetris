//
// Created by Annmay on 22/04/20.
//

#ifndef FINALPROJECT_INCLUDE_TETRIS_LEADERBOARD_H_
#define FINALPROJECT_INCLUDE_TETRIS_LEADERBOARD_H_
#include "leaderboard.h"
#include<tetris/player.h>
#include "../cmake-build-debug/_deps/sqlite-modern-cpp-src/hdr/sqlite_modern_cpp.h"
#include<string>
#include <vector>
namespace tetris {
class LeaderBoard {
 public:
  explicit LeaderBoard(const std::string& db_path);
  void AddScoreToLeaderBoard(const Player&);
  std::vector<Player> RetrieveHighScores(const size_t limit);
  std::vector<Player> RetrieveHighScores(const Player&, const size_t limit);
 public:
  sqlite::database db_;
};
}

#endif //FINALPROJECT_INCLUDE_TETRIS_LEADERBOARD_H_
