#include "CRobes/Solids.hpp"

void crb::Solids::Solid::render(const crb::Graphics::Shader& shader, GLenum mode) const
{
  shader.SetMatrix4(this->model, "model");
  this->VAO.Bind();
  glDrawElements(mode, this->vertexCount, GL_UNSIGNED_INT, NULL);
  this->VAO.Unbind();
}

crb::Solids::Solid crb::Solids::SolidFactory::createPlane(const crb::Space::Vec3& position, const float length, const float width, const unsigned int segmentCount)
{
  GLfloat vertices[(segmentCount + 1) * (segmentCount + 1) * 6];
  GLuint indices[(segmentCount * 2 + 3) * segmentCount];

  for (int z = 0; z < segmentCount + 1; z++)
  {
    for (int x = 0; x < segmentCount + 1; x++)
    {
      int index = z * (segmentCount + 1) * 6 + x * 6;
      vertices[index]     = x * length / segmentCount;
      vertices[index + 1] = 0.f;
      vertices[index + 2] = z * width / segmentCount;
      vertices[index + 3] = 0.1f;
      vertices[index + 4] = 0.1f;
      vertices[index + 5] = 0.1f;
    }
  }

  for (int i = 0; i < segmentCount; i++)
  {
    for (int j = 0; j <= segmentCount * 2 + 2; j++)
    {
      if (j == segmentCount * 2 + 2)
      {
        indices[i * (segmentCount * 2 + 2) + j + i] = 65535;
        continue;
      }
      indices[i * (segmentCount * 2 + 2) + j + i] =
        i * (segmentCount + 1)
        + (j % 2 == 0 ? j : j + segmentCount)
        - j / 2;
    }
  }

  crb::Graphics::VAO VAO1;
  crb::Graphics::VBO VBO1 {vertices, (GLsizeiptr)sizeof(vertices)};
  crb::Graphics::EBO EBO1 {indices, (GLsizeiptr)sizeof(indices)};

  VAO1.Bind();
  VBO1.Bind();
  EBO1.Bind();

  VAO1.LinkAttribute(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0);
  VAO1.LinkAttribute(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

  VAO1.Unbind();
  VBO1.Unbind();
  EBO1.Unbind();

  return crb::Solids::Solid(
    position,
    VAO1,
    VBO1,
    EBO1,
    (segmentCount * 2 + 3) * segmentCount
  );
}
