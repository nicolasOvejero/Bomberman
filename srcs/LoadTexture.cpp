#include <iostream>
#include "LoadTexture.hpp"

LoadTexture::LoadTexture(int angle, float sx, float sy, float sz)
{
  this->_rotation.z = -angle;
  this->_scale.x = sx;
  this->_scale.y = sy;
  this->_scale.z = sz;
  this->stat = false;
}

bool		LoadTexture::initialize(float x, float y, std::string const path)
{
  if (_texture.load(path) == false)
    {
      std::cerr << "Cannot load the texture" << std::endl;
      return (false);
    }
  this->_geometry.pushVertex(glm::vec3(-x, y, 0));
  this->_geometry.pushVertex(glm::vec3(-x, -y, 0));
  this->_geometry.pushVertex(glm::vec3(x, -y, 0));
  this->_geometry.pushVertex(glm::vec3(x, y, 0));
  this->_geometry.pushUv(glm::vec2(0.0f, 1.0f));
  this->_geometry.pushUv(glm::vec2(1.0f, 1.0f));
  this->_geometry.pushUv(glm::vec2(1.0f, 0.0f));
  this->_geometry.pushUv(glm::vec2(0.0f, 0.0f));
  this->_geometry.build();
  return (true);
}

void		LoadTexture::draw(gdl::AShader &shader,
				  __attribute__((unused))gdl::Clock const &clock)
{
  this->stat = true;
  if (this->_scale.x < 1 && this->_scale.y < 1 && this->_scale.z < 1)
    {
      this->_scale.x += 0.01;
      this->_scale.y += 0.01;
      this->_scale.z += 0.01;
      this->stat = false;
    }
  glDisable(GL_DEPTH_TEST);
  glAlphaFunc(GL_GREATER, 0.1f);
  glEnable(GL_ALPHA_TEST);
  this->_texture.bind();
  this->_geometry.draw(shader, getTransformation(), GL_QUADS);
  glEnable(GL_DEPTH_TEST);
}

glm::vec3	LoadTexture::getPosition() const
{
  return (this->_position);
}
