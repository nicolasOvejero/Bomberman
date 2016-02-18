#include <iostream>
#include <Geometry.hh>
#include "Marvin.hpp"

Marvin::Marvin(int id)
{
  this->_transformation = glm::rotate(this->_transformation, 180.0f, glm::vec3(0, 1, 0));
  this->_transformation = glm::translate(this->_transformation, glm::vec3(1, 0, 1));
  this->_transformation = glm::scale(this->_transformation, glm::vec3(0.0025f, 0.0025f, 0.0025f));
  this->_currentDir = DOWN;
  this->_Life = 1;
  this->_Speed = 55.0f;
  this->_Bomb = 1;
  this->_Range = 1;
  this->_id = id;
  if (id < 3)
    {
      this->_up = (this->_id == 1 ? SDLK_UP : SDLK_z);
      this->_down = (this->_id == 1 ? SDLK_DOWN : SDLK_s);
      this->_left = (this->_id == 1 ? SDLK_LEFT : SDLK_q);
      this->_right = (this->_id == 1 ? SDLK_RIGHT : SDLK_d);
      this->_bomb = (this->_id == 1 ? SDLK_KP_0 : SDLK_LSHIFT);
    }
  this->_score = 0;
  this->_timeSart = steady_clock::now();
}

Marvin::Marvin(glm::vec3 pos, int id)
{
  pos *= glm::vec3(1, 0, 1);
  if (id == 1)
    {
      _pos = glm::vec3(-(20 / 7), 20 / 2.5, -(20 / 5));
      _dir = glm::vec3(-(20 / 7), 0, 0);
    }
  else
    {
      _pos = glm::vec3(-pos.x, 20 / 2.5, -(20 / 5));
      _dir = glm::vec3(-pos.x, 0, 0);
    }
  this->_transformation = glm::rotate(this->_transformation, 180.0f, glm::vec3(0, 1, 0));
  this->_transformation = glm::translate(_transformation, pos);
  this->_transformation = glm::scale(this->_transformation, glm::vec3(0.0025f, 0.0025f, 0.0025f));
  this->_currentDir = DOWN;
  this->_Life = 1;
  this->_Speed = 55.0f;
  this->_Bomb = 1;
  this->_Range = 1;
  this->_id = id;
  if (id < 3)
    {
      this->_up = (this->_id == 1 ? SDLK_UP : SDLK_z);
      this->_down = (this->_id == 1 ? SDLK_DOWN : SDLK_s);
      this->_left = (this->_id == 1 ? SDLK_LEFT : SDLK_q);
      this->_right = (this->_id == 1 ? SDLK_RIGHT : SDLK_d);
      this->_bomb = (this->_id == 1 ? SDLK_KP_0 : SDLK_LSHIFT);
    }
  this->_score = 0;
  this->_timeSart = steady_clock::now();
}

Marvin::~Marvin()
{ }

bool		Marvin::initialize()
{
  if (this->_id == 1)
    {
      if (!this->_model.load("./assets/marvin2.FBX"))
	{
	  std::cerr << "Cannot load the marvin2.fbx" << std::endl;
	  return (false);
	}
    }
  else
    {
      if (!this->_model.load("./assets/marvin4.fbx"))
	{
	  std::cerr << "Cannot load the marvin4.fbx" << std::endl;
	  return (false);
	}
    }
  this->_model.createSubAnim(0, "run", 37, 53);
  this->_model.setCurrentSubAnim("run");
  this->_model.pause(true);
  return (true);
}

float		Marvin::getAngleRota(eDirection nextDir)
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

bool		Marvin::checkLeft(gdl::Input &input, Camera &cam, Map &map)
{
  if (input.getKey(this->_left) && -getPosX() > 1.2)
    {
      float nbTmp = -getPosZ() - std::floor(-getPosZ());
      char tmp = map.getMap((nbTmp >= 0.5 ? std::ceil(-getPosZ()) : std::floor(-getPosZ())), std::floor(-getPosX()));
      if (tmp != '1' && tmp != '2')
	{
	  this->_model.pause(false);
	  if (this->_currentDir != LEFT)
	    this->_transformation = glm::rotate(_transformation, this->getAngleRota(LEFT), glm::vec3(0, 1, 0));
	  this->_currentDir = LEFT;
	  this->_transformation = glm::translate(_transformation, (glm::vec3(0, 0, _Speed)));
	  cam.moveCam(glm::vec3((this->_Speed / 400), 0, 0), this->_id - 1);
	  return (true);
	}
    }
  return (false);
}

bool		Marvin::checkRight(gdl::Input &input, Camera &cam, Map &map)
{
  if (input.getKey(this->_right) && -getPosX() < map.getWidth() - 1.8)
    {
      float nbTmp = -getPosZ() - std::floor(-getPosZ());
      char tmp = map.getMap((nbTmp >= 0.5 ? std::ceil(-getPosZ()) : std::floor(-getPosZ())), std::floor(-getPosX() + 1));
      if (_id == 0)
	tmp = '0';
      if (tmp != '1' && tmp != '2')
	{
	  this->_model.pause(false);
	  if (this->_currentDir != RIGHT)
	    this->_transformation = glm::rotate(_transformation, this->getAngleRota(RIGHT), glm::vec3(0, 1, 0));
	  this->_currentDir = RIGHT;
	  this->_transformation = glm::translate(_transformation, (glm::vec3(0, 0, _Speed)));
	  cam.moveCam(glm::vec3(-(this->_Speed / 400), 0, 0), this->_id - 1);
	  return (true);
	}
    }
  return (false);
}

bool		Marvin::checkUp(gdl::Input &input, Camera &cam, Map &map)
{
  if (input.getKey(this->_up) && -getPosZ() > 1.1)
    {
      float nbTmp = -getPosX() - std::floor(-getPosX());
      char tmp = map.getMap(std::floor(-getPosZ() - 0.2), (nbTmp >= 0.5 ? std::ceil(-getPosX()) : std::floor(-getPosX())));
      if (tmp != '1' && tmp != '2')
	{
	  this->_model.pause(false);
	  if (this->_currentDir != UP)
	    this->_transformation = glm::rotate(_transformation, this->getAngleRota(UP), glm::vec3(0, 1, 0));
	  this->_currentDir = UP;
	  this->_transformation = glm::translate(_transformation, (glm::vec3(0, 0, _Speed)));
	  cam.moveCam(glm::vec3(0, 0, (this->_Speed / 400)), this->_id - 1);
	  return (true);
	}
    }
  return (false);
}

bool		Marvin::checkDown(gdl::Input &input, Camera &cam, Map &map)
{
  if (input.getKey(this->_down) && -getPosZ() < map.getHeight() - 1.8)
    {
      float nbTmp = -getPosX() - std::floor(-getPosX());
      char tmp = map.getMap(std::floor(-getPosZ() + 1), (nbTmp >= 0.5 ? std::ceil(-getPosX()) : std::floor(-getPosX())));
      if (tmp != '1' && tmp != '2')
	{
	  this->_model.pause(false);
	  if (this->_currentDir != DOWN)
	    this->_transformation = glm::rotate(_transformation, this->getAngleRota(DOWN), glm::vec3(0, 1, 0));
	  this->_currentDir = DOWN;
	  this->_transformation = glm::translate(_transformation, (glm::vec3(0, 0, _Speed)));
	  cam.moveCam(glm::vec3(0, 0, -(this->_Speed / 400)), this->_id - 1);
	  return (true);
	}
    }
  return (false);
}

void		Marvin::putBomb(Map &map, gdl::Clock const &clock)
{
  if (_id != 0 && map.getMap(std::floor(-getPosZ()), std::floor(-getPosX())) == '0')
    {
      this->_Bomb--;
      std::cout << "Player " << _id << " : - 1 Bomb" << std::endl;
      map.setMap(std::floor(-getPosZ()), std::floor(-getPosX()), '3');
      map.checkMap(clock, this);
    }
}

bool		Marvin::checkLife(Map &map, Camera &cam)
{
  steady_clock::time_point t2 = steady_clock::now();
  duration<double> time_span = duration_cast<duration<double>>(t2 - this->_timeSart);

  if (_id != 0 && time_span.count() > 3.0 &&
      (map.getMap(std::floor(-getPosZ()), std::floor(-getPosX())) == '4' ||
       map.getMap(std::ceil(-getPosZ()), std::ceil(-getPosX())) == '4'))
    {
      std::cout << "Player " << _id << " : - 1 Life" << std::endl;
      this->_Life--;
      this->_timeSart = steady_clock::now();
      if (this->_Life == 0)
	return (false);
    }
  return (true);
}

void		Marvin::modifLife(int const life)
{
  if (this->_Life < 4)
    this->_Life += life;
  std::cout << "Player " << _id << " : Total life " << _Life << std::endl;
}

void		Marvin::modifSpeed(int const speed)
{
  this->_Speed += speed;
  if (this->_Speed <= 55.0f)
    this->_Speed = 55.0f;
  std::cout << "Player " << _id << " : Total speed " << _Speed << std::endl;
}

void		Marvin::modifBomb(int const bomb)
{
  if (this->_Bomb < 10)
    this->_Bomb += bomb;
  if (this->_Bomb <= 1)
    this->_Bomb = 1;
  std::cout << "Player " << _id << " : Total bomb " << _Bomb << std::endl;
}

void		Marvin::modifRange(int const range)
{
  if (this->_Range < 30)
    this->_Range += range;
  if (this->_Range <= 1)
    this->_Range = 1;
  std::cout << "Player " << _id << " : Total range " << _Range << std::endl;
}

bool		Marvin::ckeckBonus(gdl::Clock const &clock, Map &map)
{
  char tmp = map.getMap(std::floor(-getPosZ()), std::floor(-getPosX()));

  switch (tmp)
    {
    case 'a':
      this->modifBomb(1);
      map.setMap(std::floor(-getPosZ()), std::floor(-getPosX()), '0');
      map.checkMap(clock);
      return true;
    case 'b':
      this->modifLife(1);
      map.setMap(std::floor(-getPosZ()), std::floor(-getPosX()), '0');
      map.checkMap(clock);
      return true;
    case 'c':
      this->modifRange(1);
      map.setMap(std::floor(-getPosZ()), std::floor(-getPosX()), '0');
      map.checkMap(clock);
      return true;
    case 'd':
      this->modifSpeed(10);
      map.setMap(std::floor(-getPosZ()), std::floor(-getPosX()), '0');
      map.checkMap(clock);
      return true;
    case 'e':
      this->modifBomb(-1);
      map.setMap(std::floor(-getPosZ()), std::floor(-getPosX()), '0');
      map.checkMap(clock);
      return true;
    case 'f':
      this->modifSpeed(-10);
      map.setMap(std::floor(-getPosZ()), std::floor(-getPosX()), '0');
      map.checkMap(clock);
      return true;
    case 'g':
      this->modifRange(-1);
      map.setMap(std::floor(-getPosZ()), std::floor(-getPosX()), '0');
      map.checkMap(clock);
      return true;
    }
  return false;
}

bool		Marvin::update(gdl::Clock const &clock,
			       gdl::Input &input, Camera &cam, Map &map)
{
  if (!ckeckBonus(clock, map))
    {
      if (!checkLife(map, cam))
	return (false);
      if (input.getKey(this->_bomb, true) && this->_Bomb > 0)
	this->putBomb(map, clock);
      else
	{
	  this->_model.pause(true);
	  if (!checkUp(input, cam, map))
	    if (!checkDown(input, cam, map))
	      if (!checkLeft(input, cam, map))
		checkRight(input, cam, map);
	}
    }
  return (true);
}

bool		Marvin::update(gdl::Clock const &clock, gdl::Input &input, Camera &cam, int id)
{
  if (input.getKey(this->_up))
    {
      if (this->_currentDir != UP)
	this->_transformation = glm::rotate(_transformation, this->getAngleRota(UP), glm::vec3(0, 1, 0));
      this->_currentDir = UP;
      this->_transformation = glm::translate(_transformation, (glm::vec3(0, 0, _Speed)));
      cam.moveCam(glm::vec3(0, 0, (this->_Speed / 400)), id);
    }
  if (input.getKey(this->_down))
    {
      if (this->_currentDir != DOWN)
	this->_transformation = glm::rotate(_transformation, this->getAngleRota(DOWN), glm::vec3(0, 1, 0));
      this->_currentDir = DOWN;
      this->_transformation = glm::translate(_transformation, (glm::vec3(0, 0, _Speed)));
      cam.moveCam(glm::vec3(0, 0, -(this->_Speed / 400)), id);
    }
  if (input.getKey(this->_right))
    {
      if (this->_currentDir != RIGHT)
	this->_transformation = glm::rotate(_transformation, this->getAngleRota(RIGHT), glm::vec3(0, 1, 0));
      this->_currentDir = RIGHT;
      this->_transformation = glm::translate(_transformation, (glm::vec3(0, 0, _Speed)));
      cam.moveCam(glm::vec3(-(this->_Speed / 400), 0, 0), id);
    }
  if (input.getKey(this->_left))
    {
      if (this->_currentDir != LEFT)
	this->_transformation = glm::rotate(_transformation, this->getAngleRota(LEFT), glm::vec3(0, 1, 0));
      this->_currentDir = LEFT;
      this->_transformation = glm::translate(_transformation, (glm::vec3(0, 0, _Speed)));
      cam.moveCam(glm::vec3((this->_Speed / 400), 0, 0), id);
    }
  return (true);
}

void		Marvin::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  if (_id != 0)
    this->_model.draw(shader, this->_transformation, clock.getElapsed());
}
