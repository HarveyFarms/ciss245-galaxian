#ifndef LASER_H
#define LASER_H

#include "Surface.h"
#include "Object.h"
#include "Constants.h"

class Laser
{
  public:
    Laser() 
  {}
    Laser(int x_, int y_, bool good = true) :
    good_laser(good),
    x(x_), y(y_ + 5), w(2), h(10), dy(-LASER_SPEED)
  {
    if (good)
    {
      w = LASER_WIDTH_FOR_USER;
      h = LASER_LENGTH_FOR_USER;
      the_lasers_color = USER_LASER_COLOR;
    }
    else
    {
      the_lasers_color = ENEMY_LASER_COLOR;
    }
    if (!good) 
      dy = LASER_SPEED;
  }
  void draw(Surface * s_)
  {
    s_->put_rect(x, y, w, h, the_lasers_color);
  }
  bool is_good() { return good_laser; }
  bool on_screen()
  {
    y += dy;
    if (y + h <= 0 || y >= H) return false;
    else return true;
  }
  bool good_laser;
  int x, y, w, h, dy;
  Color the_lasers_color;
};
#endif
