#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include "Object.h"
#include "Laser.h"


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
  void draw(bool b)
  {
    if (!b)
      s_->put_image(*image, image->rect());
    extra();
  }
  bool shoot()
  {
    if (lasers.size() < AMOUNT_OF_SHOOTABLE_LASERS) 
    {
      lasers.push_back(Laser(x() + (w() / 2), y()));
      return true;
    }
    return false;
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
