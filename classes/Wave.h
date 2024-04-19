#ifndef WAVE_H
#define WAVE_H

#include "Flag.h"
#include "Red.h"
#include "Purple.h"
#include "Blue.h"

class Wave : public Rect
{
public:
  Wave();
  ~Wave();
  void set_surface(Surface * s);
  void update();
  void draw();
  void decrease(int t);
  void reset();
  std::vector< Enemy * > get_enemies() { return enemies; }
  void resize();
  bool wave_has_died;
  bool coming_in;
  int wave_amount;
private:
  bool move;
  bool sections[10];
  int count_checker;
  int count;
  bool show_rect_;
  Surface * surface;
  int dx;
  std::vector< Enemy * > enemies;
};

#endif
