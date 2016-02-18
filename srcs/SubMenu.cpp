#include "SubMenu.hpp"

SubMenu::SubMenu()
{
  this->_moto = new LoadTexture(90, 1, 1, 1);
  this->_sreenMenu = new LoadTexture(90, 1, 1, 1);
}

SubMenu::~SubMenu()
{
  delete this->_moto;
  delete this->_sreenMenu;
}

bool	SubMenu::initialize()
{
  std::string   pathImg("./imgs/subMenu.tga");

  this->_sreenMenu->translate(glm::vec3(0, 0, 0));
  if (!this->_sreenMenu->initialize(25, 42, pathImg))
    return (false);
  pathImg = "./imgs/motoLoad.tga";
  this->_moto->translate(glm::vec3(-10, 15, 0));
  if (!this->_moto->initialize(3, 4, pathImg))
    return (false);
  this->_resume.initialize();
  this->_save.initialize();
  this->_quit.initialize();
  glm::vec4 color(1, 0, 0, 1);
  this->_resume.putStr("Resume", color, 2.0f);
  this->_save.putStr("Save", color, 2.0f);
  this->_quit.putStr("Quit", color, 2.0f);
  return (true);
}

int	SubMenu::update(__attribute__((unused))gdl::Clock const &clock,
			gdl::Input &input)
{
  if (input.getKey(SDLK_ESCAPE, true))
    return (0);
  else if (input.getKey(SDLK_RETURN, true))
    {
      if (this->_moto->getPosition().x == -10)
	return (1);
      else if (this->_moto->getPosition().x == -5)
	return (2);
      else if (this->_moto->getPosition().x == 0)
	return (0);
    }
  if (input.getKey(SDLK_DOWN, true) && this->_moto->getPosition().x < -1)
    this->_moto->translate(glm::vec3(5, 0, 0));
  else if (input.getKey(SDLK_UP, true) && this->_moto->getPosition().x > -9)
    this->_moto->translate(glm::vec3(-5, 0, 0));
  return (-1);
}

void	SubMenu::draw(gdl::AShader &shader, gdl::Clock const &clock, gdl::SdlContext &window)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  shader.bind();
  this->_sreenMenu->draw(shader, clock);
  this->_moto->draw(shader, clock);
  this->_resume.draw(shader, 0, 10);
  this->_save.draw(shader, 0, 5);
  this->_quit.draw(shader, 0, 0);
  window.flush();
}
