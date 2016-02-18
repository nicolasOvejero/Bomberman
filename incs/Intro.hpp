#ifndef __INTRO_HPP__
# define __INTRO_HPP__

# include <Game.hh>
# include <Clock.hh>
# include <Input.hh>
# include <SdlContext.hh>
# include <Geometry.hh>
# include <Texture.hh>
# include <BasicShader.hh>
# include <Model.hh>
# include <OpenGL.hh>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <Model.hh>
# include <iostream>

# include "LoadTexture.hpp"
# include "Text.hpp"
# include "Sound.hpp"

extern Sound sound;

class Intro
{
public:
  Intro();
  ~Intro();

  virtual bool initialize();
  virtual bool update(gdl::Clock const &, gdl::Input &);
  virtual void draw(gdl::AShader &, gdl::Clock const &, gdl::SdlContext &);

private:
  LoadTexture	*_backgroud;
  Text		_title;
  Text		_pPlay;
};

#endif
