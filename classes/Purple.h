#ifndef PURPLE_H
#define PURPLE_H
#include "Enemy.h"

class Purple : public Enemy
{
public:
  Purple() : 
    Enemy("images/GalaxianPurpleAlien.gif", 40)
  {}
  virtual int rand_amnt() 
  {
    return 1500;
  }
};
#endif
