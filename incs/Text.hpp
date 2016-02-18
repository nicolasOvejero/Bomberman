#ifndef __TEXT_HPP__
# define __TEXT_HPP__

# include <iostream>
# include <vector>
# include "AObject.hpp"

class Text
{
public:
  Text();
  ~Text();

  bool		initialize();
  void		putChar(char, glm::vec4);
  void		draw(gdl::AShader &, int, int);
  void		draw(gdl::AShader &, int, int, glm::vec3, float);
  void		putStr(std::string, glm::vec4, float);
  void		changeStr(std::string, float, glm::vec4);

private:
  int				getColumn(const char);
  std::vector<gdl::Geometry *>	_chaine;
  char				_firstChar;
  gdl::Texture			_texture;
  float				_size;
};

#endif
