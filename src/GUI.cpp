#include "CRobes/GUI.hpp"

void crb::GUI::Element::render(const crb::Graphics::Shader& shader) const
{
  crb::Space::Mat4 appliedMatrix {1.f};
  appliedMatrix = crb::Space::translate(appliedMatrix, {
    this->position.x,
    this->position.y,
    0.f,
  });
  shader.SetMatrix4(appliedMatrix, "model");
  this->VAO.Bind();
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
  this->VAO.Unbind();
}
