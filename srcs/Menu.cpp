#include <fstream>
#include <iostream>
#include "Menu.hpp"

Menu::Menu()
{
  std::ifstream file("./.save/game.save", std::ios::in);

  this->_save = false;
  if (file)
    {
      char test = file.peek();
      if (test != EOF)
	this->_save = true;
      file.close();
    }
  this->_sreenMenu = new LoadTexture(90, 1, 1, 1);
  this->_moto = new LoadTexture(90, 1, 1, 1);
}

Menu::~Menu()
{
  delete this->_sreenMenu;
  delete this->_moto;
}

bool	Menu::initialize()
{
  std::string   pathImg("./imgs/menu_base.tga");

  this->_sreenMenu->translate(glm::vec3(0, 0, 0));
  if (!this->_sreenMenu->initialize(25, 42, pathImg))
    return (false);
  pathImg = "./imgs/motoLoad.tga";
  this->_moto->translate(glm::vec3(10, 22, 0));
  if (!this->_moto->initialize(3, 4, pathImg))
    return (false);
  this->_text.initialize();
  this->_title.initialize();
  glm::vec4 color(0, 0.5, 1, 1);
  this->_text.putStr("play  resume  option  quit", color, 2.0f);
  glm::vec4 colorT(1, 0.5, 0, 1);
  this->_title.putStr("TRONBERMAN", colorT, 4.0f);
  return (true);
}


int     Menu::updateMouse(gdl::Input &input)
{
  if (input.getInput(SDL_BUTTON_LEFT, true))
    {
      if (input.getMousePosition().y >= 425 && input.getMousePosition().y <= 455 &&
	  input.getMousePosition().x >= 253 && input.getMousePosition().x <= 373)
	return (1);
      else if (input.getMousePosition().y >= 425 && input.getMousePosition().y <= 455 &&
	       input.getMousePosition().x >= 440 && input.getMousePosition().x <= 620  && this->_save)
	return (2);
      else if (input.getMousePosition().y >= 425 && input.getMousePosition().y <= 455 &&
	       input.getMousePosition().x >= 690 && input.getMousePosition().x <= 875)
	return (3);
      else if (input.getMousePosition().y >= 425 && input.getMousePosition().y <= 455 &&
	       input.getMousePosition().x >= 943 && input.getMousePosition().x <= 1064)
	return (-1);
    }
  return (0);
}

int	Menu::update(__attribute__((unused))gdl::Clock const &clock,
		     gdl::Input &input)
{
  int	value = Menu::updateMouse(input);

  std::ifstream file("./.save/game.save", std::ios::in);

  this->_save = false;
  if (file)
    {
      char test = file.peek();
      if (test != EOF)
	this->_save = true;
      file.close();
    }

  if (value != 0)
    return (value);
  if (input.getKey(SDLK_RETURN, true))
    {
      if (this->_moto->getPosition().y == -23)
	return (-1);
      else if (this->_moto->getPosition().y == 22)
	return (1);
      else if (this->_moto->getPosition().y == 7 && this->_save)
	return (2);
      else if (this->_moto->getPosition().y == -8)
	return (3);
    }
  if (input.getKey(SDLK_LEFT, true))
    {
      if (this->_moto->getPosition().y < 19)
	this->_moto->translate(glm::vec3(0, 15, 0));
    }
  else if (input.getKey(SDLK_RIGHT, true))
    if (this->_moto->getPosition().y > -20)
      this->_moto->translate(glm::vec3(0, -15, 0));
  return (0);
}

void	Menu::draw(gdl::AShader &shader, gdl::Clock const &clock, gdl::SdlContext &window)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  shader.bind();
  this->_sreenMenu->draw(shader, clock);
  this->_moto->draw(shader, clock);
  this->_text.draw(shader, -25, -4);
  this->_title.draw(shader, -15, 13);
  window.flush();
}
