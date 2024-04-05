#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include "Object.h"
#include "Laser.h"

const int AMOUNT_OF_SHOOTABLE_LASERS = 20;

class Ship : public Object
{
  public:
  Ship() :
    Object(new Image("images/GalaxianGalaxip.gif"))
  {
    lasers.resize(0);
  }
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
    if (lasers.size() < AMOUNT_OF_SHOOTABLE_LASERS) lasers.push_back(Laser(x() + (w() / 2), y()));
  }
  void cleanup(int t)
  {
    lasers.erase(lasers.begin() + t);
  }
  std::vector< Laser > get_lasers() const
  {
    return lasers;
  }
private:
  std::vector< Laser > lasers;
};
#endif
