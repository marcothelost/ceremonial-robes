#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;

out vec2 vertTex;

uniform mat4 model;
uniform mat4 cameraMatrix;

void main()
{
  vertTex = aTex;
  gl_Position = cameraMatrix * model * vec4(aPos, 1.f);
}
