#ifndef __MAP_HPP__
# define __MAP_HPP__

# include <fstream>
# include <iostream>
# include <sstream>
# include <algorithm>

# include "AObject.hpp"
# include "Cube.hpp"
# include "LoadTexture.hpp"
# include "IPerso.hpp"
# include "Bomb.hpp"
# include "Bonus.hpp"

class Map
{
public:
  Map();
  ~Map();

  bool		loadingMap(int, std::string way = "./.map/map");
  char		**getMap() const { return (this->_map); }
  char		getMap(int x, int y) const {
    if (x > 0 && x < this->_height)
      if (y > 0 && y < this->_width)
	return (this->_map[x][y]);
    return (1);
  }
  void		setMap(int const x, int const y, char const c) {
    if (x > 0 && x < this->_height)
      if (y > 0 && y < this->_width)
	this->_map[x][y] = c;
  }
  int		getWidth() const { return (this->_width); }
  void		setWidth(int const value) { this->_width = value; this->_height = value; }
  int		getHeight() const { return (this->_height); }
  void		draw(gdl::AShader &, gdl::Clock const &, int, int);
  bool		update(gdl::Clock const &, gdl::Input &);
  void		checkMap(gdl::Clock const &, IPerso * perso = NULL);
  void		freeMap();
  bool		initializeMap();
  void		createStdMap();

  void		stdRandomMap(float const density, int const pm2, int const seed = 42);
  glm::vec3*		spawnPlayer(unsigned int const nb);
  void		advancedRandomMap(int const density, int const seed = 42);

private:
  void		chechCase(int);
  int		_addDensityProb(int const density, int const x, int const y);
  void		loadMap(int);
  bool		classic(int, std::string);
  bool		resume(std::string);
  void		getHandW(std::string);
  void		putBonus(int, int, int);
  void    clear_spawn(int const x, int const y);

private:
  char				**_map;
  int				_width;
  int				_height;
  LoadTexture			*_mapBack;
  std::vector<AObject *>	_map3d;
  gdl::Texture			_texture;
  gdl::Texture			_cubeTexture;
  gdl::Model			_bomb;
  gdl::Texture			_wallTexture;
  gdl::Texture			_exploTexture;
  gdl::Texture			_moreSpeed;
  gdl::Texture			_moreLife;
  gdl::Texture			_moreBomb;
  gdl::Texture			_moreRange;
  gdl::Texture			_lessBomb;
  gdl::Texture			_lessSpeed;
  gdl::Texture			_lessRange;
};

#endif
