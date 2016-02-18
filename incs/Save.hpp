#ifndef __SAVE_HPP__
# define __SAVE_HPP__

# include <iostream>
# include <vector>
# include "IA.hpp"
# include "IPerso.hpp"
# include "Map.hpp"
# include "Camera.hpp"

class Save
{
public:
  Save();
  ~Save();

  void	saveGame(char **, std::vector<IPerso *> &, std::vector<IA *> &, int,
		 glm::vec3 *, glm::vec3 *);

private:
};

#endif
