#ifndef BLUE_H
#define BLUE_H
#include "Enemy.h"

class Blue : public Enemy
{
public:
  Blue() : 
    Enemy("images/GalaxianAquaAlien.gif", 30)
  {}
};
#endif
