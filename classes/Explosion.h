#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "Object.h"

class Explosion : public Object
{
  public:
    Explosion(int x_ = 0, int y_ = 0) :
      finished(false), draw_inner(false),
      rad(10), inner_rad(1), x(x_ + 16), y(y_ + 16),
      r(255), g(10), b(10)
  {}
    void draw()
    {
      s_->put_circle(x, y, rad, r, g, b);
      if (draw_inner)
      {
        s_->put_circle(x, y, inner_rad, BLACK);
        if (inner_rad >= 15) finished = true;
        else 
        {
          inner_rad++;
          r -= 10;
        }
      }
      if (rad >= 15)
        draw_inner = true;
      else
        rad++;
    }
    bool finished;
  private:
    bool draw_inner;
    int rad, inner_rad, x, y, r, g, b;
};
#endif
