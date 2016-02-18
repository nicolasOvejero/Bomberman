#ifndef __SOUND_HPP__
# define __SOUND_HPP__

# include <iostream>
# include <map>
# include "SDL_mixer.h"

class Sound
{
public:
  Sound();
  ~Sound();

  bool	initilize();
  void	playMusic(int, int);
  void  pauseMusic() const;
  void  resumeMusic() const;
  void  stopMusic() const;
  bool  getStat() const;

private:
  std::map<int, Mix_Music *>	_music;
  int				_volume;
};

#endif
