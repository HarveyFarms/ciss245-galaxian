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
  void laser_hits_ship();
  void enemy_hits_ship();

  // extra methods
  bool user_quits() 
  { return ((event.poll() && event.type() == QUIT) || kp[RET] && goto_exit() || user_clicked); }
  bool user_clicked;
  bool playing()
  {
    return background->playing();
  }
  bool mouse_on_play() {
    return (H / 2 + 90 < mouse_y() && mouse_y() < H / 2 + 150 && W / 2 - 250 < mouse_x() && mouse_x() < W / 2 - 50 && ALLOW_MOUSE_SELECTION);
  }
  bool mouse_on_instructions() {
    return (H / 2 + 160 < mouse_y() && mouse_y() < H / 2 + 220 && W / 2 - 250 < mouse_x() && mouse_x() < W / 2 + 320 && ALLOW_MOUSE_SELECTION);
  }
  bool mouse_on_leader() {
    return (H / 2 + 230 < mouse_y() && mouse_y() < H / 2 + 290 && W / 2 - 250 < mouse_x() && mouse_x() < W / 2 + 320 && ALLOW_MOUSE_SELECTION);
  }
  bool mouse_on_exit() {
    return (H / 2 + 300 < mouse_y() && mouse_y() < H / 2 + 360 && W / 2 - 250 < mouse_x() && mouse_x() < W / 2 - 50 && ALLOW_MOUSE_SELECTION);
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
  Music game_music;
  Sound shoot, explode;

  // extra
  int timer;
  int amount_ships;
  bool paused;
  bool reboot_ship;
  bool done_typing;
  int count;
  bool waiting;
  int wait;
  bool pressed;
  bool clicked;
  int counter_for_shot;
  bool m_key_pressed;
  bool muted;
};
#endif
