// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include<cinder/gl/gl.h>
#include <cinder/Rand.h>


namespace myapp {
using cinder::app::KeyEvent;
const char kDbPath[] = "tetris.db";

using cinder::app::KeyEvent;

MyApp::MyApp() :
    leader_board_{cinder::app::getAssetPath(kDbPath).string()}
    { }

void MyApp::setup() { }

void MyApp::update() { }

void MyApp::draw() {
  int randInt = cinder::Rand::randInt(0,7);
  int xBlockSize = 4;
  int yBlockSize = 4;
  int tile_size = 40;
  if (randInt == 0) {
    cinder::gl::color(1,0,0);
    cinder::gl::drawSolidRect(cinder::Rectf(0.0,0.0,40.0,40.0));
    cinder::gl::drawSolidRect(cinder::Rectf(0.0,40.0,40.0,80.0));
    cinder::gl::drawSolidRect(cinder::Rectf(0.0,80.0,40.0,120.0));
    cinder::gl::drawSolidRect(cinder::Rectf(0.0,120.0,40.0,160.0));
  } else if (randInt == 1) {
    cinder::gl::color(0,0,1);
    cinder::gl::drawSolidRect(cinder::Rectf(120.0,40.0,160.0,80.0));
    cinder::gl::drawSolidRect(cinder::Rectf(80.0,40.0,120.0,80.0));
    cinder::gl::drawSolidRect(cinder::Rectf(80.0,80.0,120.0,120.0));
    cinder::gl::drawSolidRect(cinder::Rectf(80.0,120.0,120.0,160.0));
  } else if (randInt == 2) {
    cinder::gl::color(0,1,0);
    cinder::gl::drawSolidRect(cinder::Rectf(40.0,240.0,80.0,280.0));
    cinder::gl::drawSolidRect(cinder::Rectf(80.0,240.0,120.0,280.0));
    cinder::gl::drawSolidRect(cinder::Rectf(80.0,280.0,120.0,320.0));
    cinder::gl::drawSolidRect(cinder::Rectf(80.0,320.0,120.0,360.0));
  } else if (randInt == 3) {
    cinder::gl::color(1,1,0);
    cinder::gl::drawSolidRect(cinder::Rectf(160.0,240.0,200.0,280.0));
    cinder::gl::drawSolidRect(cinder::Rectf(200.0,240.0,240.0,280.0));
    cinder::gl::drawSolidRect(cinder::Rectf(160.0,280.0,200.0,320.0));
    cinder::gl::drawSolidRect(cinder::Rectf(200.0,280.0,240.0,320.0));
  } else if (randInt == 4) {
    cinder::gl::color(0,1,1);
    cinder::gl::drawSolidRect(cinder::Rectf(240.0,80.0,280.0,120.0));
    cinder::gl::drawSolidRect(cinder::Rectf(280.0,80.0,320.0,120.0));
    cinder::gl::drawSolidRect(cinder::Rectf(280.0,40.0,320.0,80.0));
    cinder::gl::drawSolidRect(cinder::Rectf(320.0,40.0,360.0,80.0));
  } else if (randInt == 5) {
    cinder::gl::color(1,0,1);
    cinder::gl::drawSolidRect(cinder::Rectf(0.0,360.0,40.0,400.0));
    cinder::gl::drawSolidRect(cinder::Rectf(40.0,360.0,80.0,400.0));
    cinder::gl::drawSolidRect(cinder::Rectf(40.0,400.0,80.0,440.0));
    cinder::gl::drawSolidRect(cinder::Rectf(80.0,400.0,120.0,440.0));
  } else if (randInt == 6) {
    cinder::gl::color(1,1,1);
    cinder::gl::drawSolidRect(cinder::Rectf(240.0,320.0,280.0,360.0));
    cinder::gl::drawSolidRect(cinder::Rectf(200.0,360.0,240.0,400.0));
    cinder::gl::drawSolidRect(cinder::Rectf(240.0,360.0,280.0,400.0));
    cinder::gl::drawSolidRect(cinder::Rectf(280.0,360.0,320.0,400.0));
  }
}

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
