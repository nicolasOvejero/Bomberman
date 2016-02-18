#ifndef __CAMERA_HPP__
# define __CAMERA_HPP__

# include <Game.hh>
# include <Clock.hh>
# include <Input.hh>
# include <SdlContext.hh>
# include <Geometry.hh>
# include <Texture.hh>
# include <BasicShader.hh>
# include <Model.hh>
# include <OpenGL.hh>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <Model.hh>
# include <iostream>

class Camera
{
public:
  Camera()
  {
    this->_pos[0] = glm::vec3(0.0f, 0.0f, -40.0f);
    this->_dir[0] = glm::vec3(0.0f, 0.0f, 0.0f);
    this->_tr[0] = glm::vec3(0, 0, 0);
    this->_pos[1] = glm::vec3(0.0f, 0.0f, -40.0f);
    this->_dir[1] = glm::vec3(0.0f, 0.0f, 0.0f);
    this->_tr[1] = glm::vec3(0, 0, 0);
  }
  ~Camera() {}

  bool			initialize();
  void			setPosPlay(int, int);
  void			setPosMenu();
  gdl::AShader		&getShader(int pos) { return this->_shader[pos]; }
  void			bindShader(int pos) { this->_shader[pos].bind(); }
  void			setPerspective(float const size, int pos) {
    this->_projection[pos] = glm::perspective(60.0f, size, 0.1f, 1000.0f);
    update(pos);
  }

  void			moveCam(glm::vec3, int);
  glm::vec3		getDir(int position) const { return (_dir[position]); }
  glm::vec3		getPos(int position) const { return (_pos[position]); }
  void			setDir(glm::vec3 const dir, int const position) { _dir[position] = dir; update(position); }
  void			setPos(glm::vec3 const pos, int const position) { _pos[position] = pos; update(position); }

private:
  void			update(int);

private:
  gdl::BasicShader	_shader[2];
  glm::mat4		_transformation[2];
  glm::mat4		_projection[2];
  glm::vec3		_position[2];
  glm::vec3		_pos[2];
  glm::vec3		_dir[2];
  glm::vec3		_tr[2];
};

#endif
