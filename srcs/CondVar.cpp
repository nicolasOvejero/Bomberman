//
// CondVar.cpp for  in /home/lelabo_m
//
// Made by Marc Le Labourier
// Login   <lelabo_m@epitech.net>
//
// Started on  Wed May 28 16:45:32 2014 Marc Le Labourier
// Last update Wed May 28 18:52:30 2014 Marc Le Labourier
//

#include "CondVar.hh"

CondVar::CondVar(Mutex *m) : _mutex(m)
{
  _cond = new pthread_cond_t;
  pthread_cond_init(_cond, 0);
  _islock = false;
}

CondVar::~CondVar(void)
{
  delete _cond;
}

void	CondVar::wait(void)
{
  _islock = true;
  pthread_cond_wait(_cond, _mutex->getMutex());
  _islock = false;
}

void	CondVar::signal(void)
{
  pthread_cond_signal(_cond);
}

void	CondVar::broadcast(void)
{
  pthread_cond_broadcast(_cond);
}
