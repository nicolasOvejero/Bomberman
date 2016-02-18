#ifndef __SUBMENU_HPP__
# define __SUBMENU_HPP__

# include "AObject.hpp"
# include "Text.hpp"
# include "LoadTexture.hpp"

class SubMenu
{
public:
  SubMenu();
  ~SubMenu();

  virtual bool	initialize();
  virtual int	update(gdl::Clock const &, gdl::Input &);
  virtual void	draw(gdl::AShader &, gdl::Clock const &, gdl::SdlContext &);

private:
  LoadTexture		*_moto;
  LoadTexture		*_sreenMenu;
  Text			_resume;
  Text			_save;
  Text			_quit;
};

#endif
