#include "IA.hpp"
#include "unistd.h"

IA::IA(int  id)
{
  this->_Last_dir = 0;
  this->_transformation = glm::rotate(this->_transformation, 180.0f, glm::vec3(0, 1, 0));
  this->_transformation = glm::translate(this->_transformation, glm::vec3(1, 0, 1));
  this->_transformation = glm::scale(this->_transformation, glm::vec3(0.0025f, 0.0025f, 0.0025f));
  this->_currentDir = DOWN;
  this->_Life = 1;
  this->_Speed = 55.0f;
  this->_Bomb = 1;
  this->_Range = 1;
  this->_id = id;
  this->_score = 0;
  this->_timeSart = steady_clock::now();
}

IA::IA(glm::vec3 pos, int id)
{
  pos *= glm::vec3(1, 0, 1);
  this->_Last_dir = 0;
  this->_transformation = glm::rotate(this->_transformation, 180.0f, glm::vec3(0, 1, 0));
  this->_transformation = glm::translate(this->_transformation, pos);
  this->_transformation = glm::scale(this->_transformation, glm::vec3(0.0025f, 0.0025f, 0.0025f));
  this->_currentDir = DOWN;
  this->_Life = 1;
  this->_Speed = 55.0f;
  this->_Bomb = 1;
  this->_Range = 1;
  this->_id = id;
  this->_score = 0;
  this->_timeSart = steady_clock::now();
}

IA::~IA()
{
}

bool	IA::initialize()
{
  if (rand() % 2)
    {
      if (!this->_model.load("./assets/marvin3.fbx"))
	{
	  std::cerr << "Cannot load the marvin3.fbx" << std::endl;
	  return (false);
	}
    }
  else
    if (!this->_model.load("./assets/marvin5.fbx"))
      {
	std::cerr << "Cannot load the marvin3.fbx" << std::endl;
	return (false);
      }
  this->_model.pause(true);
  return (true);
}

void	IA::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  this->_model.draw(shader, this->_transformation, clock.getElapsed());
}

bool	IA::update(__attribute__((unused))gdl::Clock const &clock, gdl::Input &input, Camera &cam, Map &map)
{
  this->_Clock = clock;
  this->ia_core(map);

  steady_clock::time_point t2 = steady_clock::now();
  duration<double> time_span = duration_cast<duration<double>>(t2 - this->_timeSart);

  if (time_span.count() > 3.0 &&
      (map.getMap(std::floor(-this->getPosZ()), std::floor(-this->getPosX())) == '4' ||
       map.getMap(std::ceil(-this->getPosZ()), std::ceil(-this->getPosX())) == '4'))
    {
      _timeSart = steady_clock::now();
      this->modifLife(-1);
      if (this->getLife() == 0)
	return (false);
      std::cout << "IA " << this->getId() << " : - 1 Life" << std::endl;
    }
  return (true);
}

void	IA::ia_core(Map &map)
{
  srand(time(NULL));
  int r = rand() % 4 + 1;

  if (check_danger(map) == true)
    this->_Last_dir = 0;
  check_move(map);
  if (this->_Last_dir != 0)
    r = this->_Last_dir;
  switch (r)
    {
    case 1:
      if (checkUp(map))
	this->_Last_dir = 1;
      else
	this->_Last_dir = 0;
      break;
    case 2:
      if (checkDown(map))
	this->_Last_dir = 2;
      else
	this->_Last_dir = 0;
      break;
    case 3:
      if (checkLeft(map))
	this->_Last_dir = 3;
      else
	this->_Last_dir = 0;
      break;
    case 4:
      if (checkRight(map))
	this->_Last_dir = 4;
      else
	this->_Last_dir = 0;
      break;
    default:
      break;
    }
  if (this->getBomb() > 0)
    {
      putBomb(map);
      this->_Last_dir = 0;
    }
}

float	IA::getAngleRota(eDirection nextDir)
{
  float		tmp;

  switch (this->_currentDir)
    {
    case UP:
      tmp = ((nextDir == RIGHT) ? -90.0f :
	     (nextDir == DOWN) ? 180.0f : 90.0f);
      break;
    case DOWN:
      tmp = ((nextDir == LEFT) ? -90.0f :
	     (nextDir == UP) ? 180.0f : 90.0f);
      break;
    case RIGHT:
      tmp = ((nextDir == DOWN) ? -90.0f :
	     (nextDir == LEFT) ? 180.0f : 90.0f);
      break;
    case LEFT:
      tmp = ((nextDir == UP) ? -90.0f :
	     (nextDir == RIGHT) ? 180.0f : 90.0f);
      break;
    }
  return (tmp);
}

bool    IA::checkLeft(Map &map)
{
  if (-(getPosX()) > 1.2)
    {
      float nbTmp = -getPosZ() - std::floor(-getPosZ());
      char tmp = map.getMap((nbTmp >= 0.5 ? std::ceil(-getPosZ()) : std::floor(-getPosZ())), std::floor(-getPosX()));
      if (tmp != 1 && tmp != '1' && tmp != '2')
	{
	  if (this->_currentDir != LEFT)
	    this->_transformation = glm::rotate(_transformation, this->getAngleRota(LEFT), glm::vec3(0, 1, 0));
	  this->_currentDir = LEFT;
	  this->_transformation = glm::translate(_transformation, (glm::vec3(0, 0, _Speed)));
	  return (true);
	}
    }
  return (false);
}

bool    IA::checkRight(Map &map)
{
  if (-(getPosX()) < map.getWidth() - 1.8)
    {
      float nbTmp = -getPosZ() - std::floor(-getPosZ());
      char tmp = map.getMap((nbTmp >= 0.5 ? std::ceil(-getPosZ()) : std::floor(-getPosZ())), std::floor(-getPosX() + 1));
      if (tmp != 1 && tmp != '1' && tmp != '2')
	{
	  if (this->_currentDir != RIGHT)
	    this->_transformation = glm::rotate(_transformation, this->getAngleRota(RIGHT), glm::vec3(0, 1, 0));
	  this->_currentDir = RIGHT;
	  this->_transformation = glm::translate(_transformation, (glm::vec3(0, 0, _Speed)));
	  return (true);
	}
    }
  return (false);
}

bool    IA::checkUp(Map &map)
{
  if (-(getPosZ()) > 1.2)
    {
      float nbTmp = -getPosX() - std::floor(-getPosX());
      char tmp = map.getMap(std::floor(-getPosZ() - 0.2), (nbTmp >= 0.5 ? std::ceil(-getPosX()) : std::floor(-getPosX())));
      if (tmp != 1 && tmp != '1' && tmp != '2')
	{
	  if (this->_currentDir != UP)
	    this->_transformation = glm::rotate(_transformation, this->getAngleRota(UP), glm::vec3(0, 1, 0));
	  this->_currentDir = UP;
	  this->_transformation = glm::translate(_transformation, (glm::vec3(0, 0, _Speed)));
	  return (true);
	}
    }
  return (false);
}

bool	IA::checkDown(Map &map)
{
  if (-(getPosZ()) < map.getHeight() - 1.8)
    {
      float nbTmp = -getPosX() - std::floor(-getPosX());
      char tmp = map.getMap(std::floor(-getPosZ() + 1), (nbTmp >= 0.5 ? std::ceil(-getPosX()) : std::floor(-getPosX())));
      if (tmp != 1 && tmp != '1' && tmp != '2')
	{
	  if (this->_currentDir != DOWN)
	    this->_transformation = glm::rotate(_transformation, this->getAngleRota(DOWN), glm::vec3(0, 1, 0));
	  this->_currentDir = DOWN;
	  this->_transformation = glm::translate(_transformation, (glm::vec3(0, 0, _Speed)));
	  return (true);
	}
    }
  return (false);
}

void	IA::putBomb(Map &map)
{
  if (map.getMap(std::floor(-(getPosZ())), std::floor(-(getPosX())) == '0'))
    {
      this->modifBomb(-1);
      map.setMap(std::floor(-(getPosZ())), std::floor(-(getPosX())), '3');
      map.checkMap(this->_Clock, this);
      std::cout << "IA " << this->getId() << " : - 1 Bomb" << std::endl;
    }
}

bool	IA::check_danger(Map &map)
{
  char	tmp;

  tmp = map.getMap(std::floor(-(getPosZ())), std::floor(-(getPosX())) - 1);
  if (tmp == '3' || tmp == '4')
    return (true);
  tmp = map.getMap(std::floor(-(getPosZ())), std::floor(-(getPosX())) + 1);
  if (tmp == '3' || tmp == '4')
    return (true);
  tmp = map.getMap(std::floor(-(getPosZ())) - 1, std::floor(-(getPosX())));
  if (tmp == '3' || tmp == '4')
    return (true);
  tmp = map.getMap(std::floor(-(getPosZ())) + 2, std::floor(-(getPosX())));
  if (tmp == '3' || tmp == '4')
    return (true);
  return (false);
}

void	IA::check_move(Map &map)
{
  char	tmp;

  tmp = map.getMap(std::floor(-(getPosZ())), std::floor(-(getPosX())));
  this->_Left = (tmp != '1' && tmp != '2') ? true : false;
  tmp = map.getMap(std::floor(-(getPosZ())), std::floor(-(getPosX())) + 1);
  this->_Right = (tmp != '1' && tmp != '2') ? true : false;
  tmp = map.getMap(std::floor(-(getPosZ())) - 1, std::floor(-(getPosX())));
  this->_Up = (tmp != '1' && tmp != '2') ? true : false;
  tmp = map.getMap(std::floor(-(getPosZ())) + 2, std::floor(-(getPosX())));
  this->_Down = (tmp != '1' && tmp != '2') ? true : false;
}


void		IA::modifLife(int const life)
{
  if (this->_Life < 4)
    this->_Life += life;
  std::cout << "IA " << _id << " : Total life " << _Life << std::endl;
}

void		IA::modifSpeed(int const speed)
{
  this->_Speed += speed;
  if (this->_Speed <= 55.0f)
    this->_Speed = 55.0f;
  std::cout << "IA " << _id << " : Total speed " << _Speed << std::endl;
}

void		IA::modifBomb(int const bomb)
{
  if (this->_Bomb < 10)
    this->_Bomb += bomb;
  else if (this->_Bomb <= 1)
    this->_Bomb = 1;
  std::cout << "IA " << _id << " : Total bomb " << _Bomb << std::endl;
}

void		IA::modifRange(int const range)
{
  if (this->_Range < 30)
    this->_Range += range;
  else if (this->_Range <= 1)
    this->_Range = 1;
  std::cout << "IA " << _id << " : Total range " << _Range << std::endl;
}
