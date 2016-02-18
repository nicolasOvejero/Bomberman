#include "Sound.hpp"

Sound	sound;

Sound::Sound()
{
  setenv("SDL_AUDIODRIVER", "alsa", 1);
  this->_volume = MIX_MAX_VOLUME;
}

Sound::~Sound()
{
  Mix_FreeMusic(this->_music[0]);
  Mix_FreeMusic(this->_music[1]);
  Mix_FreeMusic(this->_music[2]);
  Mix_FreeMusic(this->_music[3]);
  Mix_FreeMusic(this->_music[4]);
  Mix_FreeMusic(this->_music[5]);
  Mix_FreeMusic(this->_music[6]);
  Mix_FreeMusic(this->_music[7]);
  Mix_FreeMusic(this->_music[8]);
  Mix_CloseAudio();
}

bool	Sound::initilize()
{
  if(Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048) == -1)
    {
      std::cerr << Mix_GetError() << std::endl;
      return (false);
    }
  if (!(this->_music[0] = Mix_LoadMUS("./sound/music_intro.flac")))
    {
      std::cerr << "Error : " << Mix_GetError() << std::endl;
      return (false);
    }
  if (!(this->_music[1] = Mix_LoadMUS("./sound/loose.flac")))
    {
      std::cerr << "Error : " << Mix_GetError() << std::endl;
      return (false);
    }
  if (!(this->_music[2] = Mix_LoadMUS("./sound/music_menu.flac")))
    {
      std::cerr << "Error : " << Mix_GetError() << std::endl;
      return (false);
    }
  if (!(this->_music[3] = Mix_LoadMUS("./sound/credit.flac")))
    {
      std::cerr << "Error : " << Mix_GetError() << std::endl;
      return (false);
    }
  if (!(this->_music[4] = Mix_LoadMUS("./sound/lightcycle.flac")))
    {
      std::cerr << "Error : " << Mix_GetError() << std::endl;
      return (false);
    }
  if (!(this->_music[5] = Mix_LoadMUS("./sound/music_01.flac")))
    {
      std::cerr << "Error : " << Mix_GetError() << std::endl;
      return (false);
    }
  if (!(this->_music[6] = Mix_LoadMUS("./sound/music_02.flac")))
    {
      std::cerr << "Error : " << Mix_GetError() << std::endl;
      return (false);
    }
  if (!(this->_music[7] = Mix_LoadMUS("./sound/music_03.flac")))
    {
      std::cerr << "Error : " << Mix_GetError() << std::endl;
      return (false);
    }
  if (!(this->_music[8] = Mix_LoadMUS("./sound/music_04.flac")))
    {
      std::cerr << "Error : " << Mix_GetError() << std::endl;
      return (false);
    }
  return (true);
}

void	Sound::playMusic(int music, int nb)
{
  Mix_PlayMusic(this->_music[music], nb);
  Mix_VolumeMusic(this->_volume);
}

void	Sound::pauseMusic() const
{
  Mix_PauseMusic();
}

void	Sound::resumeMusic() const
{
  Mix_ResumeMusic();
}

void	Sound::stopMusic() const
{
  Mix_HaltMusic();
}

bool	Sound::getStat() const
{
  return (Mix_PlayingMusic());
}
