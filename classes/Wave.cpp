#include "Wave.h"

Wave::Wave()
  : wave_has_died(false), coming_in(false),
  wave_amount(1), 
  move(false), show_rect_(false), dx(1), count(0)
{
  x = 0;
  y = 100;
  w = 440;
  h = 260;
  enemies.resize(46);
  for (int i = 0; i < 2; ++i)
  {
    enemies[i] = new Flag;
    enemies[i]->x() = (i * 135) + 135;
    enemies[i]->y() = y;
    enemies[i]->save(enemies[i]->x(), enemies[i]->y());
  }
  for (int i = 2; i < 5; ++i)
  {
    enemies[i] = new Red(enemies[0]);
    enemies[i]->x() = ((i-2) * 45) + 90;
    enemies[i]->y() = y + 45;
    enemies[i]->save(enemies[i]->x(), enemies[i]->y());
  }
  for (int i = 5; i < 8; ++i)
  {
    enemies[i] = new Red(enemies[1]);
    enemies[i]->x() = ((i-2) * 45) + 90;
    enemies[i]->y() = y + 45;
    enemies[i]->save(enemies[i]->x(), enemies[i]->y());
  }
  for (int i = 8; i < 16; ++i)
  {
    enemies[i] = new Purple;
    enemies[i]->x() = (i % 8 * 45) + 45;
    enemies[i]->y() = y + 90;
    enemies[i]->save(enemies[i]->x(), enemies[i]->y());
  }
  for (int i = 16; i < 46; ++i)
  {
    enemies[i] = new Blue;
    int j = i % 3;
    enemies[i]->x() = (i % 10 * 45);
    enemies[i]->y() = y + 135 + j * 45;
    enemies[i]->save(enemies[i]->x(), enemies[i]->y());
  }
}

Wave::~Wave()
{
  for (Enemy * e : enemies)
  {
    delete e;
  }
}

void Wave::set_surface(Surface * s)
{
  surface = s;
}

void Wave::update()
{
  x += dx;
  if (x <= 0 || x + w >= W)
  {
    move = true;
    if (x <= 0) dx = 1;
    else if (x + w >= W) dx = -1;
  }
  if (wave_has_died)
    reset();
  for (Enemy * e : enemies)
  {
    if (count <= 1)
      e->update(move, false);
    else
      e->update(move, true);
    if (e->enemy_attacking_control0()) ++count;
    if (e->enemy_attacking_control1()) --count;
  }
  move = false;
}

void Wave::draw()
{
  if (show_rect_) surface->put_rect(Rect(*this), WHITE);
  for (Enemy * e : enemies)
  {
    if (!e->has_been_hit()) e->draw();
  }
}

void Wave::decrease(int t)
{
  enemies[t]->switch_hit_status();
  if (enemies[t]->is_attacking()) count--;
  enemies.erase(enemies.begin() + t);
  if (enemies.size() == 0) wave_has_died = true;
}

void Wave::reset()
{
  ++wave_amount;
  std::cout << "wave_amount = " << wave_amount << '\n';
  coming_in = true;
  x = 0;
  y = 100;
  w = 440;
  h = 260;
  enemies.resize(46);
  for (int i = 0; i < 2; ++i)
  {
    enemies[i] = new Flag;
    enemies[i]->breaktime = 1;
    enemies[i]->x() = (i * 135) + 135;
    enemies[i]->y() = -32;
    enemies[i]->save(enemies[i]->x(), 0);
  }
  for (int i = 2; i < 5; ++i)
  {
    enemies[i] = new Red(enemies[0]);
    enemies[i]->breaktime = 25;
    enemies[i]->x() = ((i-2) * 45) + 90;
    enemies[i]->y() = -32;
    enemies[i]->save(enemies[i]->x(), y + 45);
  }
  for (int i = 5; i < 8; ++i)
  {
    enemies[i] = new Red(enemies[1]);
    enemies[i]->breaktime = 25;
    enemies[i]->x() = ((i-2) * 45) + 90;
    enemies[i]->y() = -32;
    enemies[i]->save(enemies[i]->x(), y + 45);
  }
  for (int i = 8; i < 16; ++i)
  {
    enemies[i] = new Purple;
    enemies[i]->breaktime = 55;
    enemies[i]->x() = (i % 8 * 45) + 45;
    enemies[i]->y() = -32;
    enemies[i]->save(enemies[i]->x(), y + 90);
  }
  for (int i = 16; i < 46; ++i)
  {
    enemies[i] = new Blue;
    int j = i % 3;
    enemies[i]->breaktime = j * 45 + 80;
    enemies[i]->x() = (i % 10 * 45);
    enemies[i]->y() = -32;
    enemies[i]->save(enemies[i]->x(), y + 135 + j * 45);
  }
  wave_has_died = false;
}
