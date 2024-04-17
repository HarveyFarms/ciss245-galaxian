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
    if (enemies[i] != nullptr) delete enemies[i];
    enemies[i] = new Flag;
    enemies[i]->x() = (i * 135) + 135;
    enemies[i]->y() = y;
    enemies[i]->save(enemies[i]->x(), enemies[i]->y());
  }
  for (int i = 2; i < 5; ++i)
  {
    if (enemies[i] != nullptr) delete enemies[i];
    enemies[i] = new Red(enemies[0]);
    enemies[i]->x() = ((i-2) * 45) + 90;
    enemies[i]->y() = y + 45;
    enemies[i]->save(enemies[i]->x(), enemies[i]->y());
  }
  for (int i = 5; i < 8; ++i)
  {
    if (enemies[i] != nullptr) delete enemies[i];
    enemies[i] = new Red(enemies[1]);
    enemies[i]->x() = ((i-2) * 45) + 90;
    enemies[i]->y() = y + 45;
    enemies[i]->save(enemies[i]->x(), enemies[i]->y());
  }
  for (int i = 8; i < 16; ++i)
  {
    if (enemies[i] != nullptr) delete enemies[i];
    enemies[i] = new Purple;
    enemies[i]->x() = (i % 8 * 45) + 45;
    enemies[i]->y() = y + 90;
    enemies[i]->save(enemies[i]->x(), enemies[i]->y());
  }
  for (int i = 16; i < 46; ++i)
  {
    if (enemies[i] != nullptr) delete enemies[i];
    enemies[i] = new Blue;
    int j = i % 3;
    enemies[i]->x() = (i % 10 * 45);
    enemies[i]->y() = y + 135 + j * 45;
    enemies[i]->save(enemies[i]->x(), enemies[i]->y());
  }
}

Wave::~Wave()
{
  for (int i = 0; i < enemies.size(); ++i)
  {
    if (enemies[i] != nullptr) delete enemies[i];
    enemies.erase(enemies.begin() + (i--));
  }
}

void Wave::set_surface(Surface * s)
{
  surface = s;
}

void Wave::update()
{
  if (enemies.size() == 0) wave_has_died = true;
  x += dx;
  if (x <= 0 || x + w >= W)
  {
    move = true;
    if (x <= 0) dx = 1;
    else if (x + w >= W) dx = -1;
  }
  if (wave_has_died)
    reset();
  for (int i = 0; i < enemies.size(); ++i)
  {
    if (enemies[i]->delete_me)
    {
      enemies.erase(enemies.begin() + (i--));
      continue;
    }
    if (enemies[i]->y() == enemies[i]->savey) coming_in = false;
    if (count <= 1) // count is for controlling the amnt of enemies on the screen
      enemies[i]->update(move, false);
    else
      enemies[i]->update(move, true);
    if (enemies[i]->enemy_attacking_control0()) ++count;
    if (enemies[i]->enemy_attacking_control1()) --count;
  }
  move = false;
}

void Wave::draw()
{
  if (show_rect_) surface->put_rect(Rect(*this), WHITE);
  for (Enemy * e : enemies)
  {
    e->draw();
  }
}

void Wave::decrease(int t)
{
  enemies[t]->switch_hit_status();
  if (enemies[t]->is_attacking()) count--;
  enemies[t]->counter = 1;
}

void Wave::reset()
{
  ++wave_amount;
  if (wave_amount <= 10)
  {
    RANDOM_FOR_ENEMY = 2500 - (wave_amount * 200);
    RANDOM_FOR_FLAG = 3500 - (wave_amount * 200);
  }
  else
{
    RANDOM_FOR_ENEMY = 200;
    RANDOM_FOR_FLAG = 300;
  }
  coming_in = true;
  x = 0;
  y = 100;
  w = 440;
  h = 260;
  enemies.resize(46);
  for (int i = 0; i < 2; ++i)
  {
    if (enemies[i] != nullptr) delete enemies[i];
    enemies[i] = new Flag;
    enemies[i]->breaktime = 20;
    enemies[i]->x() = (i * 135) + 135;
    enemies[i]->dx() = 0;
    enemies[i]->y() = -32;
    enemies[i]->save(enemies[i]->x(), y);
  }
  for (int i = 2; i < 5; ++i)
  {
    if (enemies[i] != nullptr) delete enemies[i];
    enemies[i] = new Red(enemies[0]);
    enemies[i]->breaktime = 55;
    enemies[i]->dx() = 0;
    enemies[i]->x() = ((i-2) * 45) + 90;
    enemies[i]->y() = -32;
    enemies[i]->save(enemies[i]->x(), y + 45);
  }
  for (int i = 5; i < 8; ++i)
  {
    if (enemies[i] != nullptr) delete enemies[i];
    enemies[i] = new Red(enemies[1]);
    enemies[i]->breaktime = 55;
    enemies[i]->dx() = 0;
    enemies[i]->x() = ((i-2) * 45) + 90;
    enemies[i]->y() = -32;
    enemies[i]->save(enemies[i]->x(), y + 45);
  }
  for (int i = 8; i < 16; ++i)
  {
    if (enemies[i] != nullptr) delete enemies[i];
    enemies[i] = new Purple;
    enemies[i]->breaktime = 75;
    enemies[i]->dx() = 0;
    enemies[i]->x() = (i % 8 * 45) + 45;
    enemies[i]->y() = -32;
    enemies[i]->save(enemies[i]->x(), y + 90);
  }
  for (int i = 16; i < 46; ++i)
  {
    if (enemies[i] != nullptr) delete enemies[i];
    enemies[i] = new Blue;
    int j = i % 3;
    enemies[i]->breaktime = j * 35 + 100;
    enemies[i]->dx() = 0;
    enemies[i]->x() = (i % 10 * 45);
    enemies[i]->y() = -32;
    enemies[i]->save(enemies[i]->x(), y + 135 + j * 45);
  }
  wave_has_died = false;
}
