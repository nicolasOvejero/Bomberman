#ifndef __IPERSO_HPP__
# define __IPERSO_HPP__

# include <Clock.hh>
# include <Input.hh>

class Map;
class Camera;

enum eDirection
  {
    UP,
    LEFT,
    DOWN,
    RIGHT
  };

class IPerso : public AObject
{
public:
  virtual ~IPerso() {}

  virtual void		setId(int const) = 0;
  virtual int		getId() const = 0;
  virtual float		getPosX() const = 0;
  virtual float		getPosY() const = 0;
  virtual float		getPosZ() const = 0;
  virtual void		modifLife(int const) = 0;
  virtual int		getLife() const = 0;
  virtual void		modifSpeed(int const) = 0;
  virtual int		getSpeed() const = 0;
  virtual void		modifBomb(int const) = 0;
  virtual int		getBomb() const = 0;
  virtual void		modifRange(int const) = 0;
  virtual int		getRange() const = 0;
  virtual bool		update(gdl::Clock const &, gdl::Input &, Camera &, Map &) = 0;
  virtual bool		update(gdl::Clock const &, gdl::Input &, Camera &, int) = 0;
  virtual void		setPos(glm::vec3 const) = 0;
  virtual void		setScore(int const) = 0;
  virtual int		getScore() const = 0;
  virtual glm::vec3	getPosPlayer() const = 0;
  virtual glm::vec3	getDirPlayer() const = 0;
};

#endif
