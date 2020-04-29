// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/app/App.h>
#include<mylibrary/location.h>
#include<cinder/gl/gl.h>
#include <cinder/Rand.h>
#include<cinder/audio/audio.h>
#include<mylibrary/tetrominos.h>
#include <string>

namespace myapp {
using cinder::app::KeyEvent;
const char kDbPath[] = "tetris.db";

#if defined(CINDER_COCOA_TOUCH)
const char kNormalFont[] = "Arial";
const char kBoldFont[] = "Arial-BoldMT";
const char kDifferentFont[] = "AmericanTypewriter";
#elif defined(CINDER_LINUX)
const char kNormalFont[] = "Arial Unicode MS";
const char kBoldFont[] = "Arial Unicode MS";
const char kDifferentFont[] = "Purisa";
#else
const char kNormalFont[] = "Arial";
const char kBoldFont[] = "Arial Bold";
const char kDifferentFont[] = "Papyrus";
#endif

using cinder::app::KeyEvent;
using cinder::Color;
using cinder::ColorA;
using cinder::TextBox;
MyApp::MyApp() :
    leader_board_{cinder::app::getAssetPath(kDbPath).string()},
    randInt{cinder::Rand::randInt(0, 7)},
    matrixOccupied{},
    linesCleared{0},
    score{0},
    level{1},
    linesClearedTotal{0}
    {}

void MyApp::setup() {
  randInt = cinder::Rand::randInt(0, 7);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 20; j++) {
      matrixOccupied[i][j] = 0;
    }
  }
  cinder::audio::SourceFileRef sourceFile = cinder::audio::load( cinder::app::loadAsset( "tetris.mp3" ) );
  themeSong = cinder::audio::Voice::create( sourceFile );
  if (!themeSong->isPlaying()) {
    themeSong->start();
  }
}


void MyApp::update() {
  if (isBottom) {
    randInt = cinder::Rand::randInt(0, 7);
    loc = mylibrary::Location(0, 0.0);
    isBottom = false;
  }
  if (isCollided) {
    randInt = cinder::Rand::randInt(0, 7);
    loc = mylibrary::Location(0, 0.0);
    isCollided = false;
  }
  const auto time = std::chrono::system_clock::now();
  using std::chrono::milliseconds;
  //Elapsed time is the time from the last time the food changed colour
  long elapsed_time =
      std::chrono::duration_cast<milliseconds>(time - last_time_)
          .count();
  //Converts milliseconds to seconds
  elapsed_time /= 1000.0;
  long dropDelay = long(2.0) - (0.1 * level);
  if (elapsed_time >= dropDelay) {
    DownwardMovement();
    last_time_ = time;
  }
  DeletePossibleLines();
  if (linesCleared == 1) {
    score += (100 * level);
    cinder::audio::SourceFileRef sourceFile = cinder::audio::load( cinder::app::loadAsset( "single_line.wav" ) );
    singleSound = cinder::audio::Voice::create( sourceFile );
    if (!singleSound->isPlaying()) {
      singleSound->start();
    }
  } else if (linesCleared == 2) {
    score += (400 * level);
    cinder::audio::SourceFileRef sourceFile = cinder::audio::load( cinder::app::loadAsset( "double_line.wav" ) );
    doubleSound = cinder::audio::Voice::create( sourceFile );
    if (!doubleSound->isPlaying()) {
      doubleSound->start();
    }
  } else if (linesCleared == 3) {
    score += (900 * level);
    cinder::audio::SourceFileRef sourceFile = cinder::audio::load( cinder::app::loadAsset( "triple_line.wav" ) );
    tripleSound = cinder::audio::Voice::create( sourceFile );
    if (!tripleSound->isPlaying()) {
      tripleSound->start();
    }
  } else if (linesCleared == 4) {
    score += (2500 * level);
    cinder::audio::SourceFileRef sourceFile = cinder::audio::load(cinder::app::loadAsset("tetris_cleared.wav"));
    tetrisSound = cinder::audio::Voice::create(sourceFile);
    if (!tetrisSound->isPlaying()) {
      tetrisSound->start();
    }
  }
  if (!themeSong->isPlaying()) {
    themeSong->start();
  }
  linesCleared = 0;
  if (linesClearedTotal % 30 == 0 && (linesClearedTotal != 0)) {
    level += 1;
  }

}
int CountOccupiedMatrix(int n[10][20]) {
  int c = 0;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 20; j++) {
      if (n[i][j] == 1) {
        c += 1;
      }
    }
  }
  return c;
}
void MyApp::draw() {
  cinder::gl::clear();
  DrawOccupied();
  if (!isCollided) {
    DrawCurrent();
  }
  DrawScore();
  DrawLevel();
  DrawLinesCleared();
}

void PrintText(const std::string& text, const Color& color, const cinder::ivec2& size,
               const cinder::vec2& loc) {
  cinder::gl::color(color);

  auto box = cinder::TextBox()
      .alignment(cinder::TextBox::CENTER)
      .font(cinder::Font(kNormalFont, 30))
      .size(size)
      .color(color)
      .backgroundColor(ColorA(0, 0, 0, 0))
      .text(text);

  const auto box_size = box.getSize();
  const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
}

void MyApp::DrawScore() const {
  const std::string scoreText = "Score :" + std::to_string(score);
  const Color color = {1, 1, 1};
  const cinder::ivec2 size = {120, 50};
  const cinder::vec2 location = {500, 500};

  PrintText(scoreText, color, size, location);
}
void MyApp::DrawLevel() const {
  const std::string scoreText = "Level :" + std::to_string(level);
  const Color color = {1, 1, 1};
  const cinder::ivec2 size = {120, 50};
  const cinder::vec2 location = {500, 600};

  PrintText(scoreText, color, size, location);
}
void MyApp::DrawLinesCleared() const {
  const std::string scoreText = "Lines :" + std::to_string(linesClearedTotal);
  const Color color = {1, 1, 1};
  const cinder::ivec2 size = {120, 50};
  const cinder::vec2 location = {500, 700};

  PrintText(scoreText, color, size, location);
}

void MyApp::DrawCurrent() {
  int xBlockSize = 4;
  int yBlockSize = 4;
  int tile_size_ = 40;

  for (int x = 0; x < xBlockSize; x++) {
    for (int y = 0; y < yBlockSize; y++) {
      if (tetromino_.GetTetrominoType(randInt, x, y) == 1) {
        int drawRow = loc.Row() + (tile_size_ * x);
        int drawCol = loc.Col() + (tile_size_ * y);
        int matrixRow = drawRow / 40;
        int matrixCol = drawCol / 40;
        cinder::gl::color(tetromino_.GetColorType(randInt, 0),
                          tetromino_.GetColorType(randInt, 1),
                          tetromino_.GetColorType(randInt, 2));
        cinder::gl::drawSolidRect(cinder::Rectf(drawRow, drawCol, drawRow + 40, drawCol + 40));
        if (matrixOccupied[matrixRow][matrixCol] != 0) {
          isCollided = true;
        }
      } else {
        int drawRow = loc.Row() + (tile_size_ * x);
        int drawCol = loc.Col() + (tile_size_ * y);
        int matrixRow = drawRow / 40;
        int matrixCol = drawCol / 40;
        if (matrixOccupied[matrixRow][matrixCol] == 0) {
          cinder::gl::color(0, 0, 0);
          cinder::gl::drawSolidRect(cinder::Rectf(drawRow, drawCol, drawRow + 40, drawCol + 40));
        } else {
          cinder::gl::color(tetromino_.GetColorType(randInt, 0),
                            tetromino_.GetColorType(randInt, 1),
                            tetromino_.GetColorType(randInt, 2));
          cinder::gl::drawSolidRect(cinder::Rectf(drawRow, drawCol, drawRow + 40, drawCol + 40));
        }
      }
    }
  }
}
void MyApp::DrawOccupied() {
  int boardHeight = 20;
  int boardWidth = 10;
  int tile_size_ = 40;
  //cinder::gl::clear();
  for (int x = 0; x < boardWidth; x++) {
    for (int y = 0; y < boardHeight; y++) {
      if (matrixOccupied[x][y] != 0) {
        int pType = matrixOccupied[x][y] - 1;
        int drawRow2 = (tile_size_ * x);
        int drawCol2 = (tile_size_ * y);
        cinder::gl::color(tetromino_.GetColorType(pType, 0),
                          tetromino_.GetColorType(pType, 1),
                          tetromino_.GetColorType(pType, 2));
        cinder::gl::drawSolidRect(cinder::Rectf(drawRow2, drawCol2, drawRow2 + 40, drawCol2 + 40));
      }
    }
  }
}
bool MyApp::DetectDownwardCollision(int tetromino) {
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      if (tetromino_.GetTetrominoType(tetromino, x, y) == 1) {
        int toCheckCol = (loc.Col() / 40) + y + 1;
        int toCheckRow = (loc.Row() / 40) + x;
        if (matrixOccupied[toCheckRow][toCheckCol] != 0) {
          return true;
        }
      }
    }
  }
  return false;
}
bool MyApp::DetectLeftwardCollision(int tetromino) {
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      if (tetromino_.GetTetrominoType(tetromino, x, y) == 1) {
        int toCheckCol = (loc.Col() / 40) + y;
        int toCheckRow = (loc.Row() / 40) + x - 1;
        if (matrixOccupied[toCheckRow][toCheckCol] != 0) {
          return true;
        }
      }
    }
  }
  return false;
}
bool MyApp::DetectRightwardCollision(int tetromino) {
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      if (tetromino_.GetTetrominoType(tetromino, x, y) == 1) {
        int toCheckCol = (loc.Col() / 40) + y;
        int toCheckRow = (loc.Row() / 40) + x + 1;
        if (matrixOccupied[toCheckRow][toCheckCol] != 0) {
          return true;
        }
      }
    }
  }
  return false;
}
int MyApp::GetSouthernmostPoint(int tetromino) {
  int southernmost = 0;
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      if (tetromino_.GetTetrominoType(tetromino, x, y) == 1) {
        if (y > southernmost) {
          southernmost = y;
        }
      }
    }
  }
  return southernmost;
}
int MyApp::GetWestmostPoint(int tetromino) {
  int westmost = 3;
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      if (tetromino_.GetTetrominoType(tetromino, x, y) == 1) {
        if (x < westmost) {
          westmost = x;
        }
      }
    }
  }
  return westmost;
}
int MyApp::GetEastmostPoint(int tetromino) {
  int eastmost = 0;
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      if (tetromino_.GetTetrominoType(tetromino, x, y) == 1) {
        if (x > eastmost) {
          eastmost = x;
        }
      }
    }
  }
  return eastmost;
}
void MyApp::DownwardMovement() {
  int tile_size = 40;
  int southernmost = GetSouthernmostPoint(randInt);
  int kLimit = 800 - ((southernmost + 1) * tile_size);
  if (loc.Col() < kLimit && (!DetectDownwardCollision(randInt))) {
    loc.col_ += 40;
  } else if (loc.Col() >= kLimit) {
    isBottom = true;
    for (int x = 0; x < 4; x++) {
      for (int y = 0; y < 4; y++) {
        if (tetromino_.GetTetrominoType(randInt, x, y) == 1) {
          int RowOccupied = loc.Row() / 40 + x;
          int ColOccupied = loc.Col() / 40 + y;
          matrixOccupied[RowOccupied][ColOccupied] = randInt + 1;
        }
      }
    }
  } else if (DetectDownwardCollision(randInt)) {
    isCollided = true;
    for (int x = 0; x < 4; x++) {
      for (int y = 0; y < 4; y++) {
        if (tetromino_.GetTetrominoType(randInt, x, y) == 1) {
          int RowOccupied = loc.Row() / 40 + x;
          int ColOccupied = loc.Col() / 40 + y;
          matrixOccupied[RowOccupied][ColOccupied] = randInt + 1;
        }
      }
    }

  }
}

int MyApp::countLines() {
  int count_per_line = 0;
  int count_lines = 0;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 20; j++) {
      if (matrixOccupied[i][j] != 0) {
        count_per_line += 1;
      }
    }
    if (count_per_line == 20) {
      count_lines += 1;
      fullLines[i] = 1;
    }
  }
  return count_lines;
}

void MyApp::deleteLine(int pY) {
  int BOARD_WIDTH = 10;
  for (int j = pY; j > 0; j--)
  {
    for (int i = 0; i < BOARD_WIDTH; i++)
    {
      matrixOccupied[i][j] = matrixOccupied[i][j-1];
    }
  }
}
void MyApp::DeletePossibleLines ()
{
  int BOARD_HEIGHT = 20;
  int BOARD_WIDTH = 10;
  for (int j = 0; j < BOARD_HEIGHT; j++)
  {
    int i = 0;
    while (i < BOARD_WIDTH)
    {
      if (matrixOccupied[i][j] == 0) break;
      i++;
    }
    if (i == BOARD_WIDTH) {
      deleteLine (j);
      linesCleared++;
      linesClearedTotal += 1;
    }

  }
}
void MyApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_DOWN: {
      DownwardMovement();
      break;
    }
    case KeyEvent::KEY_UP: {
      tetromino_.RotateTetromino(randInt);
      int tile_size = 40;
      int eastmost = GetEastmostPoint(randInt);
      int westmost = GetWestmostPoint(randInt);
      int kLimitRight = 400 - ((eastmost + 1) * tile_size);
      int kLimitLeft = (0 - ((westmost) * tile_size));
      if (loc.Row() > kLimitRight || loc.Row() < kLimitLeft) {
        tetromino_.RotateTetrominoCounterClockwise(randInt);
      }
      break;
    }
    case KeyEvent::KEY_RIGHT: {
      int tile_size = 40;
      int eastmost = GetEastmostPoint(randInt);
      int kLimit = 400 - ((eastmost + 1) * tile_size);
      if (loc.Row() < kLimit && (!DetectRightwardCollision(randInt))) {
        loc.row_ += tile_size;
      }
      break;
    }
    case KeyEvent::KEY_LEFT: {
      int tile_size = 40;
      int westmost = GetWestmostPoint(randInt);
      int kLimit = (0 - ((westmost) * tile_size));
      if (loc.Row() > kLimit && (!DetectLeftwardCollision(randInt))) {
        loc.row_ -= tile_size;
      } else if (loc.Row() >= kLimit) {
        break;
      } else if (DetectLeftwardCollision(randInt)) {
        isCollided = true;
        for (int x = 0; x < 4; x++) {
          for (int y = 0; y < 4; y++) {
            if (tetromino_.GetTetrominoType(randInt, x, y) == 1) {
              int RowOccupied = loc.Row() / 40 + x;
              int ColOccupied = loc.Col() / 40 + y;
              matrixOccupied[RowOccupied][ColOccupied] = randInt + 1;
            }
          }
        }
      }
      break;
    }
  }
}


// namespace myapp
}