#include "Map.hpp"

Map::Map()
{
  this->_map = NULL;
  this->_mapBack = NULL;
  this->_height = 0;
  this->_width = 0;
}

Map::~Map()
{
  if (this->_map)
    {
      for (int i = 0; i < this->_height; i++)
	delete[] this->_map[i];
      delete[] this->_map;
    }
  if (this->_mapBack)
    delete this->_mapBack;
  this->_map = NULL;
  this->_mapBack = NULL;
}

void		Map::freeMap()
{
  if (this->_map)
    {
      for (int i = 0; i < this->_height; i++)
	delete[] this->_map[i];
      this->_map = NULL;
    }
  delete this->_mapBack;
  this->_width = 0;
  this->_height = 0;
  this->_mapBack = NULL;
}

void		Map::draw(gdl::AShader &shader, gdl::Clock const &clock, int x, int y)
{
  int		tmpX;
  int		tmpZ;

  this->_mapBack->draw(shader, clock);
  for (size_t i = 0; i < this->_map3d.size(); ++i)
    {
      tmpX = i / this->_width;
      tmpZ = i % this->_width;
      if ((tmpX > (y - 12) && tmpX < (y + 12)) &&
	  (tmpZ > (x - 12) && tmpZ < (x + 12)))
	{
	  if (this->_map3d[i])
	    {
	      switch (this->_map3d[i]->getValue())
		{
		case '1':
		  this->_wallTexture.bind();
		  this->_map3d[i]->draw(shader, clock);
		  break;
		case '2':
		  this->_cubeTexture.bind();
		  this->_map3d[i]->draw(shader, clock);
		  break;
		case '3':
		  this->_map3d[i]->draw(shader, clock);
		  break;
		case '4':
		  this->_exploTexture.bind();
		  this->_map3d[i]->draw(shader, clock);
		  break;
		case '6':
		  this->_exploTexture.bind();
		  this->_map3d[i]->draw(shader, clock);
		  break;
		case 'a':
		  this->_moreBomb.bind();
		  this->_map3d[i]->draw(shader, clock);
		  break;
		case 'b':
		  this->_moreLife.bind();
		  this->_map3d[i]->draw(shader, clock);
		  break;
		case 'c':
		  this->_moreRange.bind();
		  this->_map3d[i]->draw(shader, clock);
		  break;
		case 'd':
		  this->_moreSpeed.bind();
		  this->_map3d[i]->draw(shader, clock);
		  break;
		case 'e':
		  this->_lessBomb.bind();
		  this->_map3d[i]->draw(shader, clock);
		  break;
		case 'f':
		  this->_lessSpeed.bind();
		  this->_map3d[i]->draw(shader, clock);
		  break;
		case 'g':
		  this->_lessRange.bind();
		  this->_map3d[i]->draw(shader, clock);
		  break;
		}
	    }
	}
    }
}

bool		Map::update(gdl::Clock const &clock, gdl::Input &input)
{
  for (size_t i = 0; i < this->_map3d.size(); ++i)
    {
      if (this->_map3d[i] && this->_map3d[i]->getValue() == '3')
	static_cast<Bomb *>(this->_map3d[i])->update(clock, input, const_cast<Map *>(this));
    }
  return (true);
}

void		Map::putBonus(int value, int x, int y)
{
  delete this->_map3d[(x * this->_width + y)];
  switch (value)
    {
    case 0:
      this->_map3d[(x * this->_width + y)] = new Bonus(this->_moreBomb, x, y);
      this->_map3d[(x * this->_width + y)]->initialize('a');
      this->_map[x][y] = 'a';
      break;
    case 2:
      this->_map3d[(x * this->_width + y)] = new Bonus(this->_moreLife, x, y);
      this->_map3d[(x * this->_width + y)]->initialize('b');
      this->_map[x][y] = 'b';
      break;
    case 4:
      this->_map3d[(x * this->_width + y)] = new Bonus(this->_moreRange, x, y);
      this->_map3d[(x * this->_width + y)]->initialize('c');
      this->_map[x][y] = 'c';
      break;
     case 6:
      this->_map3d[(x * this->_width + y)] = new Bonus(this->_moreSpeed, x, y);
      this->_map3d[(x * this->_width + y)]->initialize('d');
      this->_map[x][y] = 'd';
      break;
     case 8:
      this->_map3d[(x * this->_width + y)] = new Bonus(this->_lessBomb, x, y);
      this->_map3d[(x * this->_width + y)]->initialize('e');
      this->_map[x][y] = 'e';
      break;
     case 10:
      this->_map3d[(x * this->_width + y)] = new Bonus(this->_lessSpeed, x, y);
      this->_map3d[(x * this->_width + y)]->initialize('f');
      this->_map[x][y] = 'f';
      break;
     case 12:
      this->_map3d[(x * this->_width + y)] = new Bonus(this->_lessRange, x, y);
      this->_map3d[(x * this->_width + y)]->initialize('g');
      this->_map[x][y] = 'g';
      break;
    default:
      this->_map3d[(x * this->_width + y)] = NULL;
      break;
    }
}

void		Map::checkMap(__attribute__((unused))gdl::Clock const &clock, IPerso *perso)
{
  for (int x = 0; x < this->_height; x++)
    {
      for (int y = 0; y < this->_width; y++)
	{
	  if (this->_map[x][y])
	    switch (this->_map[x][y])
	      {
	      case '3':
		if (!this->_map3d[(x * this->_width + y)])
		  this->_map3d[(x * this->_width + y)] = new Bomb(x, y, this->_bomb, perso);
		break;
	      case '4':
		if (this->_map3d[(x * this->_width + y)] && this->_map3d[(x * this->_width + y)]->getValue() == '2')
		  {
		    delete this->_map3d[(x * this->_width + y)];
		    this->_map3d[(x * this->_width + y)] = new Cube(this->_exploTexture);
		    this->_map3d[(x * this->_width + y)]->translate(glm::vec3(-y, 0, -x));
		    this->_map3d[(x * this->_width + y)]->initialize('6');
		    break;
		  }
		else if (this->_map3d[(x * this->_width + y)] && this->_map3d[(x * this->_width + y)]->getValue() >= 'a' &&
			 this->_map3d[(x * this->_width + y)]->getValue() <= 'g')
		  {
		    delete this->_map3d[(x * this->_width + y)];
		    this->_map3d[(x * this->_width + y)] = NULL;
		  }
		if (!this->_map3d[(x * this->_width + y)])
		  {
		    this->_map3d[(x * this->_width + y)] = new Cube(this->_exploTexture);
		    this->_map3d[(x * this->_width + y)]->translate(glm::vec3(-y, 0, -x));
		    this->_map3d[(x * this->_width + y)]->initialize('4');
		  }
		break;
	      default:
		if (this->_map3d[(x * this->_width + y)] &&
		    (this->_map[x][y] != this->_map3d[(x * this->_width + y)]->getValue()))
		  {
		    if (this->_map3d[(x * this->_width + y)]->getValue() == '6')
		      putBonus(rand() % 20, x, y);
		    else
		      {
			delete this->_map3d[(x * this->_width + y)];
			this->_map3d[(x * this->_width + y)] = NULL;
		      }
		  }
		break;
	      }
	}
    }
}

bool		Map::initializeMap()
{
  if (!this->_cubeTexture.load("./imgs/box.tga"))
    {
      std::cout << "Cannot load the box.tga" << std::endl;
      return (false);
    }
  std::cout << "./imgs/box.tga loaded" << std::endl;
  if (!this->_wallTexture.load("./imgs/wall.tga"))
    {
      std::cout << "Cannot load the wall.tga" << std::endl;
      return (false);
    }
  std::cout << "./imgs/wall.tga loaded" << std::endl;
  if (!this->_exploTexture.load("./imgs/explosion.tga"))
    {
      std::cout << "Cannot load the explosion.tga" << std::endl;
      return (false);
    }
  std::cout << "./imgs/explosion.tga loaded" << std::endl;
  if (!this->_bomb.load("./assets/bomb.obj"))
    {
      std::cerr << "Cannot load the bomb.obj" << std::endl;
      return (false);
    }
  std::cout << "./imgs/bomb.obj loaded" << std::endl;
  if (!this->_moreSpeed.load("./imgs/lapin_up.tga"))
    {
      std::cout << "Cannot load the lapin_up.tga" << std::endl;
      return (false);
    }
  std::cout << "./imgs/lapin_up.tga loaded" << std::endl;
  if (!this->_moreBomb.load("./imgs/bomb_up.tga"))
    {
      std::cout << "Cannot load the bomb_up.tga" << std::endl;
      return (false);
    }
  std::cout << "./bomb_up.tga loaded" << std::endl;
  if (!this->_moreRange.load("./imgs/range.tga"))
    {
      std::cout << "Cannot load the up.tga" << std::endl;
      return (false);
    }
  std::cout << "./imgs/range.tga loaded" << std::endl;
  if (!this->_moreLife.load("./imgs/life.tga"))
    {
      std::cout << "Cannot load the life.tga" << std::endl;
      return (false);
    }
  std::cout << "./imgs/life.tga loaded" << std::endl;
  if (!this->_lessRange.load("./imgs/rangedown.tga"))
    {
      std::cout << "Cannot load the rangedown.tga" << std::endl;
      return (false);
    }
  std::cout << "./imgs/rangedown.tga loaded" << std::endl;
  if (!this->_lessSpeed.load("./imgs/lapin_down.tga"))
    {
      std::cout << "Cannot load the lapin_down.tga" << std::endl;
      return (false);
    }
  std::cout << "./imgs/lapin_down.tga loaded" << std::endl;
  if (!this->_lessBomb.load("./imgs/bomb_down.tga"))
    {
      std::cout << "Cannot load the bomb_down.tga" << std::endl;
      return (false);
    }
  std::cout << "./imgs/bomb_down.tga loaded" << std::endl;
  return (true);
}

void		Map::loadMap(int map)
{
  std::ifstream file;

  if (map == 0)
    {
      file.open("./.map/map1", std::ios::in);
      this->_height = std::count(std::istreambuf_iterator<char>(file),
				 std::istreambuf_iterator<char>(), '\n' );
      file.close();
    }
  else if (map == 1)
    {
      file.open("./.map/map2", std::ios::in);
      this->_height = std::count(std::istreambuf_iterator<char>(file),
				 std::istreambuf_iterator<char>(), '\n' );
      file.close();
    }
}

bool		Map::classic(int map, std::string way)
{
  std::ifstream file;
  std::string	s;

  loadMap(map);
  way += std::to_string(map + 1);
  file.open(way, std::ios::in);
  if (file.is_open())
    {
      std::getline(file, s);
      this->_width = s.size();
      this->_mapBack = new LoadTexture(90, 1, 1, 1);
      this->_map3d.assign((this->_width * this->_height + 1), NULL);
      this->_mapBack->translate(glm::vec3(this->_height / 2 - 0.5, -(this->_width) / 2 + 0.5, 0));
      this->_mapBack->rotate(glm::vec3(1, 0, 0), 90);
      if (!this->_mapBack->initialize(this->_height / 2, this->_width / 2, "./imgs/fondMap.tga"))
	return (false);
      this->_map = new char *[this->_height + 1];
      int  i;
      for (i = 0; i < this->_height; i++)
	{
	  this->_map[i] = new char[this->_width + 1];
	  strcpy(this->_map[i], s.c_str());
	  this->chechCase(i);
	  std::getline(file, s);
	}
      this->_map[i] = NULL;
      file.close();
      return (true);
    }
  else
    {
      std::cout << "Error while loading  map" << std::endl;
      return (false);
    }
}

void		Map::getHandW(std::string way)
{
  std::ifstream file;
  std::string	s;

  file.open(way, std::ios::in);
  if (file.is_open())
    {
      std::getline(file, s);
      this->_width = s.size();
      while (s.compare(0, 5, "perso"))
	{
	  this->_height++;
	  std::getline(file, s);
	}
      file.close();
    }
}

void		Map::chechCase(int i)
{
  for (int j = 0; j < this->_width; j++)
    {
      if (this->_map[i][j] == '1')
	{
	  this->_map3d[(i * this->_width + j)] = new Cube(this->_wallTexture);
	  this->_map3d[(i * this->_width + j)]->translate(glm::vec3(-j, 0, -i));
	  this->_map3d[(i * this->_width + j)]->initialize('1');
	}
      else if (this->_map[i][j] == '2')
	{
	  this->_map3d[(i * this->_width + j)] = new Cube(this->_cubeTexture);
	  this->_map3d[(i * this->_width + j)]->translate(glm::vec3(-j, 0, -i));
	  this->_map3d[(i * this->_width + j)]->initialize('2');
	}
    }
}

bool		Map::resume(std::string way)
{
  std::ifstream file;
  std::string	s;

  getHandW(way);
  file.open(way, std::ios::in);
  if (file.is_open())
    {
      this->_map3d.assign((this->_width * this->_height + 1), NULL);
      std::getline(file, s);
      this->_map = new char *[this->_height + 1];
      int  i = 0;
      while (s.compare(0, 5, "perso"))
	{
	  this->_map[i] = new char[this->_width + 1];
	  strcpy(this->_map[i], s.c_str());
	  this->chechCase(i);
	  std::getline(file, s);
	  i++;
	}
      this->_map[i] = NULL;
      file.close();
      this->_mapBack = new LoadTexture(90, 1, 1, 1);
      this->_mapBack->translate(glm::vec3(this->_height / 2 - 1, -(this->_width) / 2 + 0.5, 0));
      this->_mapBack->rotate(glm::vec3(1, 0, 0), 90);
      if (!this->_mapBack->initialize(this->_height / 2, this->_width / 2, "./imgs/fondMap.tga"))
	return (false);
      file.close();
    }
  else
    {
      throw ("Error while loading  map");
    }
  return (true);
}

bool		Map::loadingMap(int map, std::string way)
{
  if (way.empty())
    {
      this->_map3d.assign((this->_width * this->_height + 1), NULL);
      this->_mapBack = new LoadTexture(90, 1, 1, 1);
      this->_mapBack->translate(glm::vec3(this->_height / 2 - 0.5, -(this->_width) / 2 + 0.5, 0));
      this->_mapBack->rotate(glm::vec3(1, 0, 0), 90);
      if (!this->_mapBack->initialize(this->_height / 2, this->_width / 2, "./imgs/fondMap.tga"))
	return (false);
      this->stdRandomMap(rand() % 60, rand() % 2);
      for (int i = 0; i < this->_height; i++)
	this->chechCase(i);
    }
  if (!way.compare("./.map/map"))
    {
      if (!classic(map, way))
	return (false);
    }
  else if (!way.compare("./.save/game.save"))
    if (!resume(way))
      return (false);
  return (true);
}


void		Map::createStdMap()
{
  int		x = 0;
  int		y = 0;

  for (x = 0; x < this->_width; x++)
    {
      this->_map[x] = new char[this->_width + 1];
      for (y = 0; y < this->_height; y++)
	{
	  this->_map[x][y] = '0';
	}
    }
  for (y = 0; y < this->_width; y++)
    {
      for (x = 0; x < this->_width; x++)
	{
	  if (x == 1 || x == this->_width - 2 || y == 1 || y == this->_width - 2 ||
	      (this->_map[x][y] == '0' && x > 1 && y > 1 && y < this->_width - 2 && x < this->_width - 2))
	    this->_map[x][y] = '2';
	  if (x == 0 || y == 0 || y == this->_width - 1 || x == this->_width - 1 ||
	      (x % 2 == 0 && y % 2 == 0 && x > 1 && y > 1 && y < this->_width - 2 && x < this->_width - 2))
	    this->_map[x][y] = '1';
	  else if (((x == 1 || x == this->_width - 2) && (y < 3 || y >= this->_width - 3)) ||
		   ((y == 1 || y == this->_width - 2) && (x < 3 || x >= this->_width - 3)))
	    this->_map[x][y] = '0';
	}
    }
}

void		Map::stdRandomMap(float const density, int const pm2, int const seed)
{
  int		x = 0;
  int		y = 0;

  this->_map = new char *[this->_height + 1];
  this->createStdMap();
  if (density >= 100) return;
  seed == 42 ? srand(static_cast<unsigned> (time(NULL))) : srand(static_cast<unsigned> (seed));
  for (y = 2; y < this->_width - 2; y++)
    {
      for (x = 2; x < this->_width - 2; x++)
	{
	  if (rand() % 100 >= density && this->_map[x][y] == '1' && pm2 == 1 ||
	      (this->_map[x][y] != '1' && rand() % 100 <= density))
	    this->_map[x][y] = '0';
	  else if (rand() % 100 < density && this->_map[x][y] == '0')
	    this->_map[x][y] = '2';
	}
    }
}

int			Map::_addDensityProb(int const density, int const x, int const y)
{
  int			 map[2][4] = { { 1, 0, -1, 0 }, { 0, -1, 0, 1 } };
  int			 loop = 0;
  int			 proximity = 0;

  for (loop = 0; loop < 4; loop++)
    {
      if (this->_map[x + map[0][loop]][y + map[1][loop]] == '1')
	proximity += 1;
    }
  return (density * (proximity * 10) / 100);
}

void		Map::advancedRandomMap(int const density, int const seed)
{
  int		x = 0;
  int		y = 0;
  seed == 42 ? srand(static_cast<unsigned> (time(NULL))) : srand(static_cast<unsigned> (seed));
  this->createStdMap();
  if (density >= 100) return;
  for (y = 2; y < this->_width - 2; y++)
    {
      for (x = 2; x < this->_width - 2; x++)
	{
	  if (rand() % 100 < density + this->_addDensityProb(density, x, y) && this->_map[x][y] != '1')
	    this->_map[x][y] = '1';
	  else if (rand() % 100 < density && this->_map[x][y] == '2')
	    this->_map[x][y] = '0';
	}
    }
}

void		Map::clear_spawn(int const spawn_x, int const spawn_y)
{
  int		map[2][4] = { { 1, 0, -1, 0 }, { 0, -1, 0, 1 } };
  int		loop = 0;

  for (loop = 0; loop < 4; loop++)
    {
      if (spawn_x + map[0][loop] > 0 && spawn_y + map[1][loop] > 0 &&
	  spawn_x + map[0][loop] < this->_height && spawn_y + map[1][loop] < this->_width)
	if (this->_map[spawn_x + map[0][loop]][spawn_y + map[1][loop]] != '1')
	  this->_map[spawn_x + map[0][loop]][spawn_y + map[1][loop]] = '0';
    }
}

glm::vec3*	Map::spawnPlayer(unsigned int const nb)
{
  int		proximity = 0;
  int		i = 0;
  int		spawnMap[11][2] = {{1, 1}, {this->_width - 2, 1}, {1, this->_height - 2},
				   {this->_width - 2, this->_height - 2}, {this->_width / 2, 1},
				   {1, this->_height / 2}, {this->_width / 2, this->_height / 2},
				   {this->_width / 3, this->_height / 3}, {this->_width / 3 * 2, this->_height / 3 * 2},
				   {this->_width / 3 * 2, this->_height / 3}, {this->_width / 3, this->_height / 3 * 2}};

  if (nb > 11) return NULL;
  glm::vec3* spawnZone = new glm::vec3[nb];
  for(i = 0; i < nb; i++)
    {
      spawnZone[i] = glm::vec3(spawnMap[i][0], 0, spawnMap[i][1]);
      clear_spawn(spawnMap[i][0], spawnMap[i][1]);
    }
  return spawnZone;
}
