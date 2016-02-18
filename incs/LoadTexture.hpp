#ifndef __LOADTEXTURE_HPP__
# define __LOADTEXTURE_HPP__

# include "AObject.hpp"

class LoadTexture : public AObject
{
public:
  LoadTexture(int, float, float, float);
  ~LoadTexture() {};

  virtual bool		initialize(float ,float , std::string const);
  virtual bool		update(gdl::Clock const &, gdl::Input &) { return true; }
  virtual void		draw(gdl::AShader &, gdl::Clock const &);
  glm::vec3		getPosition() const;

  bool			stat;
private:
  gdl::Geometry		_geometry;
  gdl::Texture		_texture;
};

#endif
