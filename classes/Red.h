#ifndef RED_H
#define RED_H

#include "Flag.h"

class Red : public Enemy
{
  public:
    Red(Enemy * m = NULL) : 
      Enemy("images/GalaxianRedAlien.gif", 50),
      master(m),
      on_own(false)
  {}
    virtual void extra_update(bool square, bool dont_attack)
    {
      if (master->has_been_hit()) on_own = true;
      passed0 = false;
      if (!on_own && master->is_attacking() && !master->close_to_bottom() && !attacking)
      {
        attacking = true;
        passed0 = true;
      }
      if (rand() % rand_amnt() == 0 && !attacking && on_own && !recovering && breaktime == 0 && !dont_attack)
      {
        attacking = true;
        passed0 = true;
      }
      if (!attacking)
      {
        if (rand() % 2 == 0) 
        {
          if (rand() % 5 == 0)
            doing_sin_curve = !doing_sin_curve;
          going_left = !going_left;
        }
      }
      if (attacking)
      {
        if (on_own)
        {
          if (doing_sin_curve)
          {
            dx() = 8 * sin(PI * y() / 100);
            dy() = 2;
          }
          else
          {
            if (going_left)
            {
              dx() = 5;
            }
            else
            {
              dx() = -5;
            }
            dy() = 3;
          }
        }
        else
        {
          dx() = master->dx();
          dy() = master->dy();
        }
      }
      savex += edx();
      if (breaktime != 0)
      {
        if (breaktime < 200) ++breaktime;
        else
        {
          recovering = true;
          dx() = edx();
          dy() = 1;
          x() = savex;
          y() = 0;
          breaktime = 0;
        }
      }
      passed1 = false;
      if (outside_bottom())
      {
        attacking = false;
        breaktime = 1;
        passed1 = true;
        dx() = edx();
        dy() = 0;
        x() = savex;
        y() = -32;
      }
      if (recovering && y() == savey)
      {
        recovering = false;
        dy() = 0;
      }
      if (outside_left())
      {
        x() = W - 32;
      }
      if (outside_right())
      {
        x() = 0;
      }
      if (square)
      {
        if (!attacking) dx() *= -1;
        edx() *= -1;
      }
    }
    virtual bool outside_bottom()
    {
      return (y() + h() >= H);
    }
    Enemy * master;
    bool on_own;
    int rand_amnt() { return 1000; }
};
#endif
