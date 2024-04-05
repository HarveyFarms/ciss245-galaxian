#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <vector>
#include <fstream>
#include "Includes.h"
#include "Constants.h"
#include "Surface.h"

class Star
{
public:
  Star();
  void update();
  void draw();
  static void set_surface(Surface * s);
  static Surface * s_;
private:
  int x, y, dx, dy;
  int r, g, b;
  int timer;
  bool on_screen;
};


class Background
{
public:
  Background();
  ~Background();
  void update();
  void draw();
  static void set_surface(Surface * s);
  static Surface * surface;
  bool on_starting_screen() { return starting_screen; }
  void update_score(int score)
  {
    score_score += score;
  }
  void switch_screen() 
  {
    starting_screen = !starting_screen; 
    setup_text();
    setup_rects();
  }
  bool playing()
  {
    return (!starting_screen && !typing && !leaderboards_screen && !instructions_screen);
  }
  int get_hiscore() { return high_score; }
  bool game_ended() { return game_over; }
  bool is_typing() { return typing; }
  void game_over_switch() { game_over = !game_over; }
  void switch_typing() { typing = !typing; }
  void inputplace(int x) 
  {
    if (keyinput0 != NULL) delete keyinput0;
    switch (x)
    {
      case 1:
        keyinput0 = new Image(small.render("Amazing job on getting the best score!", WHITE));
        break;
      case 2:
        keyinput0 = new Image(small.render("Well done getting the second highest score!", WHITE));
        break;
      case 3:
        keyinput0 = new Image(small.render("Good job getting the third highest score.", WHITE));
        break;
      default:
        keyinput0 = new Image(small.render("Good job on getting top 10 on the leaderboards.", WHITE));
      break;
    }
  keyinput0->rect().x = W / 2 - 300;
  keyinput0->rect().y = H / 2 - 150;
  }
  void reset();
  void cursor_up() 
  { if (cursor_y > H / 2 + 90) cursor_y -= 70; 
    else cursor_y = H / 2 + 300;
  }
  void cursor_down() 
  { if (cursor_y < H / 2 + 300) cursor_y += 70; 
    else cursor_y = H / 2 + 90;
  }
  bool goto_play() { return (cursor_y == H / 2 + 90); }
  bool goto_instructions() { return (cursor_y == H / 2 + 160); }
  bool goto_leaderboards() { return (cursor_y == H / 2 + 230); }
  bool goto_exit() { return (cursor_y == H / 2 + 300); }
  void switch_leaderboards() 
  {
    starting_screen = !starting_screen;
    leaderboards_screen = !leaderboards_screen; 
    setup_text();
  }
  bool on_leaderboards() { return leaderboards_screen; }
  void switch_instructions() 
  {
    starting_screen = !starting_screen;
    reset_intructions();
    instructions_screen = !instructions_screen;
    setup_text();
  }
  bool on_instructions() { return instructions_screen; }
private:
  // methods to setup text
  void setup_text();
  void setup_rects();
  bool starting_screen;
  bool leaderboards_screen;
  bool instructions_screen;
  bool typing;
  void update_score_section();
  void draw_score_section();
  void get_names();
  void update_cursor_section();
  void draw_cursor_section();
  void update_ships();
  void draw_ships();

  // stars
  std::vector< Star > stars;

  // fonts
  Font small;
  Font middle;
  Font big;

  // text
  Image high;
  int high_score;
  Image* high_s;
  Image score;
  int score_score;
  Image* score_s;
  Image name;
  Image madeby;
  Image gameover;
  Image* keyinput0;
  Image keyinput1;
  Image galactic_heroes;
  Image top10;
  Image pos_score_name;

  // for cursor and options
  Image* cursor;
  Image* Iinstructions;
  int cursor_y;
  Image* play;
  Image* instructions;
  Image* leaderboards;
  Image* exit;

  // for instructions screen
  int counter;
  void reset_intructions();
  Image we_are_the_galaxians;
  Image mission_destroy_aliens;
  Image score_advance_table;
  Image convoy_charger;
  Image* flagship;
  bool flag_moving;
  Image* red_escort;
  bool red_moving;
  Image* purple;
  bool purple_moving;
  Image* blue;
  bool blue_moving;
  Image flagship_points;
  Image red_escort_points;
  Image purple_points;
  Image blue_points;

  // for scores
  std::string score1;
  std::string name1;
  std::string score2;
  std::string name2;
  std::string score3;
  std::string name3;
  std::string score4;
  std::string name4;
  std::string score5;
  std::string name5;
  std::string score6;
  std::string name6;
  std::string score7;
  std::string name7;
  std::string score8;
  std::string name8;
  std::string score9;
  std::string name9;
  std::string score10;
  std::string name10;

  Image first;
  Image* first_score;
  Image* first_name;
  Image second;
  Image* second_score;
  Image* second_name;
  Image third;
  Image* third_score;
  Image* third_name;
  Image fourth;
  Image* fourth_score;
  Image* fourth_name;
  Image fifth;
  Image* fifth_score;
  Image* fifth_name;
  Image sixth;
  Image* sixth_score;
  Image* sixth_name;
  Image seventh;
  Image* seventh_score;
  Image* seventh_name;
  Image eighth;
  Image* eighth_score;
  Image* eighth_name;
  Image ninth;
  Image* ninth_score;
  Image* ninth_name;
  Image tenth;
  Image* tenth_score;
  Image* tenth_name;

  // rects
  Rect high_rect;
  Rect score_rect;
  Rect pos_r;
  Rect score_r;
  Rect name_r;

  // Galaxian ships

  // Galaxian Logo
  Image * galaxian_logo;

  // other
  bool game_over;
};
#endif
