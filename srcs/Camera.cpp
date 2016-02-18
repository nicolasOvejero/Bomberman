#include "Camera.hpp"

void		Camera::update(int pos)
{
  this->_transformation[pos] = glm::lookAt(this->_pos[pos], this->_dir[pos], glm::vec3(0, 1, 0));
  this->_shader[pos].bind();
  this->_shader[pos].setUniform("view", this->_transformation[pos]);
  this->_shader[pos].setUniform("projection", this->_projection[pos]);
}

bool		Camera::initialize()
{
  glEnable(GL_DEPTH_TEST);
  if (!this->_shader[0].load("./shaders/basic.fp", GL_FRAGMENT_SHADER)
      || !this->_shader[0].load("./shaders/basic.vp", GL_VERTEX_SHADER)
      || !this->_shader[0].build())
    {
      std::cerr << "Error : can't load basic.fp or basic.vp" << std::endl;
      return (false);
    }
  this->_projection[0] = glm::perspective(60.0f, 1280.0f / 720.0f, 0.1f, 1000.0f);
  this->update(0);

  if (!this->_shader[1].load("./shaders/basic.fp", GL_FRAGMENT_SHADER)
      || !this->_shader[1].load("./shaders/basic.vp", GL_VERTEX_SHADER)
      || !this->_shader[1].build())
    {
      std::cerr << "Error : can't load basic.fp or basic.vp" << std::endl;
      return (false);
    }
  this->_projection[1] = glm::perspective(60.0f, 1280.0f / 720.0f, 0.1f, 1000.0f);
  this->update(1);
  return (true);
}

void		Camera::setPosPlay(int max, int position)
{
  max = (max > 20 ? 20 : max);
  this->_pos[position] = glm::vec3(-(max / 7), max / 2.5, -(max / 5));
  this->_dir[position] = glm::vec3(-(max / 7), 0, 0);
  this->update(position);
}

void		Camera::moveCam(glm::vec3 const pos, int position)
{
  this->_pos[position] += pos;
  this->_dir[position] += pos;
  this->update(position);
}

void		Camera::setPosMenu()
{
  this->_pos[0] = glm::vec3(0.0f, 0.0f, -40.0f);
  this->_dir[0] = glm::vec3(0.0f, 0.0f, 0.0f);
  this->update(0);
  this->_pos[1] = glm::vec3(0.0f, 0.0f, -40.0f);
  this->_dir[1] = glm::vec3(0.0f, 0.0f, 0.0f);
  this->update(1);
}
