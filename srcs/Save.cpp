#include <iostream>
#include "Save.hpp"

Save::Save()
{
}

Save::~Save()
{
}

void			Save::saveGame(char **map, std::vector<IPerso *> &perso,
				       std::vector<IA *> &ia, int nb, glm::vec3 *pos, glm::vec3 *dir)
{
  std::ofstream		file("./.save/game.save", std::ios::in | std::ios::trunc);

  if (file)
    {
      int i = -1;
      while (map[++i])
	{
	  char *toto = map[i];
	  while (*toto != 0)
	    {
	      if (*toto == '4' || *toto == '3' || *toto == 'a' || *toto == 'b' || *toto == 'c')
		*toto = '0';
	      toto++;
	    }

	  file << map[i] << "\n";
	}
      i = -1;
      while (++i < nb)
	{
	  file << "perso: " << perso[i]->getId() << " "
	       << pos[i].x << " " << pos[i].y << " " << pos[i].z << " "
	       << dir[i].x << " " << dir[i].y << " " << dir[i].z << " "
	       << perso[i]->getPosX() << " " << perso[i]->getPosY() << " " << perso[i]->getPosZ() << " "
	       << perso[i]->getLife() << " " << perso[i]->getSpeed() << " " << perso[i]->getBomb() << " "
	       << perso[i]->getRange() << " " << perso[i]->getScore() << "\n";
	}
      for (int i = 0; i < ia.size(); i++)
	{
	  file << "ia: " << ia[i]->getId() << " "
	       << ia[i]->getPosX() << " " << ia[i]->getPosY() << " "
	       << ia[i]->getPosZ() << " " << ia[i]->getLife() << " "
	       << ia[i]->getSpeed() << " " << ia[i]->getBomb() << " "
	       << ia[i]->getRange() << " " << ia[i]->getScore() << "\n";
	}
      file.close();
    }
}
