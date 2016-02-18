#include <unistd.h>
#include <Geometry.hh>
#include "Intro.hpp"

static	int i = 0;

Intro::Intro()
{
  this->_backgroud = new LoadTexture(90, 0.1, 0.1, 0.1);
}

Intro::~Intro()
{
  delete this->_backgroud;
}

bool		Intro::initialize()
{
  std::string	pathImg("./imgs/intro.tga");

  this->_backgroud->translate(glm::vec3(0, 0, 0));
  if (!this->_backgroud->initialize(25, 42, pathImg))
    return (false);
  this->_title.initialize();
  this->_pPlay.initialize();
  glm::vec4 colorT(0, 0.5, 1, 1);
  this->_pPlay.putStr("Press P to play", colorT, 3);
  sound.playMusic(0, 1);
  return (true);
}

bool		Intro::update(__attribute__((unused))gdl::Clock const &clock,
			      gdl::Input &input)
{
  if (input.getKey(SDLK_p))
    return (false);
  return (true);
}

void		Intro::draw(gdl::AShader &shader,
			    __attribute__((unused))gdl::Clock const &clock,
			    gdl::SdlContext &window)
{
  std::string	name("Tronberman");

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  shader.bind();
  this->_backgroud->draw(shader, clock);
  if (static_cast<LoadTexture *>(this->_backgroud)->stat == true && i < 10)
    {
      glm::vec4 colorT(1, 0.5, 0, 1);
      this->_title.putChar(name.at(i), colorT);
      i++;
      usleep(180000);
    }
  if (i != 0)
    this->_title.draw(shader, -15, 13);
  if (i >= 10)
    this->_pPlay.draw(shader, -20, -9);
  window.flush();
}
