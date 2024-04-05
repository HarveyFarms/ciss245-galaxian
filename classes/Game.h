#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <sstream>

#include "Includes.h"
#include "Constants.h"
#include "compgeom.h"
#include "Surface.h"
#include "Event.h"

// my files
#include "Background.h"
#include "Ship.h"
#include "Wave.h"
#include "Explosion.h"

class Game
{
public:
  Game();
  ~Game();
  void run();
private:
  // my objects/classes
  Background * background;
  Ship * Galaxip;
  Wave * waves;
  std::vector< Explosion > explosions;

  // methods to run the game
  void get_input();
  void update();
  void setup_ships();
  void draw();
  void reset_all();
  int infile();
  void putinfile(int);
  void handle_background();
  void background_input();
  void laser_hits_enemy();

  // extra methods
  bool user_quits() 
  { return ((event.poll() && event.type() == QUIT) || kp[RET] && goto_exit()); }
  bool playing()
  {
    return background->playing();
  }
  bool goto_play()
  { return background->goto_play(); }
  bool goto_instructions()
  { return background->goto_instructions(); }
  bool goto_leaderboards()
  { return background->goto_leaderboards(); }
  bool goto_exit()
  { return background->goto_exit(); }
  void update_score(int t)
  {
    background->update_score(t);
  }

  // for user input for score saving
  std::string in;
  int save_score;
  int place;
  Image* in_image;
  Rect* cursor;
  bool blink;
  int counter;

  // main objects for SDL
  Surface * surface;
  Event event;
  KeyPressed kp;
  Keyboard keyboard;

  // extra
  bool paused;
  bool done_typing;
  int count;
  bool waiting;
  int wait;
  bool pressed;
};
#endif
