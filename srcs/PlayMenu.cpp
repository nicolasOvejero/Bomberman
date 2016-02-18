#include "PlayMenu.hpp"

PlayMenu::PlayMenu()
{
  this->_sreenPMenu = new LoadTexture(90, 1, 1, 1);
  this->_moto = new LoadTexture(90, 1, 1, 1);
}

PlayMenu::~PlayMenu()
{
  delete this->_sreenPMenu;
  delete this->_moto;
}

bool	PlayMenu::initialize()
{
  std::string   pathImg("./imgs/menu_base.tga");

  this->_sreenPMenu->translate(glm::vec3(0, 0, 0));
  if (!this->_sreenPMenu->initialize(25, 42, pathImg))
    return (false);
  pathImg = "./imgs/motoLoad.tga";
  this->_moto->translate(glm::vec3(10, 17, 0));
  if (!this->_moto->initialize(3, 4, pathImg))
    return (false);
  this->_text.initialize();
  glm::vec4 color(0, 0.5, 1, 1);
  this->_text.putStr("map 1  map 2  random map", color, 2.0f);
  this->_ret.initialize();
  glm::vec4 colorR(1, 0, 0, 1);
  this->_ret.putStr("<-", colorR, 1.5f);
  this->_title.initialize();
  glm::vec4 colorT(1, 0.5, 0, 1);
  this->_title.putStr("TRONBERMAN", colorT, 4.0f);
  return (true);
}

int	PlayMenu::updateMouse(gdl::Input &input)
{
  if (input.getInput(SDL_BUTTON_LEFT, true))
    {
      if (input.getMousePosition().y >= 21 && input.getMousePosition().y <= 36 &&
	  input.getMousePosition().x >= 86 && input.getMousePosition().x <= 116)
	return (-1);
      if (input.getMousePosition().y >= 426 && input.getMousePosition().y <= 459 &&
	  input.getMousePosition().x >= 317 && input.getMousePosition().x <= 462)
	{
	  this->_stat = 0;
	  return (4);
	}
    }
  return (0);
}

int	PlayMenu::update(__attribute__((unused))gdl::Clock const &clock,
			 gdl::Input &input)
{
  int	value = this->updateMouse(input);

  if (value != 0)
    return (value);
  if (input.getKey(SDLK_RETURN, true))
    {
      if (this->_moto->getPosition().y == 35)
	{
	  this->_stat = -1;
	  return (-1);
	}
      else if (this->_moto->getPosition().y == 17)
	this->_stat = 0;
      else if (this->_moto->getPosition().y == 0)
	this->_stat = 1;
      else if (this->_moto->getPosition().y == -17)
	this->_stat = 2;
      return (4);
    }
  if (input.getKey(SDLK_LEFT, true))
    {
      if (this->_moto->getPosition().y == 17)
	this->_moto->translate(glm::vec3(-27, 18, 0));
      else if (this->_moto->getPosition().y < 26)
	this->_moto->translate(glm::vec3(0, 17, 0));
    }
  else if (input.getKey(SDLK_RIGHT, true))
    {
      if (this->_moto->getPosition().y == 35)
	this->_moto->translate(glm::vec3(27, -18, 0));
      else if (this->_moto->getPosition().y > -17)
	this->_moto->translate(glm::vec3(0, -17, 0));
    }
  return (false);
}

void	PlayMenu::draw(gdl::AShader &shader, gdl::Clock const &clock, gdl::SdlContext &window)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  shader.bind();
  this->_sreenPMenu->draw(shader, clock);
  this->_moto->draw(shader, clock);
  this->_text.draw(shader, -25, -4);
  this->_ret.draw(shader, 35, 22);
  this->_title.draw(shader, -15, 13);
  window.flush();
}
