#include "Bomb.hpp"

Bomb::Bomb(gdl::Model &model, IPerso *who) :
  _model(model)
{
  this->_transformation = glm::rotate(this->_transformation, 180.0f, glm::vec3(0, 1, 0));
  this->_transformation = glm::translate(this->_transformation, glm::vec3(1, 0, 1));
  this->_transformation = glm::scale(this->_transformation, glm::vec3(0.055f, 0.055f, 0.055f));
  this->_value = '3';
  this->_timeSart = steady_clock::now();
  this->_boom = false;
  this->_who = who;
  this->_left = false;
  this->_right = false;
  this->_up = false;
  this->_down = false;
}

Bomb::Bomb(int x, int y, gdl::Model &model, IPerso *who) :
  _model(model)
{
  this->_transformation = glm::rotate(this->_transformation, 180.0f, glm::vec3(0, 1, 0));
  this->_transformation = glm::translate(this->_transformation, glm::vec3(y, 0, x));
  this->_transformation = glm::scale(this->_transformation, glm::vec3(0.055f, 0.055f, 0.055f));
  this->_value = '3';
  this->_timeSart = steady_clock::now();
  this->_x = x;
  this->_y = y;
  this->_boom = false;
  this->_who = who;
  this->_left = false;
  this->_right = false;
  this->_up = false;
  this->_down = false;
}

bool		Bomb::initialize()
{
  return (true);
}

void		Bomb::update(gdl::Clock const &clock, __attribute__((unused))gdl::Input &input,
			     Map *map)
{
  steady_clock::time_point t2 = steady_clock::now();
  duration<double> time_span = duration_cast<duration<double>>(t2 - this->_timeSart);
  char tmp;

  if (time_span.count() > 2.0 && !this->_boom)
    {
      this->_boom = true;
      for (int i = 0; i < this->_who->getRange(); i++)
	{
	  tmp = map->getMap(this->_x - (i + 1), this->_y);
	  if (tmp != -1 && (tmp == '0' || (tmp >= 'a' && tmp <= 'g')) && !_left)
	    map->setMap(this->_x - (i + 1), this->_y, '4');
	  else if (tmp != -1 && tmp == '2' && !_left)
	    {
	      _left = true;
	      this->_who->setScore(20);
	      map->setMap(this->_x - (i + 1), this->_y, '4');
	    }
	  else if (tmp != -1 && tmp == '1' && !_left)
	    _left = true;
	  tmp = map->getMap(this->_x + (i + 1), this->_y);
	  if (tmp != -1 && (tmp == '0' || (tmp >= 'a' && tmp <= 'g')) && !_right)
	    map->setMap(this->_x + (i + 1), this->_y, '4');
	  else if (tmp != -1 && tmp == '2' && !_right)
	    {
	      _right = true;
	      this->_who->setScore(20);
	      map->setMap(this->_x + (i + 1), this->_y, '4');
	    }
	  else if (tmp != -1 && tmp == '1' && !_right)
	    _right = true;
	  tmp = map->getMap(this->_x, this->_y - (i + 1));
	  if (tmp != -1 && (tmp == '0' || (tmp >= 'a' && tmp <= 'g')) && !_up)
	    map->setMap(this->_x, this->_y - (i + 1), '4');
	  else if (tmp != -1 && tmp == '2' && !_up)
	    {
	      _up = true;
	      this->_who->setScore(20);
	      map->setMap(this->_x, this->_y - (i + 1), '4');
	    }
	  else if (tmp != -1 && tmp == '1' && !_up)
	    _up = true;
	  tmp = map->getMap(this->_x, this->_y + (i + 1));
	  if (tmp != -1 && (tmp == '0' || (tmp >= 'a' && tmp <= 'g')) && !_down)
	    map->setMap(this->_x, this->_y + (i + 1), '4');
	  else if (tmp != -1 && tmp == '2' && !_down)
	    {
	      _down = true;
	      this->_who->setScore(20);
	      map->setMap(this->_x, this->_y + (i + 1), '4');
	    }
	  else if (tmp != -1 && tmp == '1' && !_down)
	    _down = true;
	}
      map->checkMap(clock, this->_who);
    }
  else if (time_span.count() > 2.5 && this->_boom)
    {
      if (this->_who->getId())
	this->_who->modifBomb(1);
      for (int i = 0; i < this->_who->getRange(); i++)
	{
	  if (map->getMap(this->_x - (i + 1), this->_y) == '4')
	    map->setMap(this->_x - (i + 1), this->_y, '0');
	  if (map->getMap(this->_x + (i + 1), this->_y) == '4')
	    map->setMap(this->_x + (i + 1), this->_y, '0');
	  if (map->getMap(this->_x, this->_y - (i + 1)) == '4')
	    map->setMap(this->_x, this->_y - (i + 1), '0');
	  if (map->getMap(this->_x, this->_y + (i + 1)) == '4')
	    map->setMap(this->_x, this->_y + (i + 1), '0');
	  map->setMap(this->_x, this->_y, '0');
	}

      map->checkMap(clock, this->_who);
    }
}

void		Bomb::draw(gdl::AShader &shader, gdl::Clock const &clock)
{
  this->_model.draw(shader, this->_transformation, clock.getElapsed());
}
