#ifndef FLAG_H
#define FLAG_H

#include "Enemy.h"

class Flag : public Enemy
{
public:
  Flag() : 
    Enemy("images/GalaxianFlagship.gif", 60)
  {}
  bool is_flag() { return true; }
  virtual int rand_amnt() 
  {
    return (RANDOM_FOR_FLAG < 100 ? 100 : RANDOM_FOR_FLAG);
  }
};
#endif
