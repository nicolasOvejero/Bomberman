#ifndef __GAME_HPP__
# define __GAME_HPP__

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
# include <SDL_mixer.h>
# include <X11/X.h>
# include <X11/Xlib.h>
# include <GL/gl.h>
# include <GL/glx.h>
# include <GL/glu.h>

# include <cstdlib>
# include <unistd.h>
# include <iostream>

# include "AObject.hpp"
# include "Marvin.hpp"
# include "Intro.hpp"
# include "LoadTexture.hpp"
# include "Menu.hpp"
# include "PlayMenu.hpp"
# include "Cube.hpp"
# include "Text.hpp"
# include "MenuOption.hpp"
# include "Map.hpp"
# include "Sound.hpp"
# include "Camera.hpp"
# include "IPerso.hpp"
# include "Thread.hpp"
# include "SubMenu.hpp"
# include "IA.hpp"
# include "Save.hpp"

# define WINX 1280
# define WINY 720

extern Sound sound;

class MyGame : public gdl::Game
{
public:
  MyGame();
  virtual ~MyGame();

  virtual bool		initialize();
  virtual bool		update();
  virtual void		draw();
  void			drawAlll();
  void			drawAlll1();
  void			updateIAa(int);

private:
  void			intro();
  int			menu();
  int			playMenu();
  bool			loadPlayer();
  void			drawLoad(LoadTexture *, int size = 10);
  bool			startWin();
  int			option();
  bool			play(std::string way = "./.map/map");
  int			Submenu();
  bool			positionCamera(std::string);
  void			setPerso(std::string, int);
  void			lastMemories();
  void			setIa(std::string, int);
  bool			checkTouch();
  void			quitGame();
  void			drawCredit();

private:
  gdl::SdlContext	_window;
  gdl::Input		_input;
  gdl::Clock		_clock;
  glm::mat4		_projection;
  glm::mat4		_transformation;

  Intro			_intro;
  Menu			_menu;
  PlayMenu		_playMenu;
  MenuOption		_optionMenu;
  Map			_map;
  Text			_players;
  Camera		_camera;
  SubMenu		_subMenu;

  unsigned int		_nbPlayer;
  int			_subret;
  int			_nbMusic;
  int			_nbIA;
  int			_nbPerso;
  int			_pos;
  bool			_musicSate;

  std::vector<IPerso *>	_perso;
  std::vector<IA *>	_ia;
  Save			_save;

  Thread		*_th;
  Thread		**_tab;
  Thread		*_th1;
};

struct greater
{
  template<class T>
  bool operator()(T const &a, T const &b) const { return a > b; }
};

void    *drawAll(void *);
void    *drawAll1(void *);
void    *updateIA(MyGame *, int);

#endif
