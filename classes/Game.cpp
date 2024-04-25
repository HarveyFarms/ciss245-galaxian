#include "Game.h"


Surface * Object::s_(NULL);

Game::Game() :
  user_clicked(false),
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
  game_music(Music("sounds/GameLoop.ogg")),
  shoot(Sound("sounds/laser.wav")),
  explode(Sound("sounds/explosion.wav")),
  timer(0),
  amount_ships(3),
  paused(false),
  reboot_ship(false),
  done_typing(false),
  count(0),
  waiting(false),
  wait(0),
  pressed(false),
  clicked(false),
  counter_for_shot(0),
  m_key_pressed(false),
  muted(START_MUTED)
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
  if (!muted)
    game_music.play();
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
  game_music.stop();

  delay(50);
}

void Game::get_input()
{
  if (!m_key_pressed && kp[SDLK_m]) {
    muted = !muted;
    m_key_pressed = true;

    if (muted) {
      game_music.stop();
    }
    else {
      game_music.play();
    }
  }
  else if (m_key_pressed && !kp[SDLK_m])
    m_key_pressed = false;
  if (kp[TAB])
    paused = true;
  else
    paused = false;
  background_input();
  if (playing())
  {
    if (!reboot_ship)
    {
      if (kp[LEFTARROW] && !Galaxip->outside_left() || mouse_x() + 10 < Galaxip->x() && ALLOW_MOUSE_MOVEMENT) Galaxip->dx() = -4;
      else if (kp[RIGHTARROW] && !Galaxip->outside_right() || mouse_x() - 42 > Galaxip->x() && ALLOW_MOUSE_MOVEMENT) Galaxip->dx() = 4;
      else Galaxip->dx() = 0;
      if (kp[SPACE] && !pressed || (mouse_left() && !clicked && ALLOW_MOUSE_SHOOTING && counter_for_shot == 0))
      {
        if (Galaxip->shoot() && !muted)
          shoot.play();
        if (kp[SPACE])
          pressed = true;
        if (mouse_left())
          clicked = true;
      }
      else if (!kp[SPACE] && pressed)
        pressed = false;
      else if (!mouse_left() && clicked)
        clicked = false;
    }
  }
}
void Game::update()
{
  if (counter_for_shot != 0) {
    ++counter_for_shot;
    if (counter_for_shot > 20)
      counter_for_shot = 0;
  }
  if (amount_ships == 0 && !background->game_ended())
  {
    background->game_over_switch();
    amount_ships = 3;
  }
  background->update();
  handle_background();
  if (playing())
  {
    waves->update();
    if (!reboot_ship && timer != 0)
    {
      ++timer;
      if (timer > 120)
      {
        timer = 0;
      }
    }
    if (reboot_ship && !background->game_ended())
    {
      ++timer;
      if (timer > 300)
      {
        reboot_ship = false;
        timer = 1;
        setup_ships();
      }
    }
    else
  {
      Galaxip->update();
      enemy_hits_ship();
      if (!INVINCIBILITY_FOR_SHIP) 
        laser_hits_ship();
    }
    if (!INVINCIBILITY_FOR_ENEMIES) 
      laser_hits_enemy();
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
    Galaxip->draw(reboot_ship);
    waves->draw();
    for (int i = 0; i < explosions.size(); ++i)
    {
      explosions[i].draw();
      if (explosions[i].finished)
        explosions.erase(explosions.begin() + (i--));
    }
  }

  surface->unlock();
  surface->flip();
}
void Game::reset_all()
{
  background->reset();
  if (Galaxip != nullptr) delete Galaxip;
  if (waves != nullptr) delete waves;
  Galaxip = new Ship();
  amount_ships = 3;
  waves = new Wave();
  waves->set_surface(surface);
  setup_ships();
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
    if (first < background->get_score()) return 1;
    f >> z;
    if (f.eof()) return 2;
    f >> second;
    if (second < background->get_score()) return 2;
    f >> z;
    if (f.eof()) return 3;
    f >> third;
    if (third < background->get_score()) return 3;
    f >> z;
    if (f.eof()) return 4;
    f >> fourth;
    if (fourth < background->get_score()) return 4;
    f >> z;
    if (f.eof()) return 5;
    f >> fifth;
    if (fifth < background->get_score()) return 5;
    f >> z;
    if (f.eof()) return 6;
    f >> sixth;
    if (sixth < background->get_score()) return 6;
    f >> z;
    if (f.eof()) return 7;
    f >> seventh;
    if (seventh < background->get_score()) return 7;
    f >> z;
    if (f.eof()) return 8;
    f >> eighth;
    if (eighth < background->get_score()) return 8;
    f >> z;
    if (f.eof()) return 9;
    f >> ninth;
    if (ninth < background->get_score()) return 9;
    f >> z;
    if (f.eof()) return 10;
    f >> tenth;
    if (tenth < background->get_score()) return 10;
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
  background->amnt_lives = amount_ships;
  std::string waves_s = "wave: ";
  std::string waves_sco = std::to_string(waves->wave_amount).c_str();
  background->waves_str() = waves_s + waves_sco;
  background->inc_wave = waves->coming_in;
  if (background->game_ended()) ++count;
  if (waiting)
    ++wait;
  if (wait > 10)
  {
    waiting = false;
    wait = 0;
  }
  if (count > 300)
  {
    if (background->get_score() > 0)
    {
      place = infile();
      background->inputplace(place);
      in.clear();
      background->switch_typing();
      save_score = background->get_score();
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
      if (mouse_on_play())
      {
        background->cursor_y = H / 2 + 90;
      }
      else if (mouse_on_instructions())
      {
        background->cursor_y = H / 2 + 160;
      }
      else if (mouse_on_leader())
      {
        background->cursor_y = H / 2 + 230;
      }
      else if (mouse_on_exit())
      {
        background->cursor_y = H / 2 + 300;
      }
      if (kp[RET] && goto_play() || mouse_on_play() && mouse_left()) {
        background->switch_screen();
        counter_for_shot = 1;
      }
      if (kp[RET] && goto_instructions() || mouse_on_instructions() && mouse_left()) 
        background->switch_instructions();
      if (kp[RET] && goto_leaderboards() || mouse_on_leader() && mouse_left()) 
        background->switch_leaderboards();
      if (mouse_on_exit() && mouse_left())
        user_clicked = true;
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
      if (kp[BACK] || mouse_right()) background->switch_leaderboards();
    }
    else if (background->on_instructions())
    {
      if (kp[BACK] || mouse_right()) background->switch_instructions();
    }
  }
}
void Game::setup_ships()
{
  Galaxip->make();
  Galaxip->y() = H / 2 + 400;
  Galaxip->x() = W / 2 - 150;
  Galaxip->dy() = 0;
  reboot_ship = false;
}
void Game::laser_hits_enemy()
{
  for (int i = 0; i < Galaxip->get_lasers().size(); ++i)
  {
    for (int j = 0; j < waves->get_enemies().size() && i < Galaxip->get_lasers().size(); ++j)
    {
      if (waves->get_enemies()[j]->hit_by_laser(Galaxip->get_lasers()[i]) && !waves->get_enemies()[j]->is_hit)
      {
        if (!muted)
          explode.play();
        RANDOM_FOR_ENEMY -= 75;
        RANDOM_FOR_FLAG -= 100;
        if (waves->get_enemies()[j]->is_attacking()) 
        {
          if (!waves->get_enemies()[j]->is_flag())
            update_score(waves->get_enemies()[j]->amount * 2);
          else
            update_score(150);
        }
        else update_score(waves->get_enemies()[j]->amount);
        Galaxip->cleanup(i--);
        explosions.push_back(Explosion(waves->get_enemies()[j]->x(), waves->get_enemies()[j]->y()));
        waves->decrease(j--);
      }
    }
  }
}
void Game::enemy_hits_ship()
{
  bool invincibility_mode = !reboot_ship && timer != 0;
  for (int j = 0; j < waves->get_enemies().size(); ++j)
  {
    if (Galaxip->collided_w_object(waves->get_enemies()[j]) && !waves->get_enemies()[j]->is_hit && amount_ships > 0 && !invincibility_mode)
    {
      if (!INVINCIBILITY_FOR_SHIP || !INVINCIBILITY_FOR_ENEMIES) {
        if (!muted)
          explode.play();
      }
      if (!INVINCIBILITY_FOR_ENEMIES)
      {
        RANDOM_FOR_ENEMY -= 40;
        RANDOM_FOR_FLAG -= 50;
        explosions.push_back(Explosion(waves->get_enemies()[j]->x(), waves->get_enemies()[j]->y()));
        waves->decrease(j--);
      }
      if (!INVINCIBILITY_FOR_SHIP)
      {
        explosions.push_back(Explosion(Galaxip->x(), Galaxip->y()));
        --amount_ships;
        reboot_ship = true;
      }
    }
  }
}
void Game::laser_hits_ship()
{
  bool invincibility_mode = !reboot_ship && timer != 0;
  for (int i = 0; i < waves->get_enemies().size(); ++i)
  {
    for (int j = 0; j < waves->get_enemies()[i]->get_lasers().size(); ++j)
    {
      if (Galaxip->hit_by_laser(waves->get_enemies()[i]->get_lasers()[j]) && amount_ships > 0 && !invincibility_mode)
      {
        if (!muted)
          explode.play();
        explosions.push_back(Explosion(Galaxip->x(), Galaxip->y()));
        waves->get_enemies()[i]->cleanup(j--);
        --amount_ships;
        reboot_ship = true;
      }
    }
  }
}
