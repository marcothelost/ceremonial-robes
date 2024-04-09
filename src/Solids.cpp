#include "CRobes/Solids.hpp"

void crb::Solids::Solid::render(const crb::Graphics::Shader& shader, GLenum mode) const
{
  crb::Space::Mat4 appliedMatrix {this->model};
  appliedMatrix = crb::Space::translate(appliedMatrix, this->position);
  shader.SetMatrix4(appliedMatrix, "model");
  this->VAO.Bind();
  glDrawElements(mode, this->vertexCount, GL_UNSIGNED_INT, NULL);
  this->VAO.Unbind();
}

crb::Solids::Solid crb::Solids::SolidFactory::createPlane(const crb::Space::Vec3& position, const float length, const float width, const unsigned int segmentCount)
{
  GLfloat vertices[(segmentCount + 1) * (segmentCount + 1) * 8];
  GLuint indices[(segmentCount * 2 + 3) * segmentCount];

  for (int z = 0; z < segmentCount + 1; z++)
  {
    for (int x = 0; x < segmentCount + 1; x++)
    {
      int index = z * (segmentCount + 1) * 8 + x * 8;
      vertices[index]     = x * length / segmentCount;
      vertices[index + 1] = 0.f;
      vertices[index + 2] = z * width / segmentCount;
      vertices[index + 3] = 0.f;
      vertices[index + 4] = 0.f;
      vertices[index + 5] = 0.f;
      vertices[index + 6] = (float)x;
      vertices[index + 7] = (float)z;
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

  crb::Graphics::VAO VAO;
  crb::Graphics::VBO VBO {vertices, (GLsizeiptr)sizeof(vertices)};
  crb::Graphics::EBO EBO {indices, (GLsizeiptr)sizeof(indices)};

  VAO.Bind();
  VBO.Bind();
  EBO.Bind();

  VAO.LinkAttribute(VBO, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)0);
  VAO.LinkAttribute(VBO, 1, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
  VAO.LinkAttribute(VBO, 2, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));

  VAO.Unbind();
  VBO.Unbind();
  EBO.Unbind();

  return crb::Solids::Solid(
    position,
    VAO,
    VBO,
    EBO,
    (segmentCount * 2 + 3) * segmentCount
  );
}
