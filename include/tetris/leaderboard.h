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
  // Creates a new leaderboard table if it doesn't already exist.
  explicit LeaderBoard(const std::string& db_path);
  // Adds a player to the leaderboard.
  void AddScoreToLeaderBoard(const Player&);
  // Returns a list of the players with the highest scores, in decreasing order.
  // The size of the list should be no greater than `limit`.
  std::vector<Player> RetrieveHighScores(const size_t limit);
  // Returns a list of the players with the highest scores, in decreasing order,
  // that have the same `name` as the input player name.
  // The size of the list should be no greater than `limit`.
  std::vector<Player> RetrieveHighScores(const Player&, const size_t limit);
 public:
  sqlite::database db_;
};
}

#endif //FINALPROJECT_INCLUDE_TETRIS_LEADERBOARD_H_
