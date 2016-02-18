#include "Thread.hpp"

Thread::~Thread()
{
  pthread_cancel(_thread);
}

void	*function(std::function<void()> *func)
{
  (*func)();
  delete func;
  pthread_exit(NULL);
}

void	Thread::joinThread() const
{
  pthread_join(_thread, NULL);
}
