#include "CRobes/Solids.hpp"

void crb::Solids::Solid::render(const crb::Graphics::Shader& shader, GLenum mode) const
{
  shader.SetMatrix4(this->model, "model");
  this->VAO.Bind();
  glDrawElements(mode, this->vertexCount, GL_UNSIGNED_INT, NULL);
  this->VAO.Unbind();
}
