#include "Game.h"

Surface * Object::s_(NULL);

Game::Game() :
  background(new Background()),
  Galaxip(new Ship()),
  waves(new Wave()),
  save_score(0),
  place(0),
  in_image(new Image((Font("fonts/Emulogic-zrEw.ttf", 48)).render(in.c_str(), WHITE))),
  cursor(new Rect(10, 10, 10, 10)),
  blink(false),
  counter(0),
  surface(new Surface(W, H)),
  kp(get_keypressed()),
  keyboard(event),
  paused(false),
  done_typing(false),
  count(0),
  waiting(false),
  wait(0),
  pressed(false)
{
  srand((unsigned int) time(nullptr));
  Star::set_surface(surface);
  Background::set_surface(surface);
  Object::set_surface(surface);
  waves->set_surface(surface);
  setup_ships();
}
Game::~Game() 
{ 
  if (background != nullptr) delete background; 
  if (surface != nullptr) delete surface; 
  if (in_image != nullptr) delete in_image; 
  if (cursor != nullptr) delete cursor; 
  if (Galaxip != nullptr) delete Galaxip;
  if (waves != nullptr) delete waves;
}


void Game::run()
{
  int start, end, dt, RATE = s60FPS;
  while (GAME_IS_RUNNING && !user_quits())
  {
    start = getTicks();

    get_input();

    if (!paused)
    {
      update();

      draw();

      end = getTicks();
      dt = RATE - end + start;
      if (dt > 0) delay(dt);
    }
  }

  delay(50);
}

void Game::get_input()
{
  background_input();
  if (playing())
  {
    if (kp[LEFTARROW] && !Galaxip->outside_left()) Galaxip->dx() = -2;
    else if (kp[RIGHTARROW] && !Galaxip->outside_right()) Galaxip->dx() = 2;
    else Galaxip->dx() = 0;
    if (kp[UPARROW] && !pressed)
    {
      Galaxip->shoot();
      pressed = true;
    }
    else if (!kp[UPARROW] && pressed)
    {
      pressed = false;
    }
  }
    /* if (!background->game_ended()) */
    /* { */
    /*   if (kp[ESC]) background->game_over_switch(); */
    /* } */
}
void Game::update()
{
  background->update();
  handle_background();
  if (playing())
  {
    Galaxip->update();
    waves->update();
    for (int i = 0; i < Galaxip->get_lasers().size(); ++i)
    {
      for (int j = 0; j < waves->get_enemies().size() && i < Galaxip->get_lasers().size(); ++j)
      {
        if (waves->get_enemies()[j]->hit_by_laser(Galaxip->get_lasers()[i]))
        {
          if (waves->get_enemies()[j]->is_attacking()) 
          {
            if (!waves->get_enemies()[j]->is_flag())
              update_score(waves->get_enemies()[j]->amount * 2);
           else
              update_score(150);
          }
          else update_score(waves->get_enemies()[j]->amount);
          Galaxip->cleanup(i--);
          waves->cleanup(j--);
        }
      }
    }
  }
}
void Game::draw()
{
  surface->lock();
  surface->fill(BLACK);

  // drawing objects in accordance with how they show up on screen
  background->draw();
  if (background->is_typing())
  {
    surface->put_image(*in_image, in_image->rect());
    if (!blink) surface->put_rect(*cursor, WHITE);
  }
  if (playing())
  {
    Galaxip->draw();
    waves->draw();
  }

  surface->unlock();
  surface->flip();
}
void Game::reset_all()
{
  background->reset();
}
int Game::infile()
{
  std::ifstream f("scores.txt", std::ios::in);
  if (f.is_open())
  {
    int first, second, third, fourth, fifth, sixth, seventh, eighth, ninth, tenth;
    char z[4];
    f >> z;
    f >> first;
    if (first < background->get_hiscore()) return 1;
    f >> z;
    if (f.eof()) return 2;
    f >> second;
    if (second < background->get_hiscore()) return 2;
    f >> z;
    if (f.eof()) return 3;
    f >> third;
    if (third < background->get_hiscore()) return 3;
    f >> z;
    if (f.eof()) return 4;
    f >> fourth;
    if (fourth < background->get_hiscore()) return 4;
    f >> z;
    if (f.eof()) return 5;
    f >> fifth;
    if (fifth < background->get_hiscore()) return 5;
    f >> z;
    if (f.eof()) return 6;
    f >> sixth;
    if (sixth < background->get_hiscore()) return 6;
    f >> z;
    if (f.eof()) return 7;
    f >> seventh;
    if (seventh < background->get_hiscore()) return 7;
    f >> z;
    if (f.eof()) return 8;
    f >> eighth;
    if (eighth < background->get_hiscore()) return 8;
    f >> z;
    if (f.eof()) return 9;
    f >> ninth;
    if (ninth < background->get_hiscore()) return 9;
    f >> z;
    if (f.eof()) return 10;
    f >> tenth;
    if (tenth < background->get_hiscore()) return 10;
    else return 0;

    f.close();
  }
  return 1;
}
void Game::putinfile(int place)
{
  std::ifstream input("scores.txt", std::ios::in);
  std::string copy;
  std::string name, score;
  int cplace = 1;
  if (input.is_open())
  {
    while (input >> name >> score)
    {
      if (cplace == place)
      {
        copy += in + ' ' + std::to_string(save_score).c_str() + '\n';
      }
      copy += name + ' ' + score + '\n';
      ++cplace;
    }
    if (cplace == place)
    {
      copy += in + ' ' + std::to_string(save_score).c_str() + '\n';
    }
  }
  else
{
    copy += in + ' ' + std::to_string(save_score).c_str() + '\n';
  }
  input.close();
  std::ofstream output("scores.txt", std::ios::out);
  output << copy;
  output.flush();
  output.close();
  }
void Game::handle_background()
{
  if (background->game_ended()) ++count;
  if (waiting)
  {
    ++wait;
  }
  if (wait > 10)
  {
    waiting = false;
    wait = 0;
  }
  if (count > 300)
  {
    if (background->get_hiscore() > 0)
    {
      place = infile();
      background->inputplace(place);
      in.clear();
      background->switch_typing();
      save_score = background->get_hiscore();
    }
    background->game_over_switch();
    reset_all();
    count = 0;
  }
  if (done_typing)
  {
    putinfile(place);
    done_typing = false;
  }
  if (in_image != nullptr) delete in_image;
  if (cursor != nullptr) delete cursor;
  in_image = new Image((Font("fonts/Emulogic-zrEw.ttf", 48)).render(in.c_str(), WHITE));
  in_image->rect().x = W / 2 - 100;
  in_image->rect().y = H / 2;
  cursor = new Rect(in_image->rect().x + 2 + (50 * in.size()), in_image->rect().y + 5, 2, 55);
  counter++;
  if (counter > 30)
  {
    blink = !blink;
    counter = 0;
  }
}
void Game::background_input()
{
  keyboard.update(event);
  if (background->is_typing())
  {
    if (event.type() == SDL_KEYDOWN && !waiting)
    {
      if (kp[BACK])
      {
        if (in.size()) in.pop_back();
      }
      else if (in.size() < 3)
      {
        in += char(keyboard.get_sym());
      }
      else if (kp[RET] && in.size())
      {
        background->switch_typing();
        done_typing = true;
      }
      delay(150);
    }
  }
  else
  {
    if (background->on_starting_screen())
    {
      if (kp[RET] && goto_play()) background->switch_screen();
      if (kp[RET] && goto_instructions()) background->switch_instructions();
      if (kp[RET] && goto_leaderboards()) background->switch_leaderboards();
      if (kp[UPARROW] && !waiting) 
      {
        background->cursor_up();
        waiting = true;
      }
      if (kp[DOWNARROW] && !waiting) 
      {
        background->cursor_down();
        waiting = true;
      }
    }
    else if (background->on_leaderboards())
    {
      if (kp[BACK]) background->switch_leaderboards();
    }
    else if (background->on_instructions())
    {
      if (kp[BACK]) background->switch_instructions();
    }
  }
}
void Game::setup_ships()
{
  Galaxip->make();
  Galaxip->y() = H / 2 + 400;
  Galaxip->x() = W / 2 - 150;
  Galaxip->dy() = 0;
}
