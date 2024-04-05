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
    x(x_), y(y_ + 5), w(2), h(10), dy(-5)
  {
    if (!good) dy = 5;
  }
  void draw(Surface * s_)
  {
    s_->put_rect(x, y, w, h, RED);
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
};
#endif