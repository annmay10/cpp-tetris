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
#include<gflags/gflags.h>

namespace myapp {
using cinder::app::KeyEvent;
const char kDbPath[] = "tetris.db";
const size_t kLimit = 3;

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

DECLARE_uint32(level);
DECLARE_string(name);

MyApp::MyApp() :
    leader_board_{cinder::app::getAssetPath(kDbPath).string()},
    current{cinder::Rand::randInt(0, 7)},
    next{cinder::Rand::randInt(0, 7)},
    score{0},
    level{FLAGS_level},
    player_name_{FLAGS_name},
    state_{GameState::kMenu},
    board_{mylibrary::Board()}
    {}

void MyApp::setup() {
  cinder::Rand::randomize();
  current = cinder::Rand::randInt(0, 7);
  next = cinder::Rand::randInt(0,7);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 20; j++) {
      board_.SetBoardArray(i, j, 0);
    }
  }
  cinder::audio::SourceFileRef sourceFile = cinder::audio::load( cinder::app::loadAsset( "tetris.mp3" ) );
  themeSong = cinder::audio::Voice::create( sourceFile );
  if (!themeSong->isPlaying()) {
    themeSong->setVolume(0.0);
    themeSong->start();
  }
}

void MyApp::update() {
  if (state_ == GameState::kGameOver) {
    if (top_players_.empty()) {
      leader_board_.AddScoreToLeaderBoard({player_name_, static_cast<size_t>(score)});
      //Returns a vector of the highest scores of all players
      top_players_ = leader_board_.RetrieveHighScores(kLimit);
      //Initialises the current player
      mylibrary::Player current_player = mylibrary::Player(player_name_, score);
      //Returns a vector of the scores of the current player
      current_player_scores_ = leader_board_.RetrieveHighScores(current_player, kLimit);
      // It is crucial the this vector be populated, given that `kLimit` > 0.
      assert(!top_players_.empty());
    }
    return;
  }
  if (isBottom || isCollided) {
    current = next;
    cinder::Rand::randomize();
    next = cinder::Rand::randInt(0,7);
    loc = mylibrary::Location(80.0, 0.0);
    isBottom = false;
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
  long dropDelay = long(2.0) - (0.2 * level);
  if (elapsed_time >= dropDelay && state_ == GameState::kPlaying) {
    DownwardMovement();
    last_time_ = time;
  }
  board_.DeletePossibleLines();
  UpdateScore();
  if (!themeSong->isPlaying()) {
    themeSong->start();
  }
  if ((board_.GetLinesClearedTotal() % 30) != 0) {
    flag = false;
  }
  if (board_.GetLinesClearedTotal() % 30 == 0 && (board_.GetLinesClearedTotal() != 0) && !flag) {
    if (level < 20) {
      level += 1;
      flag = true;
    }
  }
  if (board_.CheckGameEnd()) {
    state_ = GameState::kGameOver;
  }

}

void MyApp::draw() {
  if (state_ == GameState::kMenu) {
    DrawMenu();
  } else if (state_ == GameState::kPlaying) {
    cinder::gl::clear();
    DrawOccupied();
    if (!isCollided) {
      DrawCurrent();
    }
    DrawBackground();
    DrawNext();
    DrawScore();
    DrawLevel();
    DrawLinesCleared();
  } else if (state_ == GameState::kGameOver) {
      cinder::gl::clear(Color(1, 0, 0));
      DrawGameOver();
  }

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
  const cinder::ivec2 size = {200, 50};
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
  const std::string scoreText = "Lines :" + std::to_string(board_.GetLinesClearedTotal());
  const Color color = {1, 1, 1};
  const cinder::ivec2 size = {200, 50};
  const cinder::vec2 location = {500, 700};

  PrintText(scoreText, color, size, location);
}
void MyApp::DrawBackground() {
  cinder::gl::color(1,0,0);
  cinder::gl::drawSolidRect(cinder::Rectf(400,0,600,800));
}
void MyApp::DrawNext() {
  int xBlockSize = 4;
  int yBlockSize = 4;
  int tile_size_ = 40;

  for (int x = 0; x < xBlockSize; x++) {
    for (int y = 0; y < yBlockSize; y++) {
      if (tetromino_.GetTetrominoType(next, x, y) == 1) {
        int drawRow = 410 + (tile_size_ * x);
        int drawCol = 200 + (tile_size_ * y);
        cinder::gl::color(tetromino_.GetColorType(next, 0),
                          tetromino_.GetColorType(next, 1),
                          tetromino_.GetColorType(next, 2));
        cinder::gl::drawSolidRect(cinder::Rectf(drawRow, drawCol, drawRow + 40, drawCol + 40));
      } else {
        int drawRow = 410 + (tile_size_ * x);
        int drawCol = 200 + (tile_size_ * y);
        cinder::gl::color(0,0,0);
        cinder::gl::drawSolidRect(cinder::Rectf(drawRow, drawCol, drawRow + 40, drawCol + 40));
      }
    }
  }
  const std::string scoreText = "NEXT";
  const Color color = {1, 1, 1};
  const cinder::ivec2 size = {200, 50};
  const cinder::vec2 location = {500, 170};

  PrintText(scoreText, color, size, location);
}
void MyApp::DrawCurrent() {
  int xBlockSize = 4;
  int yBlockSize = 4;
  int tile_size_ = 40;

  for (int x = 0; x < xBlockSize; x++) {
    for (int y = 0; y < yBlockSize; y++) {
      if (tetromino_.GetTetrominoType(current, x, y) == 1) {
        int drawRow = loc.Row() + (tile_size_ * x);
        int drawCol = loc.Col() + (tile_size_ * y);
        int matrixRow = drawRow / 40;
        int matrixCol = drawCol / 40;
        cinder::gl::color(tetromino_.GetColorType(current, 0),
                          tetromino_.GetColorType(current, 1),
                          tetromino_.GetColorType(current, 2));
        cinder::gl::drawSolidRect(cinder::Rectf(drawRow, drawCol, drawRow + 40, drawCol + 40));
      } else {
        int drawRow = loc.Row() + (tile_size_ * x);
        int drawCol = loc.Col() + (tile_size_ * y);
        int matrixRow = drawRow / 40;
        int matrixCol = drawCol / 40;
        if (board_.GetBoardArray(matrixRow, matrixCol) == 0) {
          cinder::gl::color(0, 0, 0);
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
      if (board_.GetBoardArray(x, y) != 0) {
        int pType = board_.GetBoardArray(x, y) - 1;
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
void MyApp::DrawGameOver() {
  // Lazily print.
  //if (printed_game_over_) return;
  //if (top_players_.empty()) return;

  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 50};
  const Color color = Color::black();

  size_t row = 0;
  PrintText("Game Over :(", color, size, center);
  for (const mylibrary::Player& player : top_players_) {
    std::stringstream ss;
    ss << player.name << " - " << player.score;
    PrintText(ss.str(), color, size, {center.x, center.y + (++row) * 50});
  }
  std::stringstream ss;
  ss << "Your scores \n";
  PrintText(ss.str(), color, size, {center.x, center.y + (++row) * 50});
  for (const mylibrary::Player& player : current_player_scores_) {
    std::stringstream ss;
    ss << player.name << " - " << player.score;
    PrintText(ss.str(), color, size, {center.x, center.y + (++row) * 50});
  }
}
void MyApp::DrawMenu() {
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 100};
  const Color color = Color::white();
  std::stringstream ss;
  ss << "Welcome to tetris  \n Press Enter to play";
  PrintText(ss.str(), color, size, {center.x, center.y});
}
void MyApp::UpdateScore() {
  if (board_.GetLinesCleared() == 1) {
    score += (100 * level);
    cinder::audio::SourceFileRef sourceFile = cinder::audio::load( cinder::app::loadAsset( "single_line.wav" ) );
    singleSound = cinder::audio::Voice::create( sourceFile );
    if (!singleSound->isPlaying()) {
      singleSound->start();
    }
    board_.SetLinesCleared(0);
  } else if (board_.GetLinesCleared() == 2) {
    score += (400 * level);
    cinder::audio::SourceFileRef sourceFile = cinder::audio::load( cinder::app::loadAsset( "double_line.wav" ) );
    doubleSound = cinder::audio::Voice::create( sourceFile );
    if (!doubleSound->isPlaying()) {
      doubleSound->start();
    }
    board_.SetLinesCleared(0);
  } else if (board_.GetLinesCleared() == 3) {
    score += (900 * level);
    cinder::audio::SourceFileRef sourceFile = cinder::audio::load( cinder::app::loadAsset( "triple_line.wav" ) );
    tripleSound = cinder::audio::Voice::create( sourceFile );
    if (!tripleSound->isPlaying()) {
      tripleSound->start();
    }
    board_.SetLinesCleared(0);
  } else if (board_.GetLinesCleared() == 4) {
    score += (2500 * level);
    cinder::audio::SourceFileRef sourceFile = cinder::audio::load(cinder::app::loadAsset("tetris_cleared.wav"));
    tetrisSound = cinder::audio::Voice::create(sourceFile);
    if (!tetrisSound->isPlaying()) {
      tetrisSound->start();
    }
    board_.SetLinesCleared(0);
  }
}

void MyApp::DownwardMovement() {
  int tile_size = 40;
  int southernmost = tetromino_.GetSouthernmostPoint(current);
  int kLimit = 800 - ((southernmost + 1) * tile_size);
  if (loc.Col() < kLimit && (!board_.DetectDownwardCollision(current, loc))) {
    loc.col_ += 40;
  } else if (loc.Col() >= kLimit) {
    isBottom = true;
    for (int x = 0; x < 4; x++) {
      for (int y = 0; y < 4; y++) {
        if (tetromino_.GetTetrominoType(current, x, y) == 1) {
          int RowOccupied = loc.Row() / 40 + x;
          int ColOccupied = loc.Col() / 40 + y;
          board_.SetBoardArray(RowOccupied, ColOccupied, (current + 1));
        }
      }
    }
  } else if (board_.DetectDownwardCollision(current, loc)) {
    isCollided = true;
    for (int x = 0; x < 4; x++) {
      for (int y = 0; y < 4; y++) {
        if (tetromino_.GetTetrominoType(current, x, y) == 1) {
          int RowOccupied = loc.Row() / 40 + x;
          int ColOccupied = loc.Col() / 40 + y;
          board_.SetBoardArray(RowOccupied, ColOccupied, (current + 1));
        }
      }
    }
  }
}
void MyApp::HardDrop() {
  int tile_size = 40;
  int southernmost = tetromino_.GetSouthernmostPoint(current);
  int kLimit = 800 - ((southernmost + 1) * tile_size);
  while(loc.Col() < kLimit && (!isCollided) && (!isBottom)) {
    DownwardMovement();
  }
}

void MyApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_DOWN: {
      DownwardMovement();
      break;
    }
    case KeyEvent::KEY_UP: {
      tetromino_.RotateTetromino(current);
      int tile_size = 40;
      int southernmost = tetromino_.GetSouthernmostPoint(current);
      int kLimitDown = 800 - ((southernmost + 1) * tile_size);
      int eastmost = tetromino_.GetEastmostPoint(current);
      int westmost = tetromino_.GetWestmostPoint(current);
      int kLimitRight = 400 - ((eastmost + 1) * tile_size);
      int kLimitLeft = (0 - ((westmost) * tile_size));
      if (loc.Row() > kLimitRight || loc.Row() < kLimitLeft || loc.Col() > kLimitDown) {
        tetromino_.RotateTetrominoCounterClockwise(current);
      }
      break;
    }
    case KeyEvent::KEY_RIGHT: {
      int tile_size = 40;
      int eastmost = tetromino_.GetEastmostPoint(current);
      int kLimit = 400 - ((eastmost + 1) * tile_size);
      if (loc.Row() < kLimit && (!board_.DetectRightwardCollision(current, loc))) {
        loc.row_ += tile_size;
      }
      break;
    }
    case KeyEvent::KEY_LEFT: {
      int tile_size = 40;
      int westmost = tetromino_.GetWestmostPoint(current);
      int kLimit = (0 - ((westmost) * tile_size));
      if (loc.Row() > kLimit && (!board_.DetectLeftwardCollision(current, loc))) {
        loc.row_ -= tile_size;
      }
      break;
    }
    case KeyEvent::KEY_SPACE: {
      HardDrop();
    }
    case KeyEvent::KEY_RETURN: {
      state_ = GameState::kPlaying;
    }
  }
}


// namespace myapp
}