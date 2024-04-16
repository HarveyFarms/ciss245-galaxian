#ifndef FLAG_H
#define FLAG_H

#include "Enemy.h"

class Flag : public Enemy
{
public:
  Flag() : 
    Enemy("images/GalaxianFlagship.gif", 60)
  {}
  virtual int rand_amnt() 
  {
    return 2000;
  }
  bool is_flag() { return true; }
};
#endif
