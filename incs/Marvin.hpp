#ifndef __MARVIN_HPP__
# define __MARVIN_HPP__

# include "AObject.hpp"
# include "IPerso.hpp"
# include "Camera.hpp"
# include "Bomb.hpp"

using namespace std::chrono;

class Marvin : public IPerso
{
public:
  Marvin(int id = 1);
  Marvin(glm::vec3, int id = 1);
  virtual ~Marvin();
  virtual bool		initialize();
  virtual bool		update(gdl::Clock const &, gdl::Input &, Camera &, Map &);
  virtual bool		update(gdl::Clock const &, gdl::Input &, Camera &, int);
  virtual void		draw(gdl::AShader &, gdl::Clock const &);

  virtual int		getId() const { return _id; }
  virtual void		setId(int const id) { _id = id; }

  virtual void		setPos(glm::vec3 const pos) {
    (this->_transformation[3]).x = pos.x;
    (this->_transformation[3]).y = pos.y;
    (this->_transformation[3]).z = pos.z;
  }
  virtual float		getPosX() const { return ((this->_transformation[3]).x); }
  virtual float		getPosY() const { return ((this->_transformation[3]).y); }
  virtual float		getPosZ() const { return ((this->_transformation[3]).z); }

  virtual void		modifLife(int const x);
  virtual int		getLife() const { return (this->_Life); }
  virtual void		modifSpeed(int const x);
  virtual int		getSpeed() const { return (this->_Speed); }
  virtual void		modifBomb(int const x);
  virtual int		getBomb() const { return (this->_Bomb); }
  virtual void		modifRange(int const x);
  virtual int		getRange() const { return (this->_Range); }
  virtual void		setScore(int const value) { this->_score += value; }
  virtual int		getScore() const { return this->_score; }

  bool			ckeckBonus(gdl::Clock const &, Map &);

  glm::vec3		getPosPlayer() const { return _pos; }
  glm::vec3		getDirPlayer() const { return _dir; }

private:
  float			getAngleRota(eDirection);
  bool			checkLeft(gdl::Input &, Camera &, Map &);
  bool			checkRight(gdl::Input &, Camera &, Map &);
  bool			checkUp(gdl::Input &, Camera &, Map &);
  bool			checkDown(gdl::Input &, Camera &, Map &);
  void			putBomb(Map &, gdl::Clock const &);
  bool			checkLife(Map &, Camera &);

private:
  gdl::Model			_model;
  eDirection			_currentDir;
  glm::mat4			_transformation;
  int				_Life;
  int				_Bomb;
  int				_Range;
  float				_Speed;
  int				_id;
  int				_score;
  Camera			_camera;
  int				_bomb;
  int				_left;
  int				_right;
  int				_up;
  int				_down;
  steady_clock::time_point	_timeSart;
  glm::vec3			_pos;
  glm::vec3			_dir;
};

#endif
