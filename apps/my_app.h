// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include<cinder/Rand.h>
#include<mylibrary/leaderboard.h>
#include <mylibrary/tetrominos.h>
#include <mylibrary/location.h>

namespace myapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
 private:
  bool DetectDownwardCollision(int tetromino);
  bool DetectLeftwardCollision(int tetromino);
  bool DetectRightwardCollision(int tetromino);
  void DownwardMovement();
  void DrawOccupied();
  void DrawCurrent();
  int GetWestmostPoint(int tetromino);
  int GetEastmostPoint(int tetromino);
  int GetSouthernmostPoint(int tetromino);
  int randInt;
  bool isBottom = false;
  bool isCollided = false;
  bool isHitSide;
  int matrixOccupied[10][20];
  std::chrono::time_point<std::chrono::system_clock> last_time_;
  mylibrary::LeaderBoard leader_board_;
  mylibrary::Tetromino tetromino_;
  mylibrary::Location loc = mylibrary::Location(80.0,0.0);
  mylibrary::Location loc2 = mylibrary::Location(80.0,0.0);
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
