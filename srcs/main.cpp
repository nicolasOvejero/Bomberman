#include "Game.hpp"

int main()
{
  MyGame	game;

  if (!game.initialize())
    return (-1);
  while (game.update())
    game.draw();
  return 0;
}
