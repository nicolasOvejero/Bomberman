#ifndef __THREAD_HPP_
# define __THREAD_HPP_

# include <pthread.h>
# include <functional>

class Thread
{
public:
  template<typename T, typename... Args>
  Thread(T &&func, Args &&... param);
  Thread();
  ~Thread();

  void			joinThread() const;

private:
  pthread_t		_thread;
};

void	*function(std::function<void()> *);

template<typename T, typename... Args>
Thread::Thread(T &&func, Args &&... param)
{
  pthread_create(&_thread, NULL, (void* (*)(void*))&function,
		 new std::function<void()>(std::bind(func, param...)));
}

#endif
