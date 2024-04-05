#ifndef OBJECT_H
#define OBJECT_H

#include "Surface.h"
#include "Constants.h"

class Object
{
public:
  Object()
    : image(NULL)
  {}
  Object(Image * s)
  : image(s), assembled(true)
  {}
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
  static Surface * s_;
  Image* image;
  bool assembled;
  int dx_, dy_, edx_;
};
#endif
