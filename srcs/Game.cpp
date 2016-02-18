#include <string>
#include <algorithm>
#include <condition_variable>
#include "Game.hpp"

GLXContext		context;
Display			*display;
GLXDrawable		drawable;
std::mutex		m;
std::mutex		m1;
std::mutex		upia;
std::mutex		upia1;
std::condition_variable	cond_upia;
std::condition_variable	cond_upia1;
std::condition_variable	cond_var;
std::condition_variable	cond_var1;
int			nb = 0;

MyGame::MyGame()
{
  this->_nbPlayer = 1;
  this->_nbMusic = 5;
  this->_subret = 1;
  this->_nbIA = 0;
  this->_nbPerso = 0;
}

MyGame::~MyGame()
{
  while (!this->_perso.empty())
    {
      delete this->_perso.back();
      this->_perso.pop_back();
    }
  this->_window.stop();
}

bool	MyGame::startWin()
{
  if (!this->_window.start(WINX, WINY, "THE JURA'S BOMBERMAN", SDL_INIT_VIDEO))
    {
      std::cerr << "Error : can not start" << std::endl;
      return (false);
    }
  if (!this->_camera.initialize())
    return (false);
  this->_subMenu.initialize();
  this->_playMenu.initialize();
  this->_menu.initialize();
  this->_optionMenu.initialize();
  sound.initilize();
  context = glXGetCurrentContext();
  display = glXGetCurrentDisplay();
  drawable = glXGetCurrentDrawable();
  return (true);
}

bool	MyGame::initialize()
{
  int	value = -1;

  this->startWin();
  this->intro();
  sound.playMusic(2, -1);
  this->_players.initialize();
  this->_players.putStr("Nb of player ?", glm::vec4(0, 0.5, 1, 1), 4);
  while (value)
    {
      switch (value)
	{
	case -1:
	  if ((value = this->menu()) == -1)
	    return (false);
	  break;
	case 1:
	  value = this->playMenu();
	  break;
	case 2:
	  this->play("./.save/game.save");
	  value = -1;
	  break;
	case 3:
	  value = this->option();
	  break;
	case 4:
	  while (!this->_input.getKey(SDLK_KP_1) && !this->_input.getInput(SDLK_KP_2))
	    {
	      this->_window.updateInputs(this->_input);
	      this->_window.updateClock(this->_clock);
	      glEnable(GL_DEPTH_TEST);
	      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	      this->_camera.bindShader(0);
	      this->_players.draw(this->_camera.getShader(0), -20, 0);
	      this->_window.flush();
	    }
	  this->_nbPlayer = (this->_input.getKey(SDLK_KP_1) ? 1 : 2);
	  this->_nbPerso = _nbPlayer;
	  this->play();
	  value = -1;
	  break;
	case 5:
	  _optionMenu.drawScore(this->_camera.getShader(0), _window, _clock, _input);
	  value = 3;
	  break;
	case 6:
	  this->drawCredit();
	  value = 3;
	  break;
	}
    }
  return (true);
}

void		MyGame::drawCredit()
{
  Text		madeBy;
  Text		forWho;
  Text		perso1;
  Text		perso2;
  std::string	pathImg("./imgs/credit.tga");
  LoadTexture	*backgroud = new LoadTexture(90, 1, 1, 1);

  madeBy.initialize();
  madeBy.putStr("Made By", glm::vec4(1, 1, 0, 1), 3.0f);
  perso1.initialize();
  perso1.putStr("Ovejer_n Bovier_g Limagn_v", glm::vec4(1, 0.5, 0, 1), 2.5f);
  perso2.initialize();
  perso2.putStr("Comte_a De-mat_a", glm::vec4(1, 0.5, 0, 1), 2.5f);
  forWho.initialize();
  forWho.putStr("For Epitech promo 2018", glm::vec4(0, 0, 1, 1), 2.0f);

  backgroud->initialize(27, 42, pathImg);

  if (sound.getStat())
    sound.playMusic(3, -1);

  while (!_input.getKey(SDLK_ESCAPE))
    {
      glEnable(GL_DEPTH_TEST);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      _window.updateInputs(_input);
      _window.updateClock(_clock);
      if (_input.getKey(SDLK_m))
	if (!sound.getStat())
	  sound.playMusic(3, -1);
      backgroud->draw(_camera.getShader(0), _clock);
      madeBy.draw(_camera.getShader(0), -5, 22);
      perso1.draw(_camera.getShader(0), -30, 5);
      perso2.draw(_camera.getShader(0), -15, -5);
      forWho.draw(_camera.getShader(0), -20, -20);
      this->_window.flush();
    }
  delete backgroud;
  if (sound.getStat())
    sound.playMusic(2, -1);
}

int	MyGame::Submenu()
{
  int	value = 1;
  glm::vec3 pos[2];
  glm::vec3 dir[2];

  for (size_t i = 0; i < this->_nbPlayer; ++i)
    {
      pos[i] = this->_camera.getPos(i);
      dir[i] = this->_camera.getDir(i);
    }
  glViewport(0, 0, 1280, 720);
  this->_camera.setPerspective((1280.0 / 720.0), 0);
  this->_camera.setPerspective((1280.0 / 720.0), 1);
  this->_camera.setPosMenu();
  while ((value = this->_subMenu.update(this->_clock, this->_input)) == -1)
    {
      this->_window.updateInputs(this->_input);
      this->_window.updateClock(this->_clock);
      this->_subMenu.draw(this->_camera.getShader(0), this->_clock, this->_window);
    }
  if (value == 1)
    {
      float size;
      size = (_nbPlayer == 1 ? (1280.0f / 720.0f) : ((1280.0f / 2.0f) / 720.0f));
      this->_camera.setPerspective(size, 0);
      this->_camera.setPerspective(size, 1);
      for (size_t i = 0; i < this->_nbPlayer; ++i)
	  {
	  this->_camera.setPos(pos[i], i);
	  this->_camera.setDir(dir[i], i);
	}
    }
  else if (value == 2)
    {
      this->_save.saveGame(_map.getMap(), _perso, _ia, _perso.size(), pos, dir);
      return (0);
    }
  return (value);
}

bool	MyGame::positionCamera(std::string way)
{
  if (way.compare("./.save/game.save"))
    {
      if (!this->loadPlayer())
	return (false);
    }
  else
    {
      if (!this->_map.initializeMap())
	return (false);
      std::string	path("./imgs/loadgame.tga");
      std::ifstream file("./.save/game.save", std::ios::in);
      std::string s;
      int i = 0, j = 0;
      if (file.is_open())
	{
	  while (std::getline(file, s))
	    {
	      if (!s.compare(0, 5, "perso"))
		{
		  setPerso(s, i);
		  i++;
		}
	      else if (!s.compare(0, 2, "ia"))
		{
		  setIa(s, j);
		  j++;
		}
	    }
	  float size;
	  this->_nbPlayer = i;
	  size = (_nbPlayer == 1 ? (1280.0f / 720.0f) : ((1280.0f / 2.0f) / 720.0f));
	  this->_camera.setPerspective(size, 0);
	  this->_camera.setPerspective(size, 1);
	  file.close();
	}
      else
	throw ("File could not read !");
    }
  return (true);
}

void	MyGame::lastMemories()
{
  std::string	pathImg("./imgs/darkness.tga");
  LoadTexture	*backgroud = new LoadTexture(90, 0.1, 0.1, 0.1);;
  Text		end;
  int		id = 0;

  backgroud->translate(glm::vec3(0, 0, 0));
  backgroud->initialize(25, 42, pathImg);
  end.initialize();
  for (int i = 0; i < _perso.size(); i++)
    if (_perso[i]->getId())
      id = _perso[i]->getId();
  glm::vec4 colorT(1, 0.5, 0, 1);
  end.putStr("This is the end " +
	     (id ? "player " + std::to_string(id) : "Bots") +
	     " win", colorT, 2.5);
  if (sound.getStat())
    sound.playMusic(1, -1);
  while (!this->_input.getKey(SDLK_ESCAPE))
    {
      this->_window.updateInputs(this->_input);
      this->_window.updateClock(this->_clock);
      glEnable(GL_DEPTH_TEST);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      this->_camera.bindShader(0);
      backgroud->draw(_camera.getShader(0), this->_clock);
      end.draw(_camera.getShader(0), -30, -9);
      this->_window.flush();
    }
  if (!this->_perso.empty())
    {
      std::vector<int> list;
      int i = 0;
      std::string s;
      std::ifstream inFile("./.score/game.score", std::ios::in);
      if (inFile.is_open())
	{
	  while (std::getline(inFile, s))
	    {
	      if (atoi(s.c_str()) != 0)
		list.push_back(atoi(s.c_str()));
	      s.clear();
	    }
	  list.push_back(this->_perso[0]->getScore());
	  std::sort(list.begin(), list.end(), greater());
	  if (list.size() > 5)
	    list.resize(5);
	  inFile.close();
	}
      std::ofstream outFile("./.score/game.score", std::ios::in);
      if (outFile.is_open())
	{
	  for (int i = 0; i < list.size(); i++)
	    outFile << std::to_string(list[i]) << std::endl;
	  while (!list.empty())
	    list.pop_back();
	  outFile.close();
	}
    }
  delete backgroud;
}

void	MyGame::quitGame()
{
  this->_map.freeMap();
  this->_camera.setPerspective((1280.0 / 720.0), 0);
  this->_camera.setPerspective((1280.0 / 720.0), 1);
  this->_camera.setPosMenu();
  glViewport(0, 0, 1280, 720);
  if (this->_subret == 3)
    lastMemories();
  while (!this->_perso.empty())
    {
      delete this->_perso.back();
      this->_perso.pop_back();
    }
  while (!this->_ia.empty())
    {
      delete this->_ia.back();
      this->_ia.pop_back();
    }
}

bool	MyGame::play(std::string way)
{
  int	value = 1;

  try
    {
      if (this->_playMenu.getStat() == 2)
	{
	  this->_map.setWidth(this->_optionMenu.getSize());
	  this->_map.loadingMap(this->_playMenu.getStat(), std::string(""));
	}
      else
	this->_map.loadingMap(this->_playMenu.getStat(), way);
      if (!positionCamera(way))
	return false;
      this->_map.checkMap(this->_clock, NULL);
      if (_ia.size() > 0)
	{
	  this->_nbIA = _ia.size();
	  _tab = new Thread*[_nbIA];
	  for (int i = 0; i < _ia.size(); i++)
	    _tab[i] = new Thread(&updateIA, this, i);
	}
      if ((value = _subret) == 1)
	{
	  _th = new Thread(&drawAll, this);
	  if (_nbPlayer == 2)
	    _th1 = new Thread(&drawAll1, this);
	  while (value)
	    {
	      if (!sound.getStat() && _musicSate)
		{
		  _nbMusic = (_nbMusic > 8 ? 5 : ++_nbMusic);
		  sound.playMusic(_nbMusic, 1);
		}
	      if (!this->update())
		break;
	      if (this->_subret == 2)
		value = this->Submenu();
	      else if ((value = this->_subret) == 1)
		this->draw();
	      else
		value = this->_subret;
	    }
	  cond_var.notify_one();
	  _th->joinThread();
	  delete _th;
	  if (_nbPlayer == 2)
	    {
	      cond_var1.notify_one();
	      _th1->joinThread();
	      delete _th1;
	    }
	  if (_ia.size() > 0)
	    {
	      cond_upia.notify_all();
	      for (int i = 0; i < _ia.size(); i++)
		{
		  _tab[i]->joinThread();
		  delete _tab[i];
		}
	      delete[] _tab;
	    }
	}
      std::cout << " End of Game\n";
      quitGame();
      _subret = 1;
    }
  catch (const myExcep& e)
    {
      std::cerr << "Error : " << e.what() << std::endl;
    }
  if (sound.getStat())
    sound.playMusic(2, -1);
  return (true);
}

void    *drawAll(void *arg)
{
  reinterpret_cast<MyGame *>(arg)->drawAlll();
  return (NULL);
}

void    *drawAll1(void *arg)
{
  reinterpret_cast<MyGame *>(arg)->drawAlll1();
  return (NULL);
}

void	MyGame::drawAlll()
{
  std::unique_lock<std::mutex> lock(m);

  glXMakeCurrent(display, drawable, context);
  while (this->_subret == 1)
    {
      cond_var.wait(lock);
      this->_camera.bindShader(0);
      if (this->_nbPlayer > 1)
	glViewport(1280 / 2 + 2, 0, 1280 / 2 - 2, 720);
      if (this->_nbPerso > 0)
	this->_map.draw(this->_camera.getShader(0), this->_clock, -(std::floor(_perso[0]->getPosX())),
			-(std::floor(_perso[0]->getPosZ())));
      for (size_t i = 0; i < this->_perso.size(); ++i)
	if (this->_perso[i]->getId())
	  this->_perso[i]->draw(this->_camera.getShader(0), this->_clock);
      for (size_t i = 0; i < this->_nbIA; ++i)
	if (this->_ia[i]->getId() != -1)
	  this->_ia[i]->draw(this->_camera.getShader(0), this->_clock);
      cond_var.notify_one();
    }
  lock.unlock();
  pthread_exit(NULL);
}

void	MyGame::drawAlll1()
{
  std::unique_lock<std::mutex> lock(m1);

  glXMakeCurrent(display, drawable, context);
  while (this->_subret == 1)
    {
      cond_var1.wait(lock);
      glViewport(0, 0, 1280 / 2, 720);
      this->_camera.bindShader(1);
      if (this->_nbPerso > 0)
	this->_map.draw(this->_camera.getShader(1), this->_clock, -(std::floor(_perso[1]->getPosX())),
			-(std::floor(_perso[1]->getPosZ())));
      for (size_t i = 0; i < this->_perso.size(); ++i)
	if (this->_perso[i]->getId())
	  this->_perso[i]->draw(this->_camera.getShader(1), this->_clock);
      for (size_t i = 0; i < this->_nbIA; ++i)
	if (this->_ia[i]->getId() != -1)
	  this->_ia[i]->draw(this->_camera.getShader(1), this->_clock);
      cond_var1.notify_one();
    }
  lock.unlock();
  pthread_exit(NULL);
}

void	MyGame::draw()
{
  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  std::unique_lock<std::mutex> lock1(m1);
  if (this->_nbPlayer == 2)
    cond_var1.notify_one();
  std::unique_lock<std::mutex> lock(m);
  cond_var.notify_one();
  cond_var.wait(lock);
  if (this->_nbPlayer == 2)
    cond_var1.wait(lock1);
  this->_window.flush();
}

bool	MyGame::checkTouch()
{
  if (this->_input.getKey(SDLK_m, true))
    {
      if (sound.getStat())
	{
	  sound.stopMusic();
	  _musicSate = false;
	}
      else
	{
	  _nbMusic = (_nbMusic > 8 ? 5 : ++_nbMusic);
	  sound.playMusic(_nbMusic, 1);
	  _musicSate = true;
	}
    }
  if (this->_input.getKey(SDLK_ESCAPE) || this->_input.getInput(SDL_QUIT))
    {
      this->_subret = 0;
      return (false);
    }
  else if (this->_input.getKey(SDLK_p))
    {
      this->_subret = 2;
      return (true);
    }
  this->_subret = 1;
  return (true);
}

void    *updateIA(MyGame *func, int i)
{
  func->updateIAa(i);
  return (NULL);
}

void	MyGame::updateIAa(int i)
{
  int	id = i;
  std::unique_lock<std::mutex> lock(upia);

  while (this->_subret == 1)
    {
      cond_upia.wait(lock);
      if (id != -1 && this->_ia[id]->update(_clock, _input, this->_camera, this->_map) == false)
	{
	  upia1.lock();
	  this->_nbIA--;
	  upia1.unlock();
	  this->_ia[id]->setId(-1);
	  id = -1;
	}
      upia1.lock();
      nb--;
      if (nb < 0)
	nb = 0;
      upia1.unlock();
      cond_upia1.notify_one();
    }
  lock.unlock();
  pthread_exit(NULL);
}

bool	MyGame::update()
{
  nb = _ia.size();
  this->_window.updateInputs(this->_input);
  this->_window.updateClock(this->_clock);
  std::unique_lock<std::mutex> lock(upia1);
  cond_upia.notify_all();
  cond_upia1.wait(lock, [](){return nb <= 0;});
  if (!this->checkTouch())
    return (false);
  _map.update(this->_clock, this->_input);
  for (size_t i = 0; i < this->_perso.size(); ++i)
    if (this->_perso[i]->getId())
      {
	if (this->_perso[i]->update(_clock, _input, this->_camera, this->_map) == false)
	  {
	    this->_perso[i]->setId(0);
	    this->_nbPerso--;
	  }
      }
    else
      this->_perso[i]->update(_clock, _input, _camera, i);
  if ((this->_nbPerso == 1 && this->_nbIA <= 0) ||
      (this->_nbPerso == 0 && this->_nbIA > 0) ||
      (this->_nbPerso == 0 && this->_nbIA == 0))
    {
      this->_subret = 3;
      return (false);
    }
  return (true);
}

void	MyGame::drawLoad(LoadTexture *img, int size)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  this->_camera.bindShader(0);
  img->translate(glm::vec3(0, -size, 0));
  img->draw(this->_camera.getShader(0), this->_clock);
  this->_window.flush();
}

bool	MyGame::loadPlayer()
{
  if (sound.getStat())
    sound.playMusic(4, 1);
  std::string	path("./imgs/loadgame.tga");
  int		k = 0;
  glm::vec3	*spawn;
  spawn = _map.spawnPlayer(_nbPlayer + _optionMenu.getBots());

  LoadTexture	*img = new LoadTexture(90, 1, 1, 1);
  if (!img->initialize(25, 42, path))
    return (false);
  img->translate(glm::vec3(0, 50, 0));
  this->drawLoad(img);

  IPerso *perso[this->_nbPlayer];
  int j = 0;
  for (j; j < this->_nbPlayer; j++)
    {
      perso[j] = new Marvin(spawn[k], j + 1);
      if (!perso[j]->initialize())
	return (false);
      this->_perso.push_back(perso[j]);
      k++;
    }
  this->drawLoad(img);
  if (!this->_map.initializeMap())
    return (false);
  this->drawLoad(img);
  int nbBot = this->_optionMenu.getBots();
  IA *ia[nbBot];
  for (int i = 0; i < nbBot; i++)
    {
      ia[i] = new IA(spawn[k], j + i + 2);
      if (!ia[i]->initialize())
	return (false);
      this->_ia.push_back(ia[i]);
      k++;
    }
  this->drawLoad(img);

  if (this->_nbPlayer == 2)
    {
      this->_camera.setPerspective((1280.0 / 2.0) / 720.0, 0);
      this->_camera.setPerspective((1280.0 / 2.0) / 720.0, 1);
    }
  int pos = 0;
  for(std::vector<IPerso *>::iterator i = _perso.begin(); i != _perso.end(); ++i)
    {
      this->_camera.setPos((*i)->getPosPlayer(), pos);
      this->_camera.setDir((*i)->getDirPlayer(), pos);
      pos++;
    }
  if (sound.getStat())
    sound.playMusic(_nbMusic, 1);
  return (true);
}

void	MyGame::setPerso(std::string s, int i)
{
  std::string value;
  std::string type;
  std::istringstream iss(s.c_str());

  std::getline(iss, type, ' ');
  std::getline(iss, value, ' ');
  if (!type.compare(0, 5, "perso"))
    {
      IPerso *perso = new Marvin(atoi(value.c_str()));
      perso->initialize();
      this->_perso.push_back(perso);
    }
  std::getline(iss, value, ' ');
  double x = strtod(value.c_str(), NULL);
  std::getline(iss, value, ' ');
  double y = strtod(value.c_str(), NULL);
  std::getline(iss, value, ' ');
  double z = strtod(value.c_str(), NULL);
  this->_camera.setPos(glm::vec3(x, y, z), i);
  std::getline(iss, value, ' ');
  x = strtod(value.c_str(), NULL);
  std::getline(iss, value, ' ');
  y = strtod(value.c_str(), NULL);
  std::getline(iss, value, ' ');
  z = strtod(value.c_str(), NULL);
  this->_camera.setDir(glm::vec3(x, y, z), i);
  std::getline(iss, value, ' ');
  x = strtod(value.c_str(), NULL);
  std::getline(iss, value, ' ');
  y = strtod(value.c_str(), NULL);
  std::getline(iss, value, ' ');
  z = strtod(value.c_str(), NULL);
  this->_perso[i]->setPos(glm::vec3(x, y, z));
  std::getline(iss, value, ' ');
  this->_perso[i]->modifLife(strtod(value.c_str(), NULL));
  std::getline(iss, value, ' ');
  this->_perso[i]->modifSpeed(strtod(value.c_str(), NULL));
  std::getline(iss, value, ' ');
  this->_perso[i]->modifBomb(strtod(value.c_str(), NULL));
  std::getline(iss, value, ' ');
  this->_perso[i]->modifRange(strtod(value.c_str(), NULL));
  std::getline(iss, value, ' ');
  this->_perso[i]->setScore(strtod(value.c_str(), NULL));
}

void	MyGame::setIa(std::string s, int i)
{
  std::string value;
  std::string type;
  std::istringstream iss(s.c_str());

  std::getline(iss, type, ' ');
  std::getline(iss, value, ' ');
  if (!type.compare(0, 2, "ia"))
    {
      IA *ia;
      ia = new IA(atoi(value.c_str()));
      this->_ia.push_back(ia);
    }
  std::getline(iss, value, ' ');
  int x = strtod(value.c_str(), NULL);
  std::getline(iss, value, ' ');
  int y = strtod(value.c_str(), NULL);
  std::getline(iss, value, ' ');
  int z = strtod(value.c_str(), NULL);
  this->_ia[i]->setPos(glm::vec3(x, y, z));
  std::getline(iss, value, ' ');
  this->_ia[i]->modifLife(strtod(value.c_str(), NULL));
  std::getline(iss, value, ' ');
  this->_ia[i]->modifSpeed(strtod(value.c_str(), NULL));
  std::getline(iss, value, ' ');
  this->_ia[i]->modifBomb(strtod(value.c_str(), NULL));
  std::getline(iss, value, ' ');
  this->_ia[i]->modifRange(strtod(value.c_str(), NULL));
  std::getline(iss, value, ' ');
  this->_ia[i]->setScore(strtod(value.c_str(), NULL));
}


void	MyGame::intro()
{
  this->_intro.initialize();
  this->_window.updateInputs(this->_input);
  this->_window.updateClock(this->_clock);
  while (this->_intro.update(this->_clock, this->_input))
    {
      this->_window.updateInputs(this->_input);
      this->_window.updateClock(this->_clock);
      this->_intro.draw(this->_camera.getShader(0), this->_clock, this->_window);
    }
}

int	MyGame::playMenu()
{
  int	value;

  this->_window.updateInputs(this->_input);
  this->_window.updateClock(this->_clock);
  while ((value = this->_playMenu.update(this->_clock, this->_input)) == 0)
    {
      this->_window.updateInputs(this->_input);
      this->_window.updateClock(this->_clock);
      this->_playMenu.draw(this->_camera.getShader(0), this->_clock, this->_window);
    }
  return (value);
}

int	MyGame::menu()
{
  int	value;

  this->_window.updateInputs(this->_input);
  this->_window.updateClock(this->_clock);
  while ((value = this->_menu.update(this->_clock, this->_input)) == 0)
    {
      this->_window.updateInputs(this->_input);
      this->_window.updateClock(this->_clock);
      this->_menu.draw(this->_camera.getShader(0), this->_clock, this->_window);
    }
  return (value);
}

int	MyGame::option()
{
  int	value;

  this->_window.updateInputs(this->_input);
  this->_window.updateClock(this->_clock);
  while ((value = this->_optionMenu.update(this->_clock, this->_input)) == 1)
    {
      this->_window.updateInputs(this->_input);
      this->_window.updateClock(this->_clock);
      this->_optionMenu.draw(this->_camera.getShader(0), this->_clock, this->_window);
    }
  return (value);
}
