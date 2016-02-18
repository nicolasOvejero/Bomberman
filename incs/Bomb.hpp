#ifndef __BOMB_HPP__
# define __BOMB_HPP__

# include <iostream>
# include <chrono>
# include "Map.hpp"

using namespace std::chrono;

class Bomb : public AObject
{
public:
  Bomb(gdl::Model &, IPerso *);
  Bomb(int, int, gdl::Model &, IPerso *);
  ~Bomb() {}

  virtual bool		initialize();
  virtual void		update(gdl::Clock const &, gdl::Input &, Map *);
  virtual void		draw(gdl::AShader &, gdl::Clock const &);

private:
  gdl::Model			&_model;
  glm::mat4			_transformation;
  steady_clock::time_point	_timeSart;
  int				_x;
  int				_y;
  bool				_boom;
  bool				_left;
  bool				_right;
  bool				_up;
  bool				_down;
  IPerso			*_who;
};

#endif
