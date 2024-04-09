#include "CRobes/Graphics.hpp"

crb::Graphics::Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
  // Shader Source Codes
  const std::string vertexShaderSource = crb::File::getContents(vertexPath);
  const std::string fragmentShaderSource = crb::File::getContents(fragmentPath);

  const char* vertexShaderSourceC = vertexShaderSource.c_str();
  const char* fragmentShaderSourceC = fragmentShaderSource.c_str();

  // Shaders
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(vertexShader, 1, &vertexShaderSourceC, NULL);
  glShaderSource(fragmentShader, 1, &fragmentShaderSourceC, NULL);

  glCompileShader(vertexShader);
  glCompileShader(fragmentShader);

  // Info Log
  int success {0};
  char infoLog[crb::INFO_LOG_SIZE];

  // Validating the Vertex Shader
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(vertexShader, crb::INFO_LOG_SIZE, NULL, infoLog);
    std::cerr << "Failed to compile the vertex shader!\n";
    std::cerr << "Error: " << infoLog << '\n';
  }

  // Validating the Fragment Shader
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(fragmentShader, crb::INFO_LOG_SIZE, NULL, infoLog);
    std::cerr << "Failed to compile the fragment shader!\n";
    std::cerr << "Error: " << infoLog << '\n';
  }

  // Shader Program
  this->ID = glCreateProgram();
  glAttachShader(this->ID, vertexShader);
  glAttachShader(this->ID, fragmentShader);
  glLinkProgram(this->ID);

  // Validating the Shader Program
  glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(this->ID, crb::INFO_LOG_SIZE, NULL, infoLog);
    std::cerr << "Failed to link the shader program!\n";
    std::cerr << "Error: " << infoLog << '\n';
  }

  // Deleting the Shaders
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

crb::Graphics::VBO::VBO(GLfloat vertices[], GLsizeiptr verticesSize)
{
  glGenBuffers(1, &this->ID);
  this->Bind();
  glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
  this->Unbind();
}

crb::Graphics::EBO::EBO(GLuint indices[], GLsizeiptr indicesSize)
{
  glGenBuffers(1, &this->ID);
  this->Bind();
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);
  this->Unbind();
}

void crb::Graphics::VAO::LinkAttribute(const crb::Graphics::VBO& VBO, GLuint layout, GLuint size, GLenum type, GLsizeiptr stride, const void* offset) const
{
  VBO.Bind();
  glVertexAttribPointer(layout, size, type, GL_FALSE, stride, offset);
  glEnableVertexAttribArray(layout);
  VBO.Unbind();
}

crb::Graphics::Texture::Texture(const std::string& pngPath, GLenum type) : type(type)
{
  glGenTextures(1, &this->ID);
  glBindTexture(type, this->ID);

  GLubyte* data;
  unsigned int width;
  unsigned int height;
  bool hasAlpha;
  crb::Image::loadFromPNG(pngPath, &data, width, height, hasAlpha);

  glTexImage2D(
    type,
    0,
    hasAlpha ? GL_RGBA : GL_RGB,
    width,
    height,
    0,
    hasAlpha ? GL_RGBA : GL_RGB,
    GL_UNSIGNED_BYTE,
    data
  );
  glGenerateMipmap(type);

  glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  glBindTexture(type, 0);
  delete data;
}
