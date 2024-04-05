#ifndef WAVE_H
#define WAVE_H

#include "Flag.h"
#include "Red.h"
#include "Purple.h"
#include "Blue.h"

class Wave : public Rect
{
public:
  Wave()
  : move(false), show_rect_(false), dx(1)
  {
    x = 0;
    y = 100;
    w = 440;
    h = 260;
    enemies.resize(46);
    for (int i = 0; i < 2; ++i)
    {
      enemies[i] = new Flag;
      enemies[i]->x() = (i * 135) + 135;
      enemies[i]->y() = y;
      enemies[i]->save(enemies[i]->x(), enemies[i]->y());
    }
    for (int i = 2; i < 5; ++i)
    {
      enemies[i] = new Red(enemies[0]);
      enemies[i]->x() = ((i-2) * 45) + 90;
      enemies[i]->y() = y + 45;
      enemies[i]->save(enemies[i]->x(), enemies[i]->y());
    }
    for (int i = 5; i < 8; ++i)
    {
      enemies[i] = new Red(enemies[1]);
      enemies[i]->x() = ((i-2) * 45) + 90;
      enemies[i]->y() = y + 45;
      enemies[i]->save(enemies[i]->x(), enemies[i]->y());
    }
    for (int i = 8; i < 16; ++i)
    {
      enemies[i] = new Purple;
      enemies[i]->x() = (i % 8 * 45) + 45;
      enemies[i]->y() = y + 90;
      enemies[i]->save(enemies[i]->x(), enemies[i]->y());
    }
    for (int i = 16; i < 46; ++i)
    {
      enemies[i] = new Blue;
      int j = i % 3;
      enemies[i]->x() = (i % 10 * 45);
      enemies[i]->y() = y + 135 + j * 45;
      enemies[i]->save(enemies[i]->x(), enemies[i]->y());
    }
  }
  ~Wave()
  {
    for (Enemy * e : enemies)
    {
      delete e;
    }
  }
  void set_surface(Surface * s)
  {
    surface = s;
  }
  void update()
  {
    x += dx;
    if (x <= 0 || x + w >= W)
    {
      move = true;
      if (x <= 0) dx = 1;
      else if (x + w >= W) dx = -1;
    }
    for (Enemy * e : enemies)
    {
      e->update(move);
    }
    move = false;
  }
  void draw()
  {
    if (show_rect_) surface->put_rect(Rect(*this), WHITE);
    for (Enemy * e : enemies)
    {
      e->draw();
    }
  }
  void cleanup(int t)
  {
    enemies[t]->switch_hit_status();
    enemies.erase(enemies.begin() + t);
  }
  std::vector< Enemy * > get_enemies() { return enemies; }
private:
  bool move;
  bool show_rect_;
  Surface * surface;
  int dx;
  std::vector< Enemy * > enemies;
};

#endif
