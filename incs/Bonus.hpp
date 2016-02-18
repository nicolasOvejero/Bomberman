#ifndef __BONUS_HPP__
# define __BONUS_HPP__

# include <iostream>
# include "AObject.hpp"

class Bonus : public AObject
{
public:
  Bonus(gdl::Texture &, int, int);
  virtual ~Bonus() { }

  virtual bool		initialize(char const);
  virtual void		draw(gdl::AShader &, gdl::Clock const &);

private:
  gdl::Texture		&_texture;
  gdl::Geometry		_geometry;
  glm::mat4		_transformation;
  float			_speed;
};

#endif
