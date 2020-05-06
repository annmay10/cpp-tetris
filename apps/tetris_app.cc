// Copyright (c) 2020 [Annmay Sharma3]. All rights reserved.

#include "tetris_app.h"
#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/app/App.h>
#include<tetris/location.h>
#include<cinder/gl/gl.h>
#include <cinder/Rand.h>
#include<cinder/audio/audio.h>
#include<tetris/tetrominos.h>
#include <string>
#include<gflags/gflags.h>

namespace tetrisapp {
using cinder::app::KeyEvent;
const char kDbPath[] = "tetris.db";
const size_t kLimit = 3;
cinder::gl::Texture2dRef menu_image;
const int kTileSize = 40;

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

TetrisApp::TetrisApp() :
    leader_board_{cinder::app::getAssetPath(kDbPath).string()},
    current_{cinder::Rand::randInt(0, 7)},
    next_{cinder::Rand::randInt(0, 7)},
    level_{FLAGS_level},
    player_name_{FLAGS_name},
    state_{GameState::kMenu},
    board_{tetris::Board()}
    {}

void TetrisApp::setup() {
  menu_image = cinder::gl::Texture2d::create(loadImage(loadAsset("tetris-logo.jpg")));
  SetUpMusic();
  //Starts the playing the background music
  if (!theme_song_->isPlaying()) {
    theme_song_->start();
  }
}

void TetrisApp::update() {
  if (state_ == GameState::kGameOver) {
    if (top_players_.empty()) {
      leader_board_.AddScoreToLeaderBoard({player_name_, static_cast<size_t>(board_.GetScore())});
      //Returns a vector of the highest scores of all players
      top_players_ = leader_board_.RetrieveHighScores(kLimit);
      //Initialises the current player
      tetris::Player current_player = tetris::Player(player_name_, board_.GetScore());
      //Returns a vector of the scores of the current player
      current_player_scores_ = leader_board_.RetrieveHighScores(current_player, kLimit);
      assert(!top_players_.empty());
    }
    return;
  }
  //Checks if the current tetromino has hit the bottom or collided with another tetromino that is already placed
  if (is_bottom_ || is_collided_) {
    //changes the tetromino to the next piece
    current_ = next_;
    //randomizes for a truly random piece
    cinder::Rand::randomize();
    next_ = cinder::Rand::randInt(0,7);
    //Changes the location so that the new tetromino can fall from the top of the screen
    location_ = tetris::Location(80.0, 0.0);
    //Changes the booleans that check if the tetromino has reached the bottom or collided back to false
    is_bottom_ = false;
    is_collided_ = false;
  }
  const auto time = std::chrono::system_clock::now();
  using std::chrono::milliseconds;
  //Elapsed time is the time from the last time the food changed colour
  long elapsed_time =
      std::chrono::duration_cast<milliseconds>(time - last_time_)
          .count();
  //Converts milliseconds to seconds
  elapsed_time /= 1000.0;
  //Drop delay decreases as the level goes higher
  long drop_delay = long(2.0) - (0.2 * level_);
  if (elapsed_time >= drop_delay && state_ == GameState::kPlaying) {
    DownwardMovement();
    last_time_ = time;
  }
  board_.DeletePossibleLines();
  PlayMusic();
  board_.UpdateScore(level_);
  //Restarts the background music once it is over
  if (!theme_song_->isPlaying()) {
    theme_song_->start();
  }
  //Changes the flag so that the level can increase only the next time the lines cleared is divisible by 30 (level increases once for ever 30 lines cleared)
  if ((board_.GetLinesClearedTotal() % 30) != 0) {
    flag_ = false;
  }
  if (board_.GetLinesClearedTotal() % 30 == 0 && (board_.GetLinesClearedTotal() != 0) && !flag_) {
    //Ensures a max level of 19
    if (level_ < 20) {
      level_ += 1;
      flag_ = true;
      level_sound_->start();
    }
  }
  if (board_.CheckGameEnd()) {
    state_ = GameState::kGameOver;
  }

}

void TetrisApp::draw() {
  if (state_ == GameState::kMenu) {
    DrawMenu();
  } else if (state_ == GameState::kPlaying) {
    cinder::gl::clear();
    DrawOccupied();
    if (!is_collided_) {
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

void TetrisApp::DrawScore() const {
  const std::string scoreText = "Score :" + std::to_string(board_.GetScore());
  const Color color = {1, 1, 1};
  const cinder::ivec2 size = {200, 50};
  const cinder::vec2 location = {500, 500};

  PrintText(scoreText, color, size, location);
}
void TetrisApp::DrawLevel() const {
  const std::string scoreText = "Level :" + std::to_string(level_);
  const Color color = {1, 1, 1};
  const cinder::ivec2 size = {120, 50};
  const cinder::vec2 location = {500, 600};

  PrintText(scoreText, color, size, location);
}
void TetrisApp::DrawLinesCleared() const {
  const std::string scoreText = "Lines :" + std::to_string(board_.GetLinesClearedTotal());
  const Color color = {1, 1, 1};
  const cinder::ivec2 size = {200, 50};
  const cinder::vec2 location = {500, 700};

  PrintText(scoreText, color, size, location);
}
void TetrisApp::DrawBackground() const {
  cinder::gl::color(1,0,0);
  cinder::gl::drawSolidRect(cinder::Rectf(400,0,600,800));
}
void TetrisApp::DrawNext() {
  int xBlockSize = 4;
  int yBlockSize = 4;
  //Goes through the tetromino 2-d array to check the shape of the piece
  for (int x = 0; x < xBlockSize; x++) {
    for (int y = 0; y < yBlockSize; y++) {
      if (tetromino_.GetTetrominoType(next_, x, y) == 1) {
        //Gives a constant position for the next piece and draws the next piece there
        int drawRow = 410 + (kTileSize * x);
        int drawCol = 200 + (kTileSize * y);
        cinder::gl::color(tetromino_.GetColorType(next_, 0),
                          tetromino_.GetColorType(next_, 1),
                          tetromino_.GetColorType(next_, 2));
        cinder::gl::drawSolidRect(cinder::Rectf(drawRow, drawCol, drawRow + kTileSize, drawCol + kTileSize));
      } else {
        //Surrounds the piece with black so that the colours don't merge and its clear which block is next
        int drawRow = 410 + (kTileSize * x);
        int drawCol = 200 + (kTileSize * y);
        cinder::gl::color(0,0,0);
        cinder::gl::drawSolidRect(cinder::Rectf(drawRow, drawCol, drawRow + kTileSize, drawCol + kTileSize));
      }
    }
  }
  const std::string scoreText = "NEXT";
  const Color color = {1, 1, 1};
  const cinder::ivec2 size = {200, 50};
  const cinder::vec2 location = {500, 170};

  PrintText(scoreText, color, size, location);
}
void TetrisApp::DrawCurrent() {
  int xBlockSize = 4;
  int yBlockSize = 4;
  //Goes through the tetromino 2-d array to check the shape of the piece
  for (int x = 0; x < xBlockSize; x++) {
    for (int y = 0; y < yBlockSize; y++) {
      if (tetromino_.GetTetrominoType(current_, x, y) == 1) {
        //Checks the current location and accordingly draws the piece depending on the piece type
        int drawRow = location_.Row() + (kTileSize * x);
        int drawCol = location_.Col() + (kTileSize * y);
        //Colors according to the rbg values given in the colour array in tetromino.cpp
        cinder::gl::color(tetromino_.GetColorType(current_, 0),
                          tetromino_.GetColorType(current_, 1),
                          tetromino_.GetColorType(current_, 2));
        cinder::gl::drawSolidRect(cinder::Rectf(drawRow, drawCol, drawRow + kTileSize, drawCol + kTileSize));
      } else {
        int drawRow = location_.Row() + (kTileSize * x);
        int drawCol = location_.Col() + (kTileSize * y);
        int matrixRow = drawRow / kTileSize;
        int matrixCol = drawCol / kTileSize;
        //Draws the surrounding 'blocks' of the 2-d array as black as long as it is not occupied in the board
        if (board_.GetBoardArray(matrixRow, matrixCol) == 0) {
          cinder::gl::color(0, 0, 0);
          cinder::gl::drawSolidRect(cinder::Rectf(drawRow, drawCol, drawRow + kTileSize, drawCol + kTileSize));
        }
      }
    }
  }
}
void TetrisApp::DrawOccupied() {
  //Checks the board piece by piece
  for (int x = 0; x < board_.GetWidth(); x++) {
    for (int y = 0; y < board_.GetHeight(); y++) {
      //If the board contains a block
      if (board_.GetBoardArray(x, y) != 0) {
        //Gets the piece type as it is stored as (the index of the pieces array + 1)
        int pType = board_.GetBoardArray(x, y) - 1;
        int drawRow2 = (kTileSize * x);
        int drawCol2 = (kTileSize * y);
        cinder::gl::color(tetromino_.GetColorType(pType, 0),
                          tetromino_.GetColorType(pType, 1),
                          tetromino_.GetColorType(pType, 2));
        cinder::gl::drawSolidRect(cinder::Rectf(drawRow2, drawCol2, drawRow2 + kTileSize, drawCol2 + kTileSize));
      }
    }
  }
}
void TetrisApp::DrawGameOver() {
  if (top_players_.empty()) return;

  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 50};
  const Color color = Color::black();

  size_t row = 0;
  PrintText("Game Over :(", color, size, center);
  for (const tetris::Player& player : top_players_) {
    std::stringstream ss;
    ss << player.name_ << " - " << player.score_;
    PrintText(ss.str(), color, size, {center.x, center.y + (++row) * 50});
  }
  std::stringstream ss;
  ss << "Your scores \n";
  PrintText(ss.str(), color, size, {center.x, center.y + (++row) * 50});
  for (const tetris::Player& player : current_player_scores_) {
    std::stringstream ss;
    ss << player.name_ << " - " << player.score_;
    PrintText(ss.str(), color, size, {center.x, center.y + (++row) * 50});
  }
}
void TetrisApp::DrawMenu() const {
  cinder::gl::color(1,1,1);
  cinder::gl::pushModelMatrix();
  cinder::gl::translate(getWindowCenter().x, getWindowCenter().y + 225);
  cinder::Rectf drawRect(-200, -600, 200, -300);
  cinder::gl::draw(menu_image, drawRect);
  cinder::gl::popModelMatrix();
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 100};
  const Color color = {0,0.6,1};
  std::stringstream ss;
  ss << "Welcome to Tetris!  \n Press Enter to play";
  PrintText(ss.str(), color, size, {center.x, center.y});
}
void TetrisApp::PlayMusic() {
  if (board_.GetLinesCleared() == 1) {
    if (!single_sound_->isPlaying()) {
      single_sound_->start();
    }
    board_.SetLinesCleared(0);
  } else if (board_.GetLinesCleared() == 2) {
    if (!double_sound_->isPlaying()) {
      double_sound_->start();
    }
    board_.SetLinesCleared(0);
  } else if (board_.GetLinesCleared() == 3) {
    if (!triple_sound_->isPlaying()) {
      triple_sound_->start();
    }
    board_.SetLinesCleared(0);
  } else if (board_.GetLinesCleared() == 4) {
    if (!tetris_sound_->isPlaying()) {
      tetris_sound_->start();
    }
    board_.SetLinesCleared(0);
  }
}
void TetrisApp::SetUpMusic() {
  cinder::audio::SourceFileRef source_file = cinder::audio::load( cinder::app::loadAsset( "tetris.mp3" ) );
  theme_song_ = cinder::audio::Voice::create( source_file );
  cinder::audio::SourceFileRef source_file_level = cinder::audio::load( cinder::app::loadAsset( "levelup.wav" ));
  level_sound_ = cinder::audio::Voice::create( source_file_level);
  cinder::audio::SourceFileRef source_file_single = cinder::audio::load( cinder::app::loadAsset( "single_line.wav" ) );
  single_sound_ = cinder::audio::Voice::create( source_file_single );
  cinder::audio::SourceFileRef source_file_double = cinder::audio::load( cinder::app::loadAsset( "double_line.wav" ) );
  double_sound_ = cinder::audio::Voice::create( source_file_double );
  cinder::audio::SourceFileRef source_file_triple = cinder::audio::load( cinder::app::loadAsset( "triple_line.wav" ) );
  triple_sound_ = cinder::audio::Voice::create( source_file_triple );
  cinder::audio::SourceFileRef source_file_tetris = cinder::audio::load( cinder::app::loadAsset( "tetris_cleared.wav" ) );
  tetris_sound_ = cinder::audio::Voice::create( source_file_tetris );
}

void TetrisApp::DownwardMovement() {
  //int tile_size = 40;
  int southernmost = tetromino_.GetSouthernmostPoint(current_);
  int limit = 800 - ((southernmost + 1) * kTileSize);
  //Checks if the block is within limits and if it will not undergo a downward collision
  if (location_.Col() < limit && (!board_.DetectDownwardCollision(current_, location_))) {
    location_.IncrementCol();
  } else if (location_.Col() >= limit) {
    is_bottom_ = true;
    //Goes through the tetromino 2-d array to check the shape of the piece
    for (int x = 0; x < 4; x++) {
      for (int y = 0; y < 4; y++) {
        if (tetromino_.GetTetrominoType(current_, x, y) == 1) {
          int RowOccupied = location_.Row() / kTileSize + x;
          int ColOccupied = location_.Col() / kTileSize + y;
          //Updates the tetromino onto the board
          board_.SetBoardArray(RowOccupied, ColOccupied, (current_ + 1));
        }
      }
    }
  } else if (board_.DetectDownwardCollision(current_, location_)) {
    is_collided_ = true;
    //Goes through the tetromino 2-d array to check the shape of the piece
    for (int x = 0; x < 4; x++) {
      for (int y = 0; y < 4; y++) {
        if (tetromino_.GetTetrominoType(current_, x, y) == 1) {
          int RowOccupied = location_.Row() / kTileSize + x;
          int ColOccupied = location_.Col() / kTileSize + y;
          //Updates the tetromino onto the board
          board_.SetBoardArray(RowOccupied, ColOccupied, (current_ + 1));
        }
      }
    }
  }
}

void TetrisApp::HardDrop() {
  int southernmost = tetromino_.GetSouthernmostPoint(current_);
  int limit = 800 - ((southernmost + 1) * kTileSize);
  //Keeps going down until it is at the bottom or there is a downward collision
  while(location_.Col() < limit && (!is_collided_) && (!is_bottom_) && (state_ == GameState::kPlaying)) {
    DownwardMovement();
  }
}

void TetrisApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_DOWN: {
      DownwardMovement();
      break;
    }
    case KeyEvent::KEY_UP: {
      //If there is a block surriounding the current one, tetromino should not rotate
      if (board_.DetectRightwardCollision(current_, location_) || board_.DetectLeftwardCollision(current_, location_)) {
        break;
      }
      tetromino_.RotateTetromino(current_);
      int southernmost = tetromino_.GetSouthernmostPoint(current_);
      int limitDown = 800 - ((southernmost + 1) * kTileSize);
      int eastmost = tetromino_.GetEastmostPoint(current_);
      int westmost = tetromino_.GetWestmostPoint(current_);
      int limitRight = 400 - ((eastmost + 1) * kTileSize);
      int limitLeft = (0 - ((westmost) * kTileSize));
      //Checks if the block's location is valid or not after the rotation, if not rotates it back to normal
      if (location_.Row() > limitRight || location_.Row() < limitLeft || location_.Col() > limitDown) {
        tetromino_.RotateTetrominoCounterClockwise(current_);
      }
      break;
    }
    case KeyEvent::KEY_RIGHT: {
      //Moves tile to the right if it is within screen boundaries
      int eastmost = tetromino_.GetEastmostPoint(current_);
      int limit = 400 - ((eastmost + 1) * kTileSize);
      if (location_.Row() < limit && (!board_.DetectRightwardCollision(current_, location_))) {
        location_.IncrementRow();
      }
      break;
    }
    case KeyEvent::KEY_LEFT: {
      //Moves tile to the left if it is within screen boundaries
      int westmost = tetromino_.GetWestmostPoint(current_);
      int limit = (0 - ((westmost) * kTileSize));
      if (location_.Row() > limit && (!board_.DetectLeftwardCollision(current_, location_))) {
        location_.DecrementRow();
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


// namespace tetrisapp
}