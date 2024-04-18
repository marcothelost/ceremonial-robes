#include "CRobes/Solids.hpp"

crb::Solids::Solid::Solid(const crb::Space::Vec3& position, GLfloat vertices[], GLsizeiptr verticesSize, GLuint indices[], GLsizeiptr indicesSize)
: position(position), vertexCount(indicesSize / sizeof(GLuint))
{
  this->VAO = new crb::Graphics::VAO();
  this->VBO = new crb::Graphics::VBO(vertices, verticesSize);
  this->EBO = new crb::Graphics::EBO(indices, indicesSize);

  this->VAO->Bind();
  this->VBO->Bind();
  this->EBO->Bind();

  this->VAO->LinkAttribute(*this->VBO, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)0);
  this->VAO->LinkAttribute(*this->VBO, 1, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
  this->VAO->LinkAttribute(*this->VBO, 2, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));

  this->VAO->Unbind();
  this->VBO->Unbind();
  this->EBO->Unbind();
}

void crb::Solids::Solid::render(const crb::Graphics::Shader& shader, GLenum mode) const
{
  crb::Space::Mat4 appliedMatrix {this->model};
  appliedMatrix = crb::Space::translate(appliedMatrix, this->position);
  shader.SetMatrix4(appliedMatrix, "model");
  this->VAO->Bind();
  glDrawElements(mode, this->vertexCount, GL_UNSIGNED_INT, NULL);
  this->VAO->Unbind();
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

  return crb::Solids::Solid(
    position,
    vertices,
    sizeof(vertices),
    indices,
    sizeof(indices)
  );
}
