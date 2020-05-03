// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include<cinder/Rand.h>
#include<mylibrary/leaderboard.h>
#include <mylibrary/tetrominos.h>
#include <mylibrary/location.h>
#include<cinder/audio/audio.h>
#include<mylibrary/board.h>

namespace myapp {
enum class GameState {
  kMenu,
  kPlaying,
  kGameOver,
};
class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
 private:
  void DownwardMovement();
  void DrawOccupied();
  void DrawCurrent();
  void DrawScore() const;
  void DrawLevel() const;
  void DrawLinesCleared() const;
  void DrawNext();
  void DrawGameOver();
  void DrawBackground();
  void DrawMenu();
  void UpdateScore();
  void HardDrop();
  int current;
  int next;
  bool isBottom = false;
  bool isCollided = false;
  GameState state_;
  bool flag;
  std::vector<mylibrary::Player> top_players_;
  std::vector<mylibrary::Player> current_player_scores_;
  int score;
  size_t level;
  const std::string player_name_;
  cinder::audio::VoiceRef themeSong;
  cinder::audio::VoiceRef singleSound;
  cinder::audio::VoiceRef doubleSound;
  cinder::audio::VoiceRef tripleSound;
  cinder::audio::VoiceRef tetrisSound;
  cinder::audio::VoiceRef levelSound;
  std::chrono::time_point<std::chrono::system_clock> last_time_;
  mylibrary::LeaderBoard leader_board_;
  mylibrary::Tetromino tetromino_;
  mylibrary::Location loc = mylibrary::Location(80.0,0.0);
  mylibrary::Board board_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
