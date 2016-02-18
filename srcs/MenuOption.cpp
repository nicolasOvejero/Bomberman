#include <unistd.h>
#include <fstream>
#include <iostream>
#include <Geometry.hh>
#include "MenuOption.hpp"

MenuOption::MenuOption()
{
  this->_backgroud = new LoadTexture(90, 1, 1, 1);
  this->_moto = new LoadTexture(90, 1, 1, 1);
  this->_sizeValue = 20;
  this->_botsValue = 0;
  this->_soundValue = true;
  this->_colorM = glm::vec4(1, 1, 0, 1);
  this->_level[0] = "easy";
  this->_level[1] = "medium";
  this->_level[2] = "hard";
  this->_levelValue = 0;
}

MenuOption::~MenuOption()
{
  delete this->_backgroud;
  delete this->_moto;
}

bool		MenuOption::initialize()
{
  std::string	pathImg("./imgs/menu_base.tga");
  glm::vec4	colorT(1, 0.5, 0, 1);
  glm::vec4	colorR(1, 0, 0, 1);

  this->_backgroud->translate(glm::vec3(0, 0, 0));
  if (!this->_backgroud->initialize(25, 42, pathImg))
    return (false);
  pathImg = "./imgs/motoLoad.tga";
  this->_moto->translate(glm::vec3(-5, 25, 0));
  if (!this->_moto->initialize(3, 4, pathImg))
    return (false);
  this->_title.initialize();
  this->_title.putStr("Option", colorT, 3.0f);
  this->_ret.initialize();
  this->_ret.putStr("<-", colorR, 1.5f);
  this->_dificulty.initialize();
  this->_dificulty.putStr("Best score", this->_colorM, 2.0f);
  this->_bots.initialize();
  this->_bots.putStr("Nb Bots : < 0 >", this->_colorM, 2.0f);
  this->_sizeMap.initialize();
  this->_sizeMap.putStr("Size Map : < 20 >", this->_colorM, 2.0f);
  this->_sound.initialize();
  this->_sound.putStr("Sound : on", this->_colorM, 2.0f);
  this->_credit.initialize();
  this->_credit.putStr("Credit", this->_colorM, 2.0f);
  return (true);
}

void		MenuOption::changeItem(int posX, int dir)
{
  std::string	s;

  switch (posX)
    {
    case 0:
      if (dir == 1)
	this->_botsValue += ((this->_botsValue + 1) >= 10 ? 0 : 1);
      else
	this->_botsValue -= ((this->_botsValue - 1) < 0 ? 0 : 1);
      s = "Nb Bots : < " + std::to_string(this->_botsValue) + " >";
      this->_bots.changeStr(s, 2.0f, this->_colorM);
      break;
    case 5:
      if (dir == 1)
	this->_sizeValue += ((this->_sizeValue + 10) >= 100 ? 0 : 10);
      else
	this->_sizeValue -= ((this->_sizeValue - 10) < 20 ? 0 : 10);
      s = "Size Map : < " + std::to_string(this->_sizeValue) + " >";
      this->_sizeMap.changeStr(s, 2.0f, this->_colorM);
      break;
    case 10:
      this->_soundValue = ((this->_soundValue) ? false : true);
      if (this->_soundValue)
	{
	  if (!sound.getStat())
	    sound.playMusic(2, -1);
	  s = "Sound : on";
	}
      else
	{
	  sound.stopMusic();
	  s = "Sound : off";
	}
      this->_sound.changeStr(s, 2.0f, this->_colorM);
      break;
    }
}

int		MenuOption::updateMouse(gdl::Input &input)
{
  if (input.getInput(SDL_BUTTON_LEFT, true))
    {
      if (input.getMousePosition().y >= 21 && input.getMousePosition().y <= 36 &&
	  input.getMousePosition().x >= 86 && input.getMousePosition().x <= 116)
	return (-1);
      if (input.getMousePosition().y >= 366 && input.getMousePosition().y <= 393)
	{
	  if (input.getMousePosition().x >= 710 && input.getMousePosition().x <= 728)
	    this->changeItem(0, 2);
	  else if (input.getMousePosition().x >= 835 && input.getMousePosition().x <= 854)
	    this->changeItem(0, 1);
	}
      if (input.getMousePosition().y >= 440 && input.getMousePosition().y <= 465)
	{
	  if (input.getMousePosition().x >= 705 && input.getMousePosition().x <= 730)
	    this->changeItem(5, 2);
	  else if (input.getMousePosition().x >= 867 && input.getMousePosition().x <= 886)
	    this->changeItem(5, 1);
	}
      return (1);
    }
  return (0);
}

int		MenuOption::update(gdl::Clock const &clock, gdl::Input &input)
{
  int		value;

  if (input.getKey(SDLK_RETURN, true))
    {
      if (this->_moto->getPosition().x == -17)
	return (-1);
      else if (this->_moto->getPosition().x == -5)
	return (5);
      else if (this->_moto->getPosition().x == 15)
	return (6);
    }
  if ((value = this->updateMouse(input)) == -1)
    return (-1);
  else if (value == 0)
    {
      if (input.getKey(SDLK_RIGHT, true))
	this->changeItem(this->_moto->getPosition().x, 1);
      else if (input.getKey(SDLK_LEFT, true))
	this->changeItem(this->_moto->getPosition().x, 2);

      if (input.getKey(SDLK_UP, true))
	{
	  if (this->_moto->getPosition().x == -5)
	    this->_moto->translate(glm::vec3(-12, 10, 0));
	  else if (this->_moto->getPosition().x > -5)
	    this->_moto->translate(glm::vec3(-5, 0, 0));
	}
      else if (input.getKey(SDLK_DOWN, true))
	{
	  if (this->_moto->getPosition().x == -17)
	    this->_moto->translate(glm::vec3(12, -10, 0));
	  else if (this->_moto->getPosition().x < 15)
	    this->_moto->translate(glm::vec3(5, 0, 0));
	}
    }
  return (1);
}

void		MenuOption::drawScore(gdl::AShader &shader, gdl::SdlContext &window,
				      gdl::Clock &clock, gdl::Input &input)
{
  Text		first;
  Text		second;
  Text		third;
  Text		fourth;
  Text		fith;
  Text		title;
  LoadTexture	*backgroud = new LoadTexture(90, 1, 1, 1);
  std::string	pathImg("./imgs/grid.tga");
  std::string	s;
  std::ifstream file("./.score/game.score", std::ios::in);

  backgroud->translate(glm::vec3(0, 0, 0));
  backgroud->initialize(25, 42, pathImg);
  first.initialize();
  second.initialize();
  third.initialize();
  fourth.initialize();
  fith.initialize();
  title.initialize();
  title.putStr("Best Score", glm::vec4(1, 0.5, 0, 1), 3.0f);
  if (file.is_open())
    {
      std::getline(file, s);
      first.putStr(s, glm::vec4(1, 0.5, 0, 1), 3.0f);
      s.clear();
      std::getline(file, s);
      second.putStr(s, glm::vec4(1, 0.5, 0, 1), 3.0f);
      s.clear();
      std::getline(file, s);
      third.putStr(s, glm::vec4(1, 0.5, 0, 1), 3.0f);
      s.clear();
      std::getline(file, s);
      fourth.putStr(s, glm::vec4(1, 0.5, 0, 1), 3.0f);
      s.clear();
      std::getline(file, s);
      fith.putStr(s, glm::vec4(1, 0.5, 0, 1), 3.0f);
      file.close();
    }
  while (!input.getKey(SDLK_ESCAPE, true))
    {
      window.updateInputs(input);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      shader.bind();
      backgroud->draw(shader, clock);
      title.draw(shader, -5, 22);
      first.draw(shader, -5, 5);
      second.draw(shader, -5, 0);
      third.draw(shader, -5, -5);
      fourth.draw(shader, -5, -10);
      fith.draw(shader, -5, -15);
      window.flush();
    }
  delete backgroud;
}

void		MenuOption::draw(gdl::AShader &shader, gdl::Clock const &clock, gdl::SdlContext &window)
{
  std::string	name("Tronberman");

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  shader.bind();
  this->_backgroud->draw(shader, clock);
  this->_moto->draw(shader, clock);
  this->_title.draw(shader, -5, 22);
  this->_ret.draw(shader, 35, 22);
  this->_dificulty.draw(shader, -5, 5);
  this->_bots.draw(shader, -12, 0);
  this->_sizeMap.draw(shader, -14, -5);
  this->_sound.draw(shader, -5, -10);
  this->_credit.draw(shader, 0, -15);
  window.flush();
}
