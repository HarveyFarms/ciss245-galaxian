#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include "Object.h"
#include "Laser.h"

class Enemy : public Object
{
public:
  Enemy(const char * s, int t) :
    attacking(false),
    Object(new Image(s)),
    amount(t), got_hit(false), recovering(false),
    doing_sin_curve(true), breaktime(0)
  {
    lasers.resize(0);
    dx() = 1;
    edx() = 1;
    dy() = 0;
  }
  bool close_to_bottom() { return y() > W / 2; }
  void extra()
  {
    for (int i = 0; i < lasers.size(); ++i)
    {
      if (!lasers[i].on_screen()) 
        lasers.erase(lasers.begin() + (i--));
      else lasers[i].draw(s_);
    }
  }
  void shoot()
  {
    if (lasers.size() < 3) lasers.push_back(Laser(x() + (w() / 2), y(), false));
  }
  virtual void extra_update(bool square)
  {
    if (attacking)
    {
      if (doing_sin_curve)
      {
        dx() = 8 * sin(PI * y() / 50);
        dy() = 2;
      }
      else
    {
        dx() = -4;
        dy() = 3;
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
    if (outside_bottom())
    {
      attacking = false;
      breaktime = 1;
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
    if (rand() % rand_amnt() == 0 && !attacking && !recovering && breaktime == 0)
    {
      attacking = true;
      if (rand() % 2 == 0) doing_sin_curve = !doing_sin_curve;
    }
  }
  virtual int rand_amnt() 
  {
    return 1;
  }
  bool hit_by_laser(const Laser & l)
  {
    return (x() <= l.x && l.x <= x() + w() && y() <= l.y && l.y <= y() + h());
  }
  void save(int x, int y)
  {
    savex = x;
    savey = y;
  }
  virtual bool is_flag() { return false; }
  bool is_attacking() { return attacking; }
  int savex, savey;
  int amount;
  bool attacking;
  void switch_hit_status() { got_hit = true; }
  bool has_been_hit() { return got_hit; }
  bool got_hit;
  bool recovering;
  bool doing_sin_curve;
  int breaktime;
private:
  std::vector< Laser > lasers;
};

#endif
