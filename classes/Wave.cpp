#include "Wave.h"

Wave::Wave()
  : wave_has_died(false), wave_dead(false),
  dead_counter(0),
  coming_in(false), wave_amount(STARTING_WAVE), 
  move(false), show_rect_(false), dx(1), count(0)
{
  for (int i = 0; i < 10; ++i)
  {
    sections[i] = true;
  }
  x = 0;
  y = 100;
  w = 440;
  h = 260;
  enemies.resize(46);
  for (int i = 0; i < 30; ++i)
  {
    enemies[i] = new Blue;
    if (!SPAWN_BLUES) enemies[i]->is_hit = true;
    int j = i % 3;
    enemies[i]->x() = (i % 10 * 45);
    enemies[i]->y() = y + 135 + j * 45;
    enemies[i]->save(enemies[i]->x(), y + 135 + j * 45);
  }
  for (int i = 30; i < 38; ++i)
  {
    enemies[i] = new Purple;
    if (!SPAWN_PURPLES) enemies[i]->is_hit = true;
    enemies[i]->x() = (i % 10 * 45) + 45;
    enemies[i]->y() = y + 90;
    enemies[i]->save(enemies[i]->x(), y + 90);
  }
  for (int i = 38; i < 40; ++i)
  {
    enemies[i] = new Flag;
    if (!SPAWN_FLAGS) enemies[i]->is_hit = true;
    enemies[i]->x() = (i % 2 * 135) + 135;
    enemies[i]->y() = y;
    enemies[i]->save(enemies[i]->x(), y);
  }
  for (int i = 40; i < 43; ++i)
  {
    enemies[i] = new Red(enemies[38]);
    if (!SPAWN_REDS) enemies[i]->is_hit = true;
    enemies[i]->x() = ((i%40) * 45) + 90;
    enemies[i]->y() = y + 45;
    enemies[i]->save(enemies[i]->x(), y + 45);
  }
  for (int i = 43; i < 46; ++i)
  {
    enemies[i] = new Red(enemies[39]);
    if (!SPAWN_REDS) enemies[i]->is_hit = true;
    enemies[i]->x() = ((i%40) * 45) + 90;
    enemies[i]->y() = y + 45;
    enemies[i]->save(enemies[i]->x(), y + 45);
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
  if (dead_counter > 150)
    wave_has_died = true;
  if (wave_has_died)
    reset();
  resize();
  if (count >= wave_amount)
    count_checker++;
  else
    count_checker = 0;
  if (count < 0) 
    count = 0;
  if (count_checker > 400) count = 0;
  x += dx;
  if (x <= 0 || x + w >= W)
  {
    move = true;
    if (x <= 0) dx = 1;
    else if (x + w >= W) dx = -1;
  }
  wave_dead = true;
  for (int i = 0; i < enemies.size(); ++i)
  {
    if (!enemies[i]->is_hit && wave_dead)
      wave_dead = false;
    if (enemies[i]->y() == enemies[i]->savey) 
      coming_in = false;
    if (count < wave_amount) // count is for controlling the amnt of enemies on the screen
      enemies[i]->update(move, false);
    else
      enemies[i]->update(move, true);
    if (enemies[i]->enemy_attacking_control0()) ++count;
    if (enemies[i]->enemy_attacking_control1()) --count;
  }
  if (wave_dead)
    ++dead_counter;
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
}

void Wave::reset()
{
  dead_counter = 0;
  for (int i = 0; i < 10; ++i)
  {
    sections[i] = true;
  }
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
  for (int i = 0; i < 30; ++i)
  {
    int j = i % 3;
    enemies[i]->restore();
    if (!SPAWN_BLUES) enemies[i]->is_hit = true;
    enemies[i]->breaktime = j * 35 + 100;
    enemies[i]->dx() = 0;
    enemies[i]->x() = (i % 10 * 45);
    enemies[i]->y() = -32;
    enemies[i]->save(enemies[i]->x(), y + 135 + j * 45);
  }
  for (int i = 30; i < 38; ++i)
  {
    enemies[i]->restore();
    if (!SPAWN_PURPLES) enemies[i]->is_hit = true;
    enemies[i]->breaktime = 75;
    enemies[i]->dx() = 0;
    enemies[i]->x() = (i % 10 * 45) + 45;
    enemies[i]->y() = -32;
    enemies[i]->save(enemies[i]->x(), y + 90);
  }
  for (int i = 38; i < 40; ++i)
  {
    enemies[i]->restore();
    if (!SPAWN_FLAGS) enemies[i]->is_hit = true;
    enemies[i]->breaktime = 20;
    enemies[i]->x() = (i % 2 * 135) + 135;
    enemies[i]->dx() = 0;
    enemies[i]->y() = -32;
    enemies[i]->save(enemies[i]->x(), y);
  }
  for (int i = 40; i < 43; ++i)
  {
    enemies[i]->restore();
    if (!SPAWN_REDS) enemies[i]->is_hit = true;
    enemies[i]->change_master(enemies[38]);
    enemies[i]->on_own = false;
    enemies[i]->breaktime = 55;
    enemies[i]->dx() = 0;
    enemies[i]->x() = ((i%40) * 45) + 90;
    enemies[i]->y() = -32;
    enemies[i]->save(enemies[i]->x(), y + 45);
  }
  for (int i = 43; i < 46; ++i)
  {
    enemies[i]->restore();
    if (!SPAWN_REDS) enemies[i]->is_hit = true;
    enemies[i]->change_master(enemies[39]);
    enemies[i]->on_own = false;
    enemies[i]->breaktime = 55;
    enemies[i]->dx() = 0;
    enemies[i]->x() = ((i%40) * 45) + 90;
    enemies[i]->y() = -32;
    enemies[i]->save(enemies[i]->x(), y + 45);
  }
  wave_has_died = false;
}
void Wave::resize()
{
  int amount = 0;
  if (enemies[0]->is_hit && enemies[10]->is_hit && enemies[20]->is_hit)
  {
    if (sections[0]) ++amount;
    sections[0] = false;
    if (enemies[30]->is_hit && enemies[1]->is_hit && enemies[11]->is_hit && enemies[21]->is_hit)
    {
      if (sections[1]) ++amount;
      sections[1] = false;
      if (enemies[38]->is_hit && enemies[31]->is_hit && enemies[2]->is_hit && enemies[12]->is_hit && enemies[22]->is_hit)
      {
        if (sections[2]) ++amount;
        sections[2] = false;
        if (enemies[44]->is_hit && enemies[39]->is_hit && enemies[32]->is_hit && enemies[3]->is_hit && enemies[13]->is_hit && enemies[23]->is_hit)
        {
          if (sections[3]) ++amount;
          sections[3] = false;
          if (enemies[40]->is_hit && enemies[33]->is_hit && enemies[4]->is_hit && enemies[14]->is_hit && enemies[24]->is_hit)
          {
            if (sections[4]) ++amount;
            sections[4] = false;
            if (enemies[34]->is_hit && enemies[41]->is_hit && enemies[5]->is_hit && enemies[15]->is_hit && enemies[25]->is_hit)
            {
              if (sections[5]) ++amount;
              sections[5] = false;
              if (enemies[35]->is_hit && enemies[42]->is_hit && enemies[45]->is_hit && enemies[6]->is_hit && enemies[16]->is_hit && enemies[26]->is_hit)
              {
                if (sections[6]) ++amount;
                sections[6] = false;
                if (enemies[43]->is_hit && enemies[36]->is_hit && enemies[7]->is_hit && enemies[17]->is_hit && enemies[27]->is_hit)
                {
                  if (sections[7]) ++amount;
                  sections[7] = false;
                  if (enemies[37]->is_hit && enemies[8]->is_hit && enemies[18]->is_hit && enemies[28]->is_hit)
                  {
                    if (sections[8]) ++amount;
                    sections[8] = false;
                    if (enemies[9]->is_hit && enemies[19]->is_hit && enemies[29]->is_hit)
                    {
                      if (sections[9]) ++amount;
                      sections[9] = false;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  x += amount * 45;
  w -= amount * 45;
  amount = 0;
  if (enemies[9]->is_hit && enemies[19]->is_hit && enemies[29]->is_hit)
  {
    if (sections[9]) ++amount;
    sections[9] = false;
    if (enemies[37]->is_hit && enemies[8]->is_hit && enemies[18]->is_hit && enemies[28]->is_hit)
    {
      if (sections[8]) ++amount;
      sections[8] = false;
      if (enemies[43]->is_hit && enemies[36]->is_hit && enemies[7]->is_hit && enemies[17]->is_hit && enemies[27]->is_hit)
      {
        if (sections[7]) ++amount;
        sections[7] = false;
        if (enemies[35]->is_hit && enemies[42]->is_hit && enemies[45]->is_hit && enemies[6]->is_hit && enemies[16]->is_hit && enemies[26]->is_hit)
        {
          if (sections[6]) ++amount;
          sections[6] = false;
          if (enemies[34]->is_hit && enemies[41]->is_hit && enemies[5]->is_hit && enemies[15]->is_hit && enemies[25]->is_hit)
          {
            if (sections[5]) ++amount;
            sections[5] = false;
            if (enemies[40]->is_hit && enemies[33]->is_hit && enemies[4]->is_hit && enemies[14]->is_hit && enemies[24]->is_hit)
            {
              if (sections[4]) ++amount;
              sections[4] = false;
              if (enemies[44]->is_hit && enemies[39]->is_hit && enemies[32]->is_hit && enemies[3]->is_hit && enemies[13]->is_hit && enemies[23]->is_hit)
              {
                if (sections[3]) ++amount;
                sections[3] = false;
                if (enemies[38]->is_hit && enemies[31]->is_hit && enemies[2]->is_hit && enemies[12]->is_hit && enemies[22]->is_hit)
                {
                  if (sections[2]) ++amount;
                  sections[2] = false;
                  if (enemies[30]->is_hit && enemies[1]->is_hit && enemies[11]->is_hit && enemies[21]->is_hit)
                  {
                    if (sections[1]) ++amount;
                    sections[1] = false;
                    if (enemies[0]->is_hit && enemies[10]->is_hit && enemies[20]->is_hit)
                    {
                      if (sections[0]) ++amount;
                      sections[0] = false;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  w -= amount * 45;
}
