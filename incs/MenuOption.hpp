#ifndef __MENUOPTION_HPP__
# define __MENUOPTION_HPP__

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
# include "Sound.hpp"

extern Sound sound;

class MenuOption
{
public:
  MenuOption();
  ~MenuOption();

  virtual bool	initialize();
  virtual int	update(gdl::Clock const &, gdl::Input &);
  virtual void	draw(gdl::AShader &, gdl::Clock const &, gdl::SdlContext &);
  int		getSize() const { return _sizeValue; };
  bool		getSound() const { return _soundValue; };
  int		getBots() const { return _botsValue; };
  void		drawScore(gdl::AShader &, gdl::SdlContext &, gdl::Clock &, gdl::Input &);

private:
  void			changeItem(int, int);
  int			updateMouse(gdl::Input &);

private:
  LoadTexture			*_backgroud;
  LoadTexture			*_moto;
  int				_sizeValue;
  int				_botsValue;
  bool				_soundValue;
  Text				_dificulty;
  Text				_bots;
  Text				_sizeMap;
  Text				_sound;
  Text				_credit;
  Text				_ret;
  Text				_title;
  glm::vec4			_colorM;
  std::map<int, std::string>	_level;
  int				_levelValue;
};

#endif
