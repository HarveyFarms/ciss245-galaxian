#ifndef OBJECT_H
#define OBJECT_H

#include "Surface.h"
#include "Laser.h"
#include "Constants.h"

class Object
{
public:
  Object()
  : image(NULL), is_hit(false),
    doing_sin_curve(false), theta(0)
  {}
  Object(Image * s)
  : image(s), assembled(true), is_hit(false),
    doing_sin_curve(false), theta(0)
  {}
  bool doing_sin_curve;
  ~Object()
  {
    if (image != NULL) delete image;
  }
  static void set_surface(Surface * s)
  {
    s_ = s;
  }
  virtual int & x()
  {
    return image->rect().x;
  }
  virtual int & y()
  {
    return image->rect().y;
  }
  virtual int & w()
  {
    return image->rect().w;
  }
  virtual int & h()
  {
    return image->rect().h;
  }
  virtual int & dx()
  {
    return dx_;
  }
  virtual int & edx()
  {
    return edx_;
  }
  virtual int & dy()
  {
    return dy_;
  }
  virtual void make()
  {
    image->getRect();
  }
  virtual void draw()
  {
    if (!is_hit)
      s_->put_image(*image, image->rect());
    extra();
  }
  virtual void extra()
  {}
  void update(bool move = false, bool dont_attack = false)
  {
    x() += dx_;
    y() += dy_;
    extra_update(move, dont_attack);
  }
  double theta;
  virtual void extra_update(bool move, bool dont_attack)
  {}
  virtual bool outside_bottom()
  {
    return (y() + h() >= H + 50);
  }
  virtual bool outside_left()
  {
    return (x() <= -2);
  }
  virtual bool outside_right()
  {
    return (x() + w() >= W + 3);
  }
  virtual int rand_amnt() 
  {
    return 1;
  }
  bool is_assembled() 
  {
    return assembled;
  }
  void switch_assembled()
  {
    assembled = !assembled;
  }
  bool is_hit;
  bool collided_w_object(Object * o)
  {
    if (x() <= o->x() && o->x() <= x() + w() || x() <= o->x() + o->w() && o->x() + o->w() <= x() + w() && !is_hit)
    {
      return (y() <= o->y() && o->y() <= y() + h() || y() <= o->y() + o->h() && o->y() + o->h() <= y() + h());
    }
    else return false;
  }
  bool hit_by_laser(const Laser & o)
  {
    if ((x() <= o.x && o.x <= x() + w() || x() <= o.x + o.w && o.x + o.w <= x() + w()) || (o.x <= x() && x() <= o.x + o.w || o.x <= x() + w() && x() + w() <= o.x + o.w) && !is_hit)
    {
      return ((y() <= o.y && o.y <= y() + h() || y() <= o.y + o.h && o.y + o.h <= y() + h()) || (o.y <= y() && y() <= o.y + o.h || o.y <= y() + h() && y() + h() <= o.y + o.h));
    }
    else return false;
  }
  static Surface * s_;
  Image* image;
  bool assembled;
  int dx_, dy_, edx_;
};
#endif
