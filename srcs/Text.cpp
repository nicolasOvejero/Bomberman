#include "Text.hpp"

Text::Text()
{
  this->_size = 4.0f;
  this->_firstChar = 0;
}

Text::~Text()
{
  while (!this->_chaine.empty())
    {
      delete this->_chaine.back();
      this->_chaine.pop_back();
    }
}

bool			Text::initialize()
{
  if (this->_texture.load("./imgs/font/blue.tga") == false)
    {
      std::cerr << "Cannot load the texture blue.tag" << std::endl;
      return (false);
    }
  return (false);
}

int			Text::getColumn(const char c)
{
  int			ret;

  ret = 0;
  (c == '.' || c == '-') ? (this->_firstChar = ' ', ret = 16) : 0;
  (c >= '0' && c <= '?') ? (this->_firstChar = '0', ret = 15) : 0;
  (c >= '@' && c <= 'O') ? (this->_firstChar = '@', ret = 14) : 0;
  (c >= 'P' && c <= '\\') ? (this->_firstChar = 'P', ret = 13) : 0;
  return (ret);
}

void			Text::putChar(char c, glm::vec4 color)
{
  gdl::Geometry		*geometry = new gdl::Geometry();
  int			pos;

  c -= (c >= 'a' && c <= 'z') ? 32 : 0;
  pos = getColumn(c);
  geometry->setColor(color);
  geometry->pushVertex(glm::vec3(0, 0, 0));
  geometry->pushVertex(glm::vec3(-this->_size, 0, 0));
  geometry->pushVertex(glm::vec3(-this->_size, -this->_size, 0));
  geometry->pushVertex(glm::vec3(0, -this->_size, 0));
  geometry->pushUv(glm::vec2((c - this->_firstChar) / 16.0f, pos / 16.0f));
  geometry->pushUv(glm::vec2((c - this->_firstChar + 1) / 16.0f, pos / 16.0f));
  geometry->pushUv(glm::vec2((c - this->_firstChar + 1) / 16.0f, (pos - 1) / 16.0f));
  geometry->pushUv(glm::vec2((c - this->_firstChar) / 16.0f, (pos - 1) / 16.0f));
  geometry->build();
  this->_chaine.push_back(geometry);
}

void			Text::putStr(std::string str, glm::vec4 color, float size)
{
  unsigned int		i = 0;

  this->_size = size;
  while (i < str.length())
    {
      putChar(str.at(i), color);
      i++;
    }
}

void			Text::changeStr(std::string newStr, float newSize, glm::vec4 newColor)
{
  while (!this->_chaine.empty())
    {
      delete this->_chaine.back();
      this->_chaine.pop_back();
    }
  this->putStr(newStr, newColor, newSize);
}

void			Text::draw(gdl::AShader &shader, int col, int lin, glm::vec3 rot, float angle)
{
  glm::mat4		transformation;

  this->_texture.bind();
  std::vector<gdl::Geometry *>::reverse_iterator rit = this->_chaine.rbegin();
  for (; rit != this->_chaine.rend(); rit++)
    {
      glAlphaFunc(GL_GREATER, 0.1f);
      glEnable(GL_ALPHA_TEST);
      transformation = glm::translate(transformation, glm::vec3(col, lin, 0));
      transformation = glm::rotate(transformation, angle, rot);
      (*rit)->draw(shader, transformation, GL_QUADS);
      col += this->_size;
    }
}

void			Text::draw(gdl::AShader &shader, int col, int lin)
{
  glm::mat4		transformation;

  this->_texture.bind();
  std::vector<gdl::Geometry *>::reverse_iterator rit = this->_chaine.rbegin();
  for (; rit != this->_chaine.rend(); rit++)
    {
      glAlphaFunc(GL_GREATER, 0.1f);
      glEnable(GL_ALPHA_TEST);
      transformation = glm::translate(glm::mat4(1), glm::vec3(col, lin, 0));
      (*rit)->draw(shader, transformation, GL_QUADS);
      col += this->_size;
    }
}
