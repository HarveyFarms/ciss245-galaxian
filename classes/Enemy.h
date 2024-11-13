#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <vector>
#include "Object.h"

class Enemy : public Object
{
public:
  Enemy(const char * s, int t) :
    attacking(false), begin_attack(false),
    Object(new Image(s)),
    amount(t), got_hit(false), recovering(false),
    going_left(false), breaktime(0), passed0(false), passed1(false), very_beginning(false)
  {
    lasers.resize(0);
    dx() = 1;
    edx() = 1;
    dy() = 0;
  }
  void restore()
  {
    attacking = false;
    got_hit = false;
    is_hit = false;
    recovering = false;
    doing_sin_curve = true;
    going_left = false;
    passed0 = false;
    passed1 = false;
    lasers.resize(0);
    dx() = 1;
    edx() = 1;
    dy() = 0;
  }
  void cleanup(int t)
  {
    lasers.erase(lasers.begin() + t);
  }
  bool close_to_bottom() { return y() > W / 2; }
  void extra()
  {
    for (int i = 0; i < lasers.size(); ++i)
    {
      if (!lasers[i].on_screen())
        lasers.erase(lasers.begin() + (i--));
      else
        lasers[i].draw(s_);
    }
  }
  void shoot()
  {
    if (lasers.size() < 3) 
      lasers.push_back(Laser(x() + (w() / 2), y(), false));
  }
  bool very_beginning;
  virtual void extra_update(bool square, bool dont_attack)
  {
    if (attacking)
    {
      if (begin_attack)
      {
        if (very_beginning) 
        {
          theta = 0.5;
          very_beginning = false;
        }
        theta += 0.025;
        if (theta >= 1.5)
          begin_attack = false;
        dx() = (edx() < 0 ? -1 : 1) * 3 * cos(theta * PI);
        dy() = 3 * -sin(theta * PI);
      }
      else {
        if (rand() % 100 == 0 && !is_hit)
        {
          shoot();
        }
        if (doing_sin_curve)
        {
          dx() = 8 * cos(y() * PI / 100);
          dy() = 2;
        }
        else {
          if (going_left)
          {
            dx() = 5;
          }
          else {
            dx() = -5;
          }
          dy() = 3;
        }
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
    if (outside_bottom() && !is_hit)
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
      x() = W - w() - 1;
    }
    if (outside_right())
    {
      x() = 1;
    }
    if (square)
    {
      if (!attacking) dx() *= -1;
      edx() *= -1;
    }
    passed0 = false;
    if (rand() % rand_amnt() == rand() % rand_amnt() && !attacking && !recovering && breaktime == 0 && !dont_attack && !is_hit && ENEMIES_CAN_ATTACK)
    {
      attacking = true;
      begin_attack = true;
      very_beginning = true;
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
  }

  virtual int rand_amnt() 
  {
    return (RANDOM_FOR_ENEMY < 100 ? 100 : RANDOM_FOR_ENEMY);
  }
  virtual void change_master(Enemy * m = NULL)
  {}
  bool on_own;
  void save(int x, int y)
  {
    savex = x;
    savey = y;
  }
  virtual bool is_flag() { return false; }
  bool is_attacking() { return attacking; }
  bool is_recovering() { return recovering; }
  bool enemy_attacking_control0() { return passed0; }
  bool enemy_attacking_control1() { return passed1; }
  int savex, savey;
  int amount;
  bool attacking;
  bool begin_attack;
  void switch_hit_status() { is_hit =  true; got_hit = true; }
  bool has_been_hit() { return got_hit; }
  bool got_hit;
  bool recovering;
  bool going_left;
  int breaktime;
  bool passed0;
  bool passed1;
  std::vector< Laser > get_lasers() { return lasers; }
  std::vector< Laser > lasers;
private:
};

#endif
