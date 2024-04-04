#include "CRobes/Solids.hpp"

void crb::Solids::Solid::render(const crb::Graphics::Shader& shader) const
{
  shader.SetMatrix4(this->model, "model");
  this->VAO.Bind();
  glDrawElements(GL_TRIANGLES, this->vertexCount, GL_UNSIGNED_INT, NULL);
  this->VAO.Unbind();
}
