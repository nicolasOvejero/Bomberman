#include "Cube.hpp"

Cube::Cube(gdl::Texture &texture)
  : _texture(texture)
{
  this->scale(glm::vec3(0.5, 0.5, 0.5));
}

bool	Cube::initialize(char const value)
{
  this->_value = value;

  this->_geometry.setColor(glm::vec4(1, 1, 1, 1));
  this->_geometry.pushVertex(glm::vec3(1, -1, 1));
  this->_geometry.pushVertex(glm::vec3(1, 1, 1));
  this->_geometry.pushVertex(glm::vec3(-1, 1, 1));
  this->_geometry.pushVertex(glm::vec3(-1, -1, 1));
  this->_geometry.pushUv(glm::vec2(0.0f, 0.0f));
  this->_geometry.pushUv(glm::vec2(1.0f, 0.0f));
  this->_geometry.pushUv(glm::vec2(1.0f, 1.0f));
  this->_geometry.pushUv(glm::vec2(0.0f, 1.0f));

  this->_geometry.setColor(glm::vec4(1, 1, 1, 1));
  this->_geometry.pushVertex(glm::vec3(1, -1, -1));
  this->_geometry.pushVertex(glm::vec3(1, 1, -1));
  this->_geometry.pushVertex(glm::vec3(-1, 1, -1));
  this->_geometry.pushVertex(glm::vec3(-1, -1, -1));
  this->_geometry.pushUv(glm::vec2(0.0f, 0.0f));
  this->_geometry.pushUv(glm::vec2(1.0f, 0.0f));
  this->_geometry.pushUv(glm::vec2(1.0f, 1.0f));
  this->_geometry.pushUv(glm::vec2(0.0f, 1.0f));

  this->_geometry.setColor(glm::vec4(1, 1, 1, 1));
  this->_geometry.pushVertex(glm::vec3(1, -1, -1));
  this->_geometry.pushVertex(glm::vec3(1, 1, -1));
  this->_geometry.pushVertex(glm::vec3(1, 1, 1));
  this->_geometry.pushVertex(glm::vec3(1, -1, 1));
  this->_geometry.pushUv(glm::vec2(0.0f, 0.0f));
  this->_geometry.pushUv(glm::vec2(1.0f, 0.0f));
  this->_geometry.pushUv(glm::vec2(1.0f, 1.0f));
  this->_geometry.pushUv(glm::vec2(0.0f, 1.0f));

  this->_geometry.setColor(glm::vec4(1, 1, 1, 1));
  this->_geometry.pushVertex(glm::vec3(-1, -1, 1));
  this->_geometry.pushVertex(glm::vec3(-1, 1, 1));
  this->_geometry.pushVertex(glm::vec3(-1, 1, -1));
  this->_geometry.pushVertex(glm::vec3(-1, -1, -1));
  this->_geometry.pushUv(glm::vec2(0.0f, 0.0f));
  this->_geometry.pushUv(glm::vec2(1.0f, 0.0f));
  this->_geometry.pushUv(glm::vec2(1.0f, 1.0f));
  this->_geometry.pushUv(glm::vec2(0.0f, 1.0f));

  this->_geometry.setColor(glm::vec4(1, 1, 1, 1));
  this->_geometry.pushVertex(glm::vec3(1, 1, 1));
  this->_geometry.pushVertex(glm::vec3(1, 1, -1));
  this->_geometry.pushVertex(glm::vec3(-1, 1, -1));
  this->_geometry.pushVertex(glm::vec3(-1, 1, 1));
  this->_geometry.pushUv(glm::vec2(0.0f, 0.0f));
  this->_geometry.pushUv(glm::vec2(1.0f, 0.0f));
  this->_geometry.pushUv(glm::vec2(1.0f, 1.0f));
  this->_geometry.pushUv(glm::vec2(0.0f, 1.0f));

  this->_geometry.setColor(glm::vec4(1, 1, 1, 1));
  this->_geometry.pushVertex(glm::vec3(1, -1, -1));
  this->_geometry.pushVertex(glm::vec3(1, -1, 1));
  this->_geometry.pushVertex(glm::vec3(-1, -1, 1));
  this->_geometry.pushVertex(glm::vec3(-1, -1, -1));
  this->_geometry.pushUv(glm::vec2(0.0f, 0.0f));
  this->_geometry.pushUv(glm::vec2(1.0f, 0.0f));
  this->_geometry.pushUv(glm::vec2(1.0f, 1.0f));
  this->_geometry.pushUv(glm::vec2(0.0f, 1.0f));

  this->_geometry.build();
  return (true);
}

void	Cube::draw(gdl::AShader &shader,
		   __attribute__((unused))gdl::Clock const &clock)
{
  this->_texture.bind();
  this->_geometry.draw(shader, getTransformation(), GL_QUADS);
}
