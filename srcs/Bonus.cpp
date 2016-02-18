#include "Bonus.hpp"

Bonus::Bonus(gdl::Texture &texture, int x, int y)
  : _texture(texture)
{
  this->_transformation = glm::scale(this->_transformation, glm::vec3(0.5, 0.5, 0.5));
  this->_transformation = glm::translate(this->_transformation, glm::vec3(-y * 2, 0, -x * 2 + 1));
  this->_transformation = glm::rotate(this->_transformation, -90.0f, glm::vec3(0, 0, 1));
}

bool    Bonus::initialize(char const value)
{
  this->_value = value;

  this->_geometry.setColor(glm::vec4(1, 1, 1, 1));
  this->_geometry.pushVertex(glm::vec3(1, -1, -1));
  this->_geometry.pushVertex(glm::vec3(1, 1, -1));
  this->_geometry.pushVertex(glm::vec3(-1, 1, -1));
  this->_geometry.pushVertex(glm::vec3(-1, -1, -1));
  this->_geometry.pushUv(glm::vec2(0.0f, 0.0f));
  this->_geometry.pushUv(glm::vec2(1.0f, 0.0f));
  this->_geometry.pushUv(glm::vec2(1.0f, 1.0f));
  this->_geometry.pushUv(glm::vec2(0.0f, 1.0f));

  this->_geometry.build();
  return (true);
}

void	Bonus::draw(gdl::AShader &shader,
		   __attribute__((unused))gdl::Clock const &clock)
{
  this->_texture.bind();
  this->_transformation = glm::rotate(this->_transformation, 1.0f, glm::vec3(0, 0, 1));
  this->_geometry.draw(shader, _transformation, GL_QUADS);
}
