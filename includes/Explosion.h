#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "Object.h"

class Explosion : public Object
{
public:
  Explosion() :
    finished(false)
  {}
private:
  bool finished;
};
#endif
