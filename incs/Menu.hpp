#ifndef __MENU_HPP__
# define __MENU_HPP__

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

# include "AObject.hpp"
# include "LoadTexture.hpp"
# include "Text.hpp"

class Menu
{
public:
  Menu();
  ~Menu();

  virtual bool	initialize();
  virtual int	update(gdl::Clock const &, gdl::Input &);
  virtual void	draw(gdl::AShader &, gdl::Clock const &, gdl::SdlContext &);

private:
  int		updateMouse(gdl::Input &);

private:
  LoadTexture		*_moto;
  LoadTexture		*_sreenMenu;
  bool			_save;
  Text			_text;
  Text			_title;
};

#endif
