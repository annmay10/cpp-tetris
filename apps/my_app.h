// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include<cinder/Rand.h>
#include<tetris/leaderboard.h>
#include <tetris/tetrominos.h>
#include <tetris/location.h>
#include<cinder/audio/audio.h>
#include<tetris/board.h>

namespace tetrisapp {
enum class GameState {
  kMenu,
  kPlaying,
  kGameOver,
};
class TetrisApp : public cinder::app::App {
 public:
  TetrisApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
 private:
  void SetUpMusic();
  void DownwardMovement();
  void DrawMenu() const;
  void DrawCurrent();
  void DrawOccupied();
  void DrawScore() const;
  void DrawLevel() const;
  void DrawLinesCleared() const;
  void DrawBackground() const;
  void DrawNext();
  void DrawGameOver();
  void PlayMusic();
  void HardDrop();
  std::chrono::time_point<std::chrono::system_clock> last_time_;
  tetris::LeaderBoard leader_board_;
  tetris::Tetromino tetromino_;
  tetris::Location location_ = tetris::Location(80.0,0.0);
  tetris::Board board_;
  const std::string player_name_;
  GameState state_;
  int current_;
  int next_;
  bool is_bottom_ = false;
  bool is_collided_ = false;
  bool flag_;
  std::vector<tetris::Player> top_players_;
  std::vector<tetris::Player> current_player_scores_;
  size_t level_;
  cinder::audio::VoiceRef theme_song_;
  cinder::audio::VoiceRef single_sound_;
  cinder::audio::VoiceRef double_sound_;
  cinder::audio::VoiceRef triple_sound_;
  cinder::audio::VoiceRef tetris_sound_;
  cinder::audio::VoiceRef level_sound_;

};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
