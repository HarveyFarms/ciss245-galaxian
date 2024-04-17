#ifndef PURPLE_H
#define PURPLE_H
#include "Enemy.h"

class Purple : public Enemy
{
public:
  Purple() : 
    Enemy("images/GalaxianPurpleAlien.gif", 40)
  {}
};
#endif
