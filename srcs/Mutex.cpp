#include "Mutex.hh"

Mutex::Mutex(void)
{
  this->_mutex = new pthread_mutex_t;
  pthread_mutex_init(this->_mutex, 0);
}

Mutex::~Mutex(void)
{
  if (this->_mutex)
    delete this->_mutex;
}

void			Mutex::lock(void)
{
  if (this->_mutex)
    pthread_mutex_lock(this->_mutex);
}

void			Mutex::unlock(void)
{
  if (this->_mutex)
    pthread_mutex_unlock(this->_mutex);
}

bool			Mutex::trylock(void)
{
  if (!pthread_mutex_trylock(this->_mutex))
    return true;
  return (false);
}

pthread_mutex_t		*Mutex::getMutex(void) const
{
  return this->_mutex;
}
