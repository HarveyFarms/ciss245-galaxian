#include "Background.h"

Surface * Star::s_ = NULL;
Surface * Background::surface = NULL;

Background::Background() :
  starting_screen(true),
  leaderboards_screen(false),
  instructions_screen(false),
  typing(false),
  small("fonts/Emulogic-zrEw.ttf", 12),
  middle("fonts/Emulogic-zrEw.ttf", 24),
  big("fonts/Emulogic-zrEw.ttf", 48),
  waves_string("wave: 1"),
  wave_count(new Image(small.render(waves_string.c_str(), WHITE))),
  incoming_wave(big.render("INCOMING WAVE", RED)),
  lives0("images/GalaxianGalaxip.gif"),
  lives1("images/GalaxianGalaxip.gif"),
  lives2("images/GalaxianGalaxip.gif"),
  inc_wave(false),
  high(small.render("hi-score", ORANGE)),
  high_score(0),
  high_s(new Image(small.render(std::to_string(score_score).c_str(), WHITE))),
  score(small.render("score", ORANGE)),
  score_score(0),
  score_s(new Image(small.render(std::to_string(score_score).c_str(), WHITE))),
  name(small.render("Ryan Harvey", GRAY)),
  madeby(small.render("made by:", GRAY)),
  gameover(big.render("GAME OVER", RED)),
  keyinput0(NULL),
  keyinput1(small.render("Please pick a 3-letter username to save score with", WHITE)),
  galactic_heroes(small.render("galactic heroes", BLUE)),
  top10(small.render("- top 10 -", GREEN)),
  pos_score_name(small.render("pos             score             name", WHITE)),
  cursor(NULL),
  Iinstructions(NULL),
  play(new Image(big.render("Play", WHITE))),
  instructions(new Image(big.render("Instructions", GRAY))),
  leaderboards(new Image(big.render("Leaderboards", GRAY))),
  exit(new Image(big.render("exit", GRAY))),
  counter(0),
  we_are_the_galaxians(middle.render("we are the galaxians", RED)),
  mission_destroy_aliens(middle.render("mission: destroy aliens", RED)),
  score_advance_table(middle.render("- score advance table -", LITEPURP)),
  convoy_charger(middle.render("convoy      charger", CYAN)),
  flagship(NULL),
  flag_moving(false),
  red_escort(NULL),
  red_moving(false),
  purple(NULL),
  purple_moving(false),
  blue(NULL),
  blue_moving(false),
  flagship_points(middle.render("60         150 pts", WHITE)),
  red_escort_points(middle.render("50         100 pts", WHITE)),
  purple_points(middle.render("40         80 pts", WHITE)),
  blue_points(middle.render("30         60 pts", WHITE)),
  first(small.render("1st", WHITE)),
  first_score(NULL),
  first_name(NULL),
  second(small.render("2nd", WHITE)),
  second_score(NULL),
  second_name(NULL),
  third(small.render("3rd", WHITE)),
  third_score(NULL),
  third_name(NULL),
  fourth(small.render("4th", WHITE)),
  fourth_score(NULL),
  fourth_name(NULL),
  fifth(small.render("5th", WHITE)),
  fifth_score(NULL),
  fifth_name(NULL),
  sixth(small.render("6th", WHITE)),
  sixth_score(NULL),
  sixth_name(NULL),
  seventh(small.render("7th", WHITE)),
  seventh_score(NULL),
  seventh_name(NULL),
  eighth(small.render("8th", WHITE)),
  eighth_score(NULL),
  eighth_name(NULL),
  ninth(small.render("9th", WHITE)),
  ninth_score(NULL),
  ninth_name(NULL),
  tenth(small.render("10th", WHITE)),
  tenth_score(NULL),
  tenth_name(NULL),
  galaxian_logo(new Image("images/biggalaxian.png")),
  game_over(false)
{
  stars.resize(100);
  setup_text();
  setup_rects();
  cursor_y = H / 2 + 90;
}
Background::~Background()
{
  if (galaxian_logo != nullptr) delete galaxian_logo;
  if (high_s != nullptr) delete high_s;
  if (score_s != nullptr) delete score_s;
  if (keyinput0 != nullptr) delete keyinput0;
  if (first_name != nullptr) delete first_name;
  if (first_score != nullptr) delete first_score;
  if (second_name != nullptr) delete second_name;
  if (second_score != nullptr) delete second_score;
  if (third_name != nullptr) delete third_name;
  if (third_score != nullptr) delete third_score;
  if (fourth_name != nullptr) delete fourth_name;
  if (fourth_score != nullptr) delete fourth_score;
  if (fifth_name != nullptr) delete fifth_name;
  if (fifth_score != nullptr) delete fifth_score;
  if (sixth_name != nullptr) delete sixth_name;
  if (sixth_score != nullptr) delete sixth_score;
  if (seventh_name != nullptr) delete seventh_name;
  if (seventh_score != nullptr) delete seventh_score;
  if (eighth_name != nullptr) delete eighth_name;
  if (eighth_score != nullptr) delete eighth_score;
  if (ninth_name != nullptr) delete ninth_name;
  if (ninth_score != nullptr) delete ninth_score;
  if (tenth_name != nullptr) delete tenth_name;
  if (tenth_score != nullptr) delete tenth_score;
  if (cursor != nullptr) delete cursor;
  if (Iinstructions != nullptr) delete Iinstructions;
  if (play != nullptr) delete play;
  if (instructions != nullptr) delete instructions;
  if (leaderboards != nullptr) delete leaderboards;
  if (exit != nullptr) delete exit;
  if (flagship != nullptr) delete flagship;
  if (red_escort != nullptr) delete red_escort;
  if (purple != nullptr) delete purple;
  if (blue != nullptr) delete blue;
  if (wave_count != nullptr) delete wave_count;
}


void Background::set_surface(Surface * s)
{
  Background::surface = s;
}


void Background::update()
{
  for (Star & s : stars)
  {
    s.update();
  }
  if (starting_screen || instructions_screen || leaderboards_screen)
  {
    if (Iinstructions != nullptr) delete Iinstructions;
    if (starting_screen)
    {
      Iinstructions = new Image(small.render("arrow keys to navigate, enter to select", WHITE));
      Iinstructions->rect().x = W / 2 - 250;
      Iinstructions->rect().y = H / 2 + 430;
    }
    else
  {
      Iinstructions = new Image(small.render("backspace to return to starting screen", WHITE));
      Iinstructions->rect().x = W / 2 - 250;
      Iinstructions->rect().y = H / 2 + 430;
    }
  }
  if (score_s != nullptr) delete score_s;
  if (high_s != nullptr) delete high_s;
  if (wave_count != nullptr) delete wave_count;
  wave_count = new Image(small.render(waves_string.c_str(), WHITE));
  high_s = new Image(small.render(std::to_string(high_score).c_str(), WHITE));
  score_s = new Image(small.render(std::to_string(score_score).c_str(), WHITE));
  wave_count->rect().x = 5;
  wave_count->rect().y = H - 20;
  high_s->rect().x = high.rect().x;
  high_s->rect().y = high.rect().y + 15;
  score_s->rect().x = score.rect().x;
  score_s->rect().y = score.rect().y + 15;
  if (score_score > high_score) high_score = score_score;
  if (leaderboards_screen) get_names();
  if (leaderboards_screen) update_score_section();
  if (starting_screen) update_cursor_section();
  if (instructions_screen) update_ships();
}

void Background::draw()
{
  if (typing) 
  {
    surface->put_image(*keyinput0, keyinput0->rect());
    surface->put_image(keyinput1, keyinput1.rect());
  }
  else
{
    for (Star & s : stars)
    {
      s.draw();
    }
    if (game_over) surface->put_image(gameover, gameover.rect());
    else if (starting_screen)
    {
    surface->put_image(name, name.rect());
    surface->put_image(*galaxian_logo, galaxian_logo->rect());
    surface->put_image(madeby, madeby.rect());


    draw_cursor_section();
    surface->put_image(*Iinstructions, Iinstructions->rect());
  }
    else if (leaderboards_screen)
    {
      draw_score_section();
      surface->put_image(*Iinstructions, Iinstructions->rect());
    }
    else if (instructions_screen)
    {
      surface->put_image(we_are_the_galaxians, we_are_the_galaxians.rect());
      surface->put_image(mission_destroy_aliens, mission_destroy_aliens.rect());
      surface->put_image(score_advance_table, score_advance_table.rect());
      surface->put_image(convoy_charger, convoy_charger.rect());
      if (!flag_moving) surface->put_image(flagship_points, flagship_points.rect());
      if (!red_moving) surface->put_image(red_escort_points, red_escort_points.rect());
      if (!purple_moving) surface->put_image(purple_points, purple_points.rect());
      if (!blue_moving) surface->put_image(blue_points, blue_points.rect());
      draw_ships();
      surface->put_image(*Iinstructions, Iinstructions->rect());
    }
    else
  {
      if (inc_wave) 
        surface->put_image(incoming_wave, incoming_wave.rect());
      if (amnt_lives > 0)
      {
        surface->put_image(lives2, lives2.rect());
        if (amnt_lives > 1)
        {
          surface->put_image(lives1, lives1.rect());
          if (amnt_lives > 2)
            surface->put_image(lives0, lives0.rect());
        }
      }
      surface->put_image(name, name.rect());
      surface->put_image(*galaxian_logo, galaxian_logo->rect());
      surface->put_image(*high_s, high_s->rect());
      surface->put_image(*score_s, score_s->rect());
      surface->put_image(high, high.rect());
      surface->put_rect(high_rect, ORANGE);
      surface->put_image(score, score.rect());
      surface->put_rect(score_rect, ORANGE);
      surface->put_image(*wave_count, wave_count->rect());
    }
  }
}


void Background::setup_text()
{
  gameover.rect().x = W / 2 - 225;
  gameover.rect().y = H / 2 - 100;
  incoming_wave.rect().x = W / 2 - 325;
  incoming_wave.rect().y = H / 2 - 100;
  lives0.rect().x = W / 2 + 240;
  lives0.rect().y = H - 35;
  lives1.rect().x = W / 2 + 280;
  lives1.rect().y = H - 35;
  lives2.rect().x = W / 2 + 320;
  lives2.rect().y = H - 35;
  keyinput1.rect().x = W / 2 - 300;
  keyinput1.rect().y = H / 2 - 100;
  if (starting_screen)
  {
    if (galaxian_logo != nullptr) delete galaxian_logo;
    galaxian_logo = new Image("images/biggalaxian.png");
    galaxian_logo->rect().x = W / 2 - 225;
    galaxian_logo->rect().y = H / 2 - 200;
    name.rect().x = W / 2 + 80;
    name.rect().y = H / 2 - 60;
    madeby.rect().x = W / 2 - 20;
    madeby.rect().y = H / 2 - 60;

    galactic_heroes.rect().x = W / 2 - 100;
    galactic_heroes.rect().y = 25;
    top10.rect().x = W / 2 - 70;
    top10.rect().y = 70;
    pos_score_name.rect().x = W / 2 - 235;
    pos_score_name.rect().y = 115;

  }
  else if (instructions_screen)
  {
    we_are_the_galaxians.rect().x = W / 2 - 250;
    we_are_the_galaxians.rect().y = H / 2 - 300;
    mission_destroy_aliens.rect().x = W / 2 - 275;
    mission_destroy_aliens.rect().y = H / 2 - 225;
    score_advance_table.rect().x = W / 2 - 280;
    score_advance_table.rect().y = H / 2 - 100;
    convoy_charger.rect().x = W / 2 - 250;
    convoy_charger.rect().y = H / 2 - 50;
    flagship_points.rect().x = W / 2 - 200;
    flagship_points.rect().y = H / 2 + 25;
    red_escort_points.rect().x = W / 2 - 200;
    red_escort_points.rect().y = H / 2 + 100;
    purple_points.rect().x = W / 2 - 200;
    purple_points.rect().y = H / 2 + 175;
    blue_points.rect().x = W / 2 - 200;
    blue_points.rect().y = H / 2 + 250;
  }
  else
{
    if (galaxian_logo != nullptr) delete galaxian_logo;
    galaxian_logo = new Image("images/galaxian.png");
    high.rect().x = 10;
    high.rect().y = 5;
    high_s->rect().x = high.rect().x;
    high_s->rect().y = high.rect().y - 30;
    score.rect().x = W - 100;
    score.rect().y = 5;
    score_s->rect().x = score.rect().x;
    score_s->rect().y = score.rect().y - 30;
    name.rect().x = W / 2 - 80;
    name.rect().y = H - 20;
    galaxian_logo->rect().x = W / 2 - 100;
    galaxian_logo->rect().y = 5;
    wave_count->rect().x = 5;
    wave_count->rect().y = H - 20;
  }
}


void Background::setup_rects()
{
  if (!starting_screen)
  {
    high_rect.x = 10;
    high_rect.y = 20;
    high_rect.w = 96;
    high_rect.h = 2;

    score_rect.x = W - 100;
    score_rect.y = 20;
    score_rect.w = 60;
    score_rect.h = 2;
  }
  else
{
    pos_r.x = W / 2 - 234;
    first.rect().x = pos_r.x - 3;
    second.rect().x = pos_r.x - 3;
    third.rect().x = pos_r.x - 3;
    fourth.rect().x = pos_r.x - 3;
    fifth.rect().x = pos_r.x - 3;
    sixth.rect().x = pos_r.x - 3;
    seventh.rect().x = pos_r.x - 3;
    eighth.rect().x = pos_r.x - 3;
    ninth.rect().x = pos_r.x - 3;
    tenth.rect().x = pos_r.x - 3;
    pos_r.y = 130;
    first.rect().y = pos_r.y + 40;
    second.rect().y = pos_r.y + 120;
    third.rect().y = pos_r.y + 200;
    fourth.rect().y = pos_r.y + 280;
    fifth.rect().y = pos_r.y + 360;
    sixth.rect().y = pos_r.y + 440;
    seventh.rect().y = pos_r.y + 520;
    eighth.rect().y = pos_r.y + 600;
    ninth.rect().y = pos_r.y + 680;
    tenth.rect().y = pos_r.y + 760;
    pos_r.w = 35;
    pos_r.h = 2;

    score_r.x = W / 2 - 42;
    score_r.y = 130;
    score_r.w = 59;
    score_r.h = 2;

    name_r.x = W / 2 + 174;
    name_r.y = 130;
    name_r.w = 47;
    name_r.h = 2;
  }
}

Star::Star() :
  x(rand() % W), y(rand() % H), dx(0), dy(1), 
  r(rand() % 256), g(rand() % 256), b(rand() % 256),
  timer(0), on_screen(true)
{}


void Star::update()
{
  if (on_screen)
  {
    if (rand() % 1000 == 0) on_screen = false;
    if (y + 3 >= H)
    {
      y = 0;
      x = rand() % W;
    }
    y += dy;
    x += dx;
  }
  else
{
    timer++;
    if (y + 3 >= H)
    {
      y = 0;
      x = rand() % W;
    }
    y += dy;
    x += dx;
    if (timer > 100)
    {
      on_screen = true;
      timer = 0;
    }
  }
}


void Star::draw()
{
  if (on_screen)
  {
    for (int i = 0; i < 2; ++i)
    {
      for (int j = 0; j < 2; ++j)
      {
        s_->put_pixel(x + i, y + j, r, g, b);
      }
    }
  }
}


void Star::set_surface(Surface * s)
{
  Star::s_ = s;
}
void Background::reset()
{
  switch_screen();
  score_score = 0;
  high_score = 0;
}
void Background::draw_score_section()
{
  surface->put_image(galactic_heroes, galactic_heroes.rect());
  surface->put_image(top10, top10.rect());
  surface->put_image(pos_score_name, pos_score_name.rect());
  surface->put_rect(pos_r, WHITE);
  surface->put_rect(score_r, WHITE);
  surface->put_rect(name_r, WHITE);
  surface->put_image(first, first.rect());
  surface->put_image(*first_name, first_name->rect());
  surface->put_image(*first_score, first_score->rect());
  surface->put_image(second, second.rect());
  surface->put_image(*second_name, second_name->rect());
  surface->put_image(*second_score, second_score->rect());
  surface->put_image(third, third.rect());
  surface->put_image(*third_name, third_name->rect());
  surface->put_image(*third_score, third_score->rect());
  surface->put_image(fourth, fourth.rect());
  surface->put_image(*fourth_name, fourth_name->rect());
  surface->put_image(*fourth_score, fourth_score->rect());
  surface->put_image(fifth, fifth.rect());
  surface->put_image(*fifth_name, fifth_name->rect());
  surface->put_image(*fifth_score, fifth_score->rect());
  surface->put_image(sixth, sixth.rect());
  surface->put_image(*sixth_name, sixth_name->rect());
  surface->put_image(*sixth_score, sixth_score->rect());
  surface->put_image(seventh, seventh.rect());
  surface->put_image(*seventh_name, seventh_name->rect());
  surface->put_image(*seventh_score, seventh_score->rect());
  surface->put_image(eighth, eighth.rect());
  surface->put_image(*eighth_name, eighth_name->rect());
  surface->put_image(*eighth_score, eighth_score->rect());
  surface->put_image(ninth, ninth.rect());
  surface->put_image(*ninth_name, ninth_name->rect());
  surface->put_image(*ninth_score, ninth_score->rect());
  surface->put_image(tenth, tenth.rect());
  surface->put_image(*tenth_name, tenth_name->rect());
  surface->put_image(*tenth_score, tenth_score->rect());
}
void Background::update_cursor_section()
{
  if (cursor != nullptr) delete cursor;
  cursor = new Image("images/clicker.png");
  cursor->rect().x = W / 2 - 310;
  cursor->rect().y = cursor_y;
  if (play != nullptr) delete play;
  play = (cursor_y == H / 2 + 90 ? new Image(big.render("Play", WHITE)) : new Image(big.render("Play", GRAY)));
  play->rect().y = H / 2 + 80;
  play->rect().x = W / 2 - 250;
  if (instructions != nullptr) delete instructions;
  instructions = (cursor_y == H / 2 + 160 ? new Image(big.render("Instructions", WHITE)) : new Image(big.render("Instructions", GRAY)));
  instructions->rect().y = H / 2 + 150;
  instructions->rect().x = W / 2 - 258;
  if (leaderboards != nullptr) delete leaderboards;
  leaderboards = (cursor_y == H / 2 + 230 ? new Image(big.render("Leaderboards", WHITE)) : new Image(big.render("Leaderboards", GRAY)));
  leaderboards->rect().y = H / 2 + 220;
  leaderboards->rect().x = W / 2 - 250;
  if (exit != nullptr) delete exit;
  exit = (cursor_y == H / 2 + 300 ? new Image(big.render("Exit", WHITE)) : new Image(big.render("Exit", GRAY)));
  exit->rect().y = H / 2 + 290;
  exit->rect().x = W / 2 - 250;
}
void Background::draw_cursor_section()
{
  surface->put_image(*cursor, cursor->rect());
  surface->put_image(*play, play->rect());
  surface->put_image(*instructions, instructions->rect());
  surface->put_image(*leaderboards, leaderboards->rect());
  surface->put_image(*exit, exit->rect());
}
void Background::get_names()
{
  std::ifstream f("scores.txt", std::ios::in);
  f >> name1;
  if (!f.good())
  {
    name1 = "N/A";
    score1 = "N/A";
    name2 = "N/A";
    score2 = "N/A";
    name3 = "N/A";
    score3 = "N/A";
    name4 = "N/A";
    score4 = "N/A";
    name5 = "N/A";
    score5 = "N/A";
    name6 = "N/A";
    score6 = "N/A";
    name7 = "N/A";
    score7 = "N/A";
    name8 = "N/A";
    score8 = "N/A";
    name9 = "N/A";
    score9 = "N/A";
    name10 = "N/A";
    score10 = "N/A";
    return;
  }
  f >> score1;
  if (!f.good())
  {
    score1 = "N/A";
    name2 = "N/A";
    score2 = "N/A";
    name3 = "N/A";
    score3 = "N/A";
    name4 = "N/A";
    score4 = "N/A";
    name5 = "N/A";
    score5 = "N/A";
    name6 = "N/A";
    score6 = "N/A";
    name7 = "N/A";
    score7 = "N/A";
    name8 = "N/A";
    score8 = "N/A";
    name9 = "N/A";
    score9 = "N/A";
    name10 = "N/A";
    score10 = "N/A";
    return;
  }
  f >> name2;
  if (!f.good())
  {
    name2 = "N/A";
    score2 = "N/A";
    name3 = "N/A";
    score3 = "N/A";
    name4 = "N/A";
    score4 = "N/A";
    name5 = "N/A";
    score5 = "N/A";
    name6 = "N/A";
    score6 = "N/A";
    name7 = "N/A";
    score7 = "N/A";
    name8 = "N/A";
    score8 = "N/A";
    name9 = "N/A";
    score9 = "N/A";
    name10 = "N/A";
    score10 = "N/A";
    return;
  }
  f >> score2;
  if (!f.good())
  {
    score2 = "N/A";
    name3 = "N/A";
    score3 = "N/A";
    name4 = "N/A";
    score4 = "N/A";
    name5 = "N/A";
    score5 = "N/A";
    name6 = "N/A";
    score6 = "N/A";
    name7 = "N/A";
    score7 = "N/A";
    name8 = "N/A";
    score8 = "N/A";
    name9 = "N/A";
    score9 = "N/A";
    name10 = "N/A";
    score10 = "N/A";
    return;
  }
  f >> name3;
  if (!f.good())
  {
    name3 = "N/A";
    score3 = "N/A";
    name4 = "N/A";
    score4 = "N/A";
    name5 = "N/A";
    score5 = "N/A";
    name6 = "N/A";
    score6 = "N/A";
    name7 = "N/A";
    score7 = "N/A";
    name8 = "N/A";
    score8 = "N/A";
    name9 = "N/A";
    score9 = "N/A";
    name10 = "N/A";
    score10 = "N/A";
    return;
  }
  f >> score3;
  if (!f.good())
  {
    score3 = "N/A";
    name4 = "N/A";
    score4 = "N/A";
    name5 = "N/A";
    score5 = "N/A";
    name6 = "N/A";
    score6 = "N/A";
    name7 = "N/A";
    score7 = "N/A";
    name8 = "N/A";
    score8 = "N/A";
    name9 = "N/A";
    score9 = "N/A";
    name10 = "N/A";
    score10 = "N/A";
    return;
  }
  f >> name4;
  if (!f.good())
  {
    name4 = "N/A";
    score4 = "N/A";
    name5 = "N/A";
    score5 = "N/A";
    name6 = "N/A";
    score6 = "N/A";
    name7 = "N/A";
    score7 = "N/A";
    name8 = "N/A";
    score8 = "N/A";
    name9 = "N/A";
    score9 = "N/A";
    name10 = "N/A";
    score10 = "N/A";
    return;
  }
  f >> score4;
  if (!f.good())
  {
    score4 = "N/A";
    name5 = "N/A";
    score5 = "N/A";
    name6 = "N/A";
    score6 = "N/A";
    name7 = "N/A";
    score7 = "N/A";
    name8 = "N/A";
    score8 = "N/A";
    name9 = "N/A";
    score9 = "N/A";
    name10 = "N/A";
    score10 = "N/A";
    return;
  }
  f >> name5;
  if (!f.good())
  {
    name5 = "N/A";
    score5 = "N/A";
    name6 = "N/A";
    score6 = "N/A";
    name7 = "N/A";
    score7 = "N/A";
    name8 = "N/A";
    score8 = "N/A";
    name9 = "N/A";
    score9 = "N/A";
    name10 = "N/A";
    score10 = "N/A";
    return;
  }
  f >> score5;
  if (!f.good())
  {
    score5 = "N/A";
    name6 = "N/A";
    score6 = "N/A";
    name7 = "N/A";
    score7 = "N/A";
    name8 = "N/A";
    score8 = "N/A";
    name9 = "N/A";
    score9 = "N/A";
    name10 = "N/A";
    score10 = "N/A";
    return;
  }
  f >> name6;
  if (!f.good())
  {
    name6 = "N/A";
    score6 = "N/A";
    name7 = "N/A";
    score7 = "N/A";
    name8 = "N/A";
    score8 = "N/A";
    name9 = "N/A";
    score9 = "N/A";
    name10 = "N/A";
    score10 = "N/A";
    return;
  }
  f >> score6;
  if (!f.good())
  {
    score6 = "N/A";
    name7 = "N/A";
    score7 = "N/A";
    name8 = "N/A";
    score8 = "N/A";
    name9 = "N/A";
    score9 = "N/A";
    name10 = "N/A";
    score10 = "N/A";
    return;
  }
  f >> name7;
  if (!f.good())
  {
    name7 = "N/A";
    score7 = "N/A";
    name8 = "N/A";
    score8 = "N/A";
    name9 = "N/A";
    score9 = "N/A";
    name10 = "N/A";
    score10 = "N/A";
    return;
  }
  f >> score7;
  if (!f.good())
  {
    score7 = "N/A";
    name8 = "N/A";
    score8 = "N/A";
    name9 = "N/A";
    score9 = "N/A";
    name10 = "N/A";
    score10 = "N/A";
    return;
  }
  f >> name8;
  if (!f.good())
  {
    name8 = "N/A";
    score8 = "N/A";
    name9 = "N/A";
    score9 = "N/A";
    name10 = "N/A";
    score10 = "N/A";
    return;
  }
  f >> score8;
  if (!f.good())
  {
    score8 = "N/A";
    name9 = "N/A";
    score9 = "N/A";
    name10 = "N/A";
    score10 = "N/A";
    return;
  }
  f >> name9;
  if (!f.good())
  {
    name9 = "N/A";
    score9 = "N/A";
    name10 = "N/A";
    score10 = "N/A";
    return;
  }
  f >> score9;
  if (!f.good())
  {
    score9 = "N/A";
    name10 = "N/A";
    score10 = "N/A";
    return;
  }
  f >> name10;
  if (!f.good())
  {
    name10 = "N/A";
    score10 = "N/A";
    return;
  }
  f >> score10;
  if (!f.good())
  {
    score10 = "N/A";
    return;
  }
}
void Background::update_score_section()
{
  if (first_score != nullptr) delete first_score;
  first_score = new Image(small.render(score1.c_str(), WHITE));
  if (first_name != nullptr) delete first_name;
  first_name = new Image(small.render(name1.c_str(), WHITE));
  if (second_score != nullptr) delete second_score;
  second_score = new Image(small.render(score2.c_str(), WHITE));
  if (second_name != nullptr) delete second_name;
  second_name = new Image(small.render(name2.c_str(), WHITE));
  if (third_score != nullptr) delete third_score;
  third_score = new Image(small.render(score3.c_str(), WHITE));
  if (third_name != nullptr) delete third_name;
  third_name = new Image(small.render(name3.c_str(), WHITE));
  if (fourth_score != nullptr) delete fourth_score;
  fourth_score = new Image(small.render(score4.c_str(), WHITE));
  if (fourth_name != nullptr) delete fourth_name;
  fourth_name = new Image(small.render(name4.c_str(), WHITE));
  if (fifth_score != nullptr) delete fifth_score;
  fifth_score = new Image(small.render(score5.c_str(), WHITE));
  if (fifth_name != nullptr) delete fifth_name;
  fifth_name = new Image(small.render(name5.c_str(), WHITE));
  if (sixth_score != nullptr) delete sixth_score;
  sixth_score = new Image(small.render(score6.c_str(), WHITE));
  if (sixth_name != nullptr) delete sixth_name;
  sixth_name = new Image(small.render(name6.c_str(), WHITE));
  if (seventh_score != nullptr) delete seventh_score;
  seventh_score = new Image(small.render(score7.c_str(), WHITE));
  if (seventh_name != nullptr) delete seventh_name;
  seventh_name = new Image(small.render(name7.c_str(), WHITE));
  if (eighth_score != nullptr) delete eighth_score;
  eighth_score = new Image(small.render(score8.c_str(), WHITE));
  if (eighth_name != nullptr) delete eighth_name;
  eighth_name = new Image(small.render(name8.c_str(), WHITE));
  if (ninth_score != nullptr) delete ninth_score;
  ninth_score = new Image(small.render(score9.c_str(), WHITE));
  if (ninth_name != nullptr) delete ninth_name;
  ninth_name = new Image(small.render(name9.c_str(), WHITE));
  if (tenth_score != nullptr) delete tenth_score;
  tenth_score = new Image(small.render(score10.c_str(), WHITE));
  if (tenth_name != nullptr) delete tenth_name;
  tenth_name = new Image(small.render(name10.c_str(), WHITE));
  first_score->rect().x = first.rect().x + 195;
  first_score->rect().y = first.rect().y;
  first_name->rect().x = first_score->rect().x + 215;
  first_name->rect().y = first.rect().y;
  second_score->rect().x = second.rect().x + 195;
  second_score->rect().y = second.rect().y;
  second_name->rect().x = second_score->rect().x + 215;
  second_name->rect().y = second.rect().y;
  third_score->rect().x = third.rect().x + 195;
  third_score->rect().y = third.rect().y;
  third_name->rect().x = third_score->rect().x + 215;
  third_name->rect().y = third.rect().y;
  fourth_score->rect().x = fourth.rect().x + 195;
  fourth_score->rect().y = fourth.rect().y;
  fourth_name->rect().x = fourth_score->rect().x + 215;
  fourth_name->rect().y = fourth.rect().y;
  fifth_score->rect().x = fifth.rect().x + 195;
  fifth_score->rect().y = fifth.rect().y;
  fifth_name->rect().x = fifth_score->rect().x + 215;
  fifth_name->rect().y = fifth.rect().y;
  sixth_score->rect().x = sixth.rect().x + 195;
  sixth_score->rect().y = sixth.rect().y;
  sixth_name->rect().x = sixth_score->rect().x + 215;
  sixth_name->rect().y = sixth.rect().y;
  seventh_score->rect().x = seventh.rect().x + 195;
  seventh_score->rect().y = seventh.rect().y;
  seventh_name->rect().x = seventh_score->rect().x + 215;
  seventh_name->rect().y = seventh.rect().y;
  eighth_score->rect().x = eighth.rect().x + 195;
  eighth_score->rect().y = eighth.rect().y;
  eighth_name->rect().x = eighth_score->rect().x + 215;
  eighth_name->rect().y = eighth.rect().y;
  ninth_score->rect().x = ninth.rect().x + 195;
  ninth_score->rect().y = ninth.rect().y;
  ninth_name->rect().x = ninth_score->rect().x + 215;
  ninth_name->rect().y = ninth.rect().y;
  tenth_score->rect().x = tenth.rect().x + 195;
  tenth_score->rect().y = tenth.rect().y;
  tenth_name->rect().x = tenth_score->rect().x + 215;
  tenth_name->rect().y = tenth.rect().y;
}
void Background::update_ships()
{
  int x = flagship->rect().x;
  if (flag_moving)
  {
    if (x <= W / 2 - 250) flag_moving = false;
  }
  if (flagship != nullptr) delete flagship;
  flagship = new Image("images/GalaxianFlagship.gif");
  flagship->rect().x = (flag_moving ? x - 2 : W / 2 - 250);
  flagship->rect().y = H / 2 + 25;
  x = red_escort->rect().x;
  if (red_moving)
  {
    if (x <= W / 2 - 250) red_moving = false;
  }
  if (red_escort != nullptr) delete red_escort;
  red_escort = new Image("images/GalaxianRedAlien.gif");
  red_escort->rect().x = (red_moving ? x - 2 : W / 2 - 250);
  red_escort->rect().y = H / 2 + 100;
  x = purple->rect().x;
  if (purple_moving)
  {
    if (x <= W / 2 - 250) purple_moving = false;
  }
  if (purple != nullptr) delete purple;
  purple = new Image("images/GalaxianPurpleAlien.gif");
  purple->rect().x = (purple_moving ? x - 2 : W / 2 - 250);
  purple->rect().y = H / 2 + 175;
  x = blue->rect().x;
  if (blue_moving)
  {
    if (x <= W / 2 - 250) blue_moving = false;
  }
  if (blue != nullptr) delete blue;
  blue = new Image("images/GalaxianAquaAlien.gif");
  blue->rect().x = (blue_moving ? x - 2 : W / 2 - 250);
  blue->rect().y = H / 2 + 250;
}
void Background::draw_ships()
{
  surface->put_image(*flagship, flagship->rect());
  surface->put_image(*red_escort, red_escort->rect());
  surface->put_image(*purple, purple->rect());
  surface->put_image(*blue, blue->rect());
}
void Background::reset_intructions()
{
  flag_moving = true;
  red_moving = true;
  purple_moving = true;
  blue_moving = true;
  if (flagship != nullptr) delete flagship;
  if (red_escort != nullptr) delete red_escort;
  if (purple != nullptr) delete purple;
  if (blue != nullptr) delete blue;
  flagship = new Image("images/GalaxianFlagship.gif");
  flagship->rect().x = W / 2 + 650;
  flagship->rect().y = H / 2 + 25;
  red_escort = new Image("images/GalaxianRedAlien.gif");
  red_escort->rect().x = W / 2 + 550;
  red_escort->rect().y = H / 2 + 100;
  purple = new Image("images/GalaxianPurpleAlien.gif");
  purple->rect().x = W / 2 + 450;
  purple->rect().y = H / 2 + 175;
  blue = new Image("images/GalaxianAquaAlien.gif");
  blue->rect().x = W / 2 + 350;
  blue->rect().y = H / 2 + 250;
}
