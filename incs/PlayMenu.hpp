#ifndef __PLAYMENU_HPP__
# define __PLAYMENU_HPP__

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

class PlayMenu
{
public:
  PlayMenu();
  ~PlayMenu();

  virtual bool	initialize();
  virtual int	update(gdl::Clock const &, gdl::Input &);
  virtual void	draw(gdl::AShader &, gdl::Clock const &, gdl::SdlContext &);
  int		getStat() const { return _stat; }

private:
  int		updateMouse(gdl::Input &);

private:
  LoadTexture		*_sreenPMenu;
  LoadTexture		*_moto;
  // bool			_save;
  int			_stat;
  Text			_text;
  Text			_ret;
  Text			_title;
};

#endif
