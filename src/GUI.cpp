#include "CRobes/GUI.hpp"

crb::GUI::Element::Element(const crb::Space::Vec2& position, const float x, const float y, const float width, const float height)
: position(position), VAO(), VBO(), EBO()
{
  GLfloat vertices[] =
  {
    0.f,   0.f,  0.f, 0.f, 0.f,
    width, 0.f,  0.f, 1.f, 0.f,
    0.f,   height, 0.f, 0.f, 1.f,
    width, height, 0.f, 1.f, 1.f,
  };
  GLuint indices[] =
  {
    0, 1, 3,
    0, 3, 2,
  };

  this->VAO = crb::Graphics::VAO();
  this->VBO = crb::Graphics::VBO(vertices, (GLsizeiptr)sizeof(vertices));
  this->EBO = crb::Graphics::EBO(indices, (GLsizeiptr)sizeof(indices));

  VAO.Bind();
  VBO.Bind();
  EBO.Bind();

  VAO.LinkAttribute(VBO, 0, 3, GL_FLOAT, 5 * sizeof(GLfloat), (void*)0);
  VAO.LinkAttribute(VBO, 1, 2, GL_FLOAT, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

  VAO.Unbind();
  VBO.Unbind();
  EBO.Unbind();
}

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
