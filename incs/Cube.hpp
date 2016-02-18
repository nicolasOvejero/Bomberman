#ifndef __CUBE_HPP__
# define __CUBE_HPP__

# include <iostream>
# include "AObject.hpp"

class Cube : public AObject
{
public:
  Cube(gdl::Texture &);
  virtual ~Cube() { }

  virtual bool		initialize(char const);
  virtual bool		update(__attribute__((unused))gdl::Clock const &,
			       __attribute__((unused))gdl::Input &) { return true; };
  virtual void		draw(gdl::AShader &, gdl::Clock const &);

private:
  gdl::Texture		&_texture;
  gdl::Geometry		_geometry;
  float			_speed;
};

#endif
